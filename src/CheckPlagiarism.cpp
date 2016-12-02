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
  /*if(isSameFile(oneBegin, oneEnd, twoBegin, twoEnd)) {
    return true;
  }
  else if(checkNgram(oneBegin, oneEnd, twoBegin, twoEnd, rigor)) {
    return true;
  }
  else {
    return checkControlC(oneBegin, oneEnd, twoBegin, twoEnd, rigor);  
  }*/
  swap(&oneBegin, &oneEnd, &twoBegin, &twoEnd);
  return checkNgram(oneBegin, oneEnd, twoBegin, twoEnd, rigor);
}

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

void swap(vector<string>::iterator *oneBegin, vector<string>::iterator *oneEnd,vector<string>::iterator* twoBegin,vector<string>::iterator* twoEnd) {
  if(getLength(*oneBegin,*oneEnd) > getLength(*twoBegin,*twoEnd)){ //always makes sure vector one is the smaller of the two
    auto temp = *oneBegin;
    *oneBegin = *twoBegin;
    *twoBegin = temp;

    temp = *oneEnd;
    *oneEnd = *twoEnd;
    *twoEnd = temp;
  }
  
}

bool checkNgram(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd, char rigor){
  //  cout<<getLength(oneBegin,oneEnd)<<endl;
  //cout<<getLength(twoBegin,twoEnd)<<endl;

  double totalPlagLength; //holds plagiarized string lengths
  int exceptions = 0;
  //double totalDist = 0.0;
  vector<string> temp;
  double plagPercent;  //plagiarized string length over total length

  for(vector<string>::iterator i = oneBegin; i != oneEnd; i++){
    //cout<<"loop one entered"<<endl;
    for(vector<string>::iterator it = twoBegin; it != twoEnd; it++){
      //cout<<"loop two entered"<<endl;
      exceptions = 0;
      temp.clear();     
      if(*i == *it){
	//cout << *i << " current word" << endl;
	temp.push_back(*i);
	
	//************************************
	vector<string>::iterator ite = i+1;
	vector<string>::iterator iter = it+1;
	//cout<<"after iterator increment"<<endl;
	while(exceptions < 3 && ite != oneEnd) {
	  
	  //cout << "Distance is: " << dist << endl;
	  //cout << *ite << " " << *iter <<endl;
	  temp.push_back(*ite);
      	  if(*ite != *iter){
	    exceptions++;
	  }
	  ite++;
	  iter++;
	  //cout<<"total dist "<<totalDist<<endl;
	  //cout<<"avgDist "<<avgDist<<endl;
	}
	if(temp.size() < 5) {
	  continue;
	}

	else{
	  if(*(ite-1) != *(iter-1)) {
	    //cout<<"NOT END OF FILE"<<endl;
	    temp.pop_back(); //gets rid of erroneous last word if the reason why we broke the build was because the avgDist was to big
	  }
	  totalPlagLength += temp.size();
	  //cout << totalPlagLength << " is the length of plagiarised words" << endl;
	  i = ite-1;
	  break;
	}
      }
    }//end inner
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
    //cout << plagPercent << " is the plagiarism Percentage and " << totalPlagLength << " is the totalPlagLength " << endl;
  }
  return false;

  
}

bool checkControlC(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd, char rigor){
  //cout<<"entered function"<<endl;
  
  //cout<<getLength(oneBegin,oneEnd)<<endl;
  //cout<<getLength(twoBegin,twoEnd)<<endl;

  double totalPlagLength; //holds plagiarized string lengths
  double avgDist = 0.0;
  double totalDist = 0.0;
  vector<string> temp;
  double plagPercent;
  
  for(vector<string>::iterator i = oneBegin; i != oneEnd; i++){
    //cout<<"loop one entered"<<endl;
    for(vector<string>::iterator it = twoBegin; it != twoEnd; it++){
      //cout<<"loop two entered"<<endl;
      avgDist = 0.0;
      totalDist = 0.0;
      temp.clear();
      
      double dist = levenshteinDistance(*i,*it);
      if((dist < 2 && i->length() > 4) || (dist == 0 && i->length() <=4)){ // if equalsish
	//cout << *i << " current word" << endl;
	temp.push_back(*i);
	totalDist += dist;
	//************************************
	vector<string>::iterator ite = i+1;
	vector<string>::iterator iter = it+1;
	//cout<<"after iterator increment"<<endl;
	while(avgDist < 1.5 && ite != oneEnd) {	  	  
	  dist = levenshteinDistance(*ite, *iter);
	  //cout << "Distance is: " << dist << endl;
	  //cout << *ite << " " << *iter <<endl;
	  temp.push_back(*ite);
	  /*for(auto itera = temp.begin(); itera != temp.end(); itera++) {
	    cout << *itera << " ";
	  }*/
	  //cout << endl;
	  totalDist += dist;
	  //cout << temp.size() << " is size of wector" << endl;
	  avgDist = totalDist/temp.size();
	  ite++;
	  iter++;
	  //cout<<"total dist "<<totalDist<<endl;
	  //cout<<"avgDist "<<avgDist<<endl;
	}
	if(temp.size() < 3) {
	  continue;
	}

	else{
	  if(dist > 3) {
	    //cout<<"NOT END OF FILE"<<endl;
	    temp.pop_back(); //gets rid of erroneous last word if the reason why we broke the build was because the avgDist was to big
	  }
	  totalPlagLength += temp.size();
	  //cout << totalPlagLength << " is the length of plagiarised words" << endl;
	  i = ite-1;
	  break;
	}	
      }
    }//end inner
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
  
  if(getLength(oneBegin, oneEnd) != getLength(twoBegin, twoEnd)) {
    return false;
  }
  
  for(i = oneBegin; i != oneEnd; i++) {
    if(*i != *it) {
      return false;
    }
    it++;
  }

  return true;
    
}

int getLength(vector<string>::iterator begin, vector<string>::iterator end) {
  int length = 0;
  for(vector<string>::iterator i = begin; i != end; i++) {
    length++;
  }
  return length;
}
