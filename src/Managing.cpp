#include "../include/Managing.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>

using namespace std;

void printvector(vector<string> path) {
  for (vector<string>::const_iterator i = path.begin(); i != path.end(); i++) {
    cout << *i << endl;
  }
}

void checkAll(string* one, string* two, char r){
  cout<<*one<<endl;
  cout<*two<<endl;
  cout<<r<<endl;
  cout<<"*******************************************"<<endl;
}

int Managing::run() {
  string contentOne;
  string contentTwo;
  vector<string> fileList = getMasterVector(masterfilePath);
  for(vector<string>::iterator i = fileList.begin(); i != fileList.end() - 1; i++){
    contentOne = getContent(*i);
    for(vector<string>::iterator j = i + 1; j != fileList.end(); j++){
      contentTwo = getContent(*j);
      if(checkAll(&contentOne,&contentTwo, rigor)){
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

string Managing::getContent(string filepath){
  string content = "";
  ifstream inFile;
  inFile.open(filepath);
  string data;
  while(getline(inFile,data)){
    content += data;
  }
  inFile.close();
  return content;
}

void Managing::gotcha(string fileOne, string fileTwo){
  string newEntry = fileOne + ", " + fileTwo;
  suspiciousFiles.push_back(newEntry);
}

