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

int Managing::run() {
  vector<string> fileList = getMasterVector(masterfilePath);
  return 0;
}

void Managing::printSuspiciousPairs() {
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
