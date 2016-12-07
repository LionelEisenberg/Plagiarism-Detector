// TODO
// Make sure CheckControlC does not Seg Fault
// Make sure isameFile works
// implement thesaurus maybe
// if quotes then dont say plagia?
// 

#include "../include/CheckPlagiarism.hpp"
#include <algorithm> 
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

bool checkAll(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd, char rigor) {
  swap(&oneBegin, &oneEnd, &twoBegin, &twoEnd); //swap vectors if vector one > vector two
  if(isSameFile(oneBegin, oneEnd, twoBegin, twoEnd)) { //checks if both vectors are literally the same
    return true;
    }
  else if (checkNgram(oneBegin, oneEnd, twoBegin, twoEnd, rigor)){
    return true; //Gets an Ngram comparison of vectors
  }
   /*else { //This is a function that checks plagiarism a bit more thoroughly however it was very time intensive on our machines so we decided not to include this test. however please feel free to uncomment this and try it out.
    return checkControlC(oneBegin, oneEnd, twoBegin, twoEnd, rigor);  
    }*/
  return false;
}

//Levenshtein Distance Algorithm gives us the number of operations we need to do to a string to get another string. These include substitution, deletion and addition. We basically get a "distance" from one word to another.
int levenshteinDistance(string& one, string& two){ //source https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C.2B.2B
  const std::size_t len1 = one.size(), len2 = two.size();
  std::vector<unsigned int> col(len2+1), prevCol(len2+1);

  for (unsigned int i = 0; i < prevCol.size(); i++)
    prevCol[i] = i;
  for (unsigned int i = 0; i < len1; i++) {
    col[0] = i+1;
    for (unsigned int j = 0; j < len2; j++)
      col[j+1] = std::min({ prevCol[1 + j] + 1, col[j] + 1, prevCol[j] + (one[i]==two[j] ? 0 : 1) });
    col.swap(prevCol);
  }
  return prevCol[len2];
}

//function swaps vector iterators if the first one is bigger than the second, making it easier for comparing texts in future functions
void swap(vector<string>::iterator *oneBegin, vector<string>::iterator *oneEnd,vector<string>::iterator* twoBegin,vector<string>::iterator* twoEnd) { 
  if(getLength(*oneBegin,*oneEnd) > getLength(*twoBegin,*twoEnd)){ //always makes sure vector one is the smaller of the two
    auto temp = *oneBegin; //temporary holder for our iterator
    *oneBegin = *twoBegin;
    *twoBegin = temp;

    cout<<"SWAPPED"<<endl;
    
    temp = *oneEnd;
    *oneEnd = *twoEnd;
    *twoEnd = temp;
  }
  
}

//check Ngram Parses through the two texts and reports similarities, if the similarities are too high, we return true, to indicate the files are suspicious, if not we return false. Whether or not we return true is determined by the rigor Character.
bool checkNgram(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd, char rigor){
  double totalPlagLength = 0.0; //holds plagiarized string lengths
  int exceptions = 0; //number of exceptions a sentence can have where an exception is equivalent to two words differing;
  vector<string> temp = {}; //this vector temporary holds a sentence that both texts contain, we flag it as suspicious and record its length.
  double plagPercent = 0.0; //plagiarized string length over total length of text

  for(vector<string>::iterator i = oneBegin; i != oneEnd; i++){ //for loop that parses through file 1, AKA the smaller file
    //cout << "enter first loop" << endl;
    for(vector<string>::iterator it = twoBegin; it != twoEnd; it++){ //for loop that parses through file 2 for instance of i
      exceptions = 0;
      temp.clear();     
      if(*i == *it && (i)!=(oneEnd-1) && (it)!=(twoEnd-1)){ //if the i and it iterators are equal, or if a word in file 1 is equal to a word in file 2 then start comparison of teh words that preceed these.
	temp.push_back(*i); //add i to vector of plagiarised strings;
	vector<string>::iterator ite = i+1; //create iterators to go through the sentence, while keeping out i and it iterators at their respective places
	vector<string>::iterator iter = it+1;
	while(exceptions < 3 && ite != oneEnd && iter != twoEnd) { //while the sentences are very similar or we have not reached the end of the file compare the next word in the file
	  temp.push_back(*ite);
      	  if(*ite != *iter){
	    exceptions++; //if two words do not match increment the exceptions counter
	  }
	  ite++;
	  iter++;
	}
	if(temp.size() < 5) { //if the detected plagiarised sentence is smaller than 5 then do not count said sentence as suspicious.
	  continue;
	}

	else{
	  if(*( ite-1) != *(iter-1)) { //This if statement basically takes the last words out if they are the ones which caused our sentence to be flagged as no longer suspicious  
	    temp.pop_back(); //gets rid of erroneous last word if the reason why we broke the build was because the avgDist was to big
	    ite--;           //subsequent calls get rid of last total of 3 words if the last 3 were erroneous
	    iter--;
	    if(*(ite-1) != *(iter -1)) {
	      temp.pop_back();
	      ite--;
	      iter--;
	      if(*(ite-1) != *(iter -1)) {
		temp.pop_back();
		ite--;
		iter--;
	      }
	    }
	  }
	  totalPlagLength += temp.size(); 
	  i = ite-1;
	  break;
	}
      }
    }
    
    plagPercent = totalPlagLength/getLength(oneBegin, oneEnd); //Calculate plageriasim percentage of the file
    
    switch(rigor) {
    case 'h':
      if(plagPercent > 0.2 || totalPlagLength > 100) {
	return true;
      }
      break;
    case 'm':
      if(plagPercent > 0.4 ) {
	return true;
      }
      break;
    case 'l':
      if(plagPercent > 0.7 ) {
	return true;
      }
      break;
    }
  }
  return false;

  
}

