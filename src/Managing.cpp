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
  for(vector<string>::iterator i = fileList.begin(); i != fileList.end() - 1; i++){
    contentOne = getContent(*i);
    printvector(contentOne);
    for(vector<string>::iterator j = i + 1; j != fileList.end(); j++){
      contentTwo = getContent(*j);
      
      if(1){//checkAll(contentOne.begin(),contentOne.end(),contentTwo.begin(), contentTwo.end(), rigor)){
	gotcha(*i,*j);
      }
    }
  }
  return 0;
}

void Managing::printSuspiciousPairs() {
  for(vector<string>::iterator i = suspiciousFiles.begin(); i != suspiciousFiles.end(); i++){
    cout<<*i<<endl;
  }
}

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

