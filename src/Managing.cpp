#include "../include/Managing.hpp"
#include "../include/CheckPlagiarism.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>

using namespace std;

void printvector(vector<string> path) {
  for (vector<string>::const_iterator i = path.begin(); i != path.end(); i++) {
    cout << *i << " ";
  }
}

int Managing::run() {
  vector<string> contentOne;
  vector<string> contentTwo;
  vector<string> fileList = getMasterVector(masterfilePath);
  int countOne = 0;
  int countTwo = 1;
  for(vector<string>::iterator i = fileList.begin(); i != fileList.end() - 1; i++){
    countOne++;
    contentOne = getContent(*i);
    for(vector<string>::iterator j = i + 1; j != fileList.end(); j++){
      countTwo++;
      cout<<"Comparing "<<countOne<<" to "<<countTwo<<endl;
      contentTwo = getContent(*j);      
      if(checkAll(contentOne.begin(),contentOne.end(),contentTwo.begin(), contentTwo.end(), rigor)) {
	gotcha(*i,*j);
      }
    }
    countTwo = countOne + 1;
  }
  
  return 0;
}

vector<string> Managing::printSuspiciousPairs() {
  vector<string> s;
  for(vector<string>::iterator i = suspiciousFiles.begin(); i != suspiciousFiles.end(); i++){
    cout<<*i<<endl;
    s.push_back(*i);
  }
  return s;
}

//**THESE TWO COULD BE WRITTEN AS THE SAME FUNCTION**
vector<string> Managing::getMasterVector(string masterfilePath){
  vector<string> fileList;
  ifstream inFile;
  inFile.open(masterfilePath);
  string data;
  while(getline(inFile,data)){
    fileList.push_back(data);
  }
  inFile.close();
  return fileList;
}

vector<string> Managing::getContent(string filepath){
  vector<string> content; 
  ifstream inFile;
  inFile.open(filepath);
  string data;
  while(inFile >> data){
    content.push_back(data);
  }
  inFile.close();
  return content;
}

void Managing::gotcha(string fileOne, string fileTwo){
  string newEntry = fileOne + ", " + fileTwo;
  suspiciousFiles.push_back(newEntry);
}