//Check ControlC is a more fully fleshed version of Ngram which goers further than making sure if two words are equal, it looks at the Levenshtein distance bteween these words and then decides if a sentence is plagiarised or not give its average distance between words.
bool checkControlC(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd, char rigor){
  double totalPlagLength = 0.0; //holds plagiarized string lengths
  double avgDist = 0.0; //average levenshtein distance between two sentences.
  double totalDist = 0.0; //total levenshtein distance between two sentences
  vector<string> temp; //this vector temporary holds a sentence that both texts contain, we flag it as suspicious and record its length.
  double plagPercent; //plagiarized string length over total length of text
  
  for(vector<string>::iterator i = oneBegin; i != oneEnd; i++){ //for loop that parses through file 1, AKA the smaller file
    for(vector<string>::iterator it = twoBegin; it != twoEnd; it++){ //for loop that parses through file 2 for instance of i
      avgDist = 0.0;
      totalDist = 0.0;
      temp.clear();
      double dist = levenshteinDistance(*i,*it); //calculates Levenshtein distance between two words
      if((dist < 2 && i->length() > 4) || (dist == 0 && i->length() <=4)){ // in stead of looking if two words are equal we look if they are equalish, meaning if the distance proportional to their size is not too big
	temp.push_back(*i);
	totalDist += dist;
	vector<string>::iterator ite = i+1;
	vector<string>::iterator iter = it+1;
	while(avgDist < 1.5 && ite != oneEnd) {	// while average distance is smaller than 1 and a half substitutions per word, and we have not reached the end of the file, we keep comparing words
	  dist = levenshteinDistance(*ite, *iter); //set levenshtein distance to compare the next words
	  temp.push_back(*ite);
	  totalDist += dist; //increment total distance by current distance
	  avgDist = totalDist/temp.size(); //update average distance
	  ite++; 
	  iter++;
	}
	if(temp.size() < 3) { //if plagiarised sentence is small, do not flag it as plagiarised
	  continue;
	}

	else{
	  if(dist > 3) { //if the last words were very different and were the reason we broke out of the build then pop it from the vector
	    ite--;
	    temp.pop_back();
	  }
	  totalPlagLength += temp.size(); //update totalPlageLength
	  i = ite-1; //set iterator to the word at the end of the comparison
	  break;
	}	
      }
    }
    
    plagPercent = totalPlagLength/getLength(oneBegin, oneEnd);
    
    switch(rigor) {
    case 'h':
      if(plagPercent > 0.2 || totalPlagLength > 100) {
	return true;
      }
      break;
    case 'm':
      if(plagPercent > 0.4 ) {
	return true;
      }
      break;
    case 'l':
      if(plagPercent > 0.7 ) {
	return true;
      }
      break;
    }
  }
  return false;

}

bool isSameFile(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd) {
  vector<string>::iterator i;
  vector<string>::iterator it = twoBegin;
  
  if(getLength(oneBegin, oneEnd) != getLength(twoBegin, twoEnd)) { //if the length of texts is not the same, thet cannot be exactly the same file.
    return false;
  }
  
  for(i = oneBegin; i != oneEnd; i++) { //parse through both files to look if each word is equal
    if(*i != *it) {
      return false;
    }
    it++;
  }

  return true;
    
}

//gets length of vector
//returns an int
int getLength(vector<string>::iterator begin, vector<string>::iterator end) {
  int length = 0;
  for(vector<string>::iterator i = begin; i != end; i++) {
    length++;
  }
  return length;
}
