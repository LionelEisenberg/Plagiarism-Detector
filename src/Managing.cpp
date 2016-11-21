#include "../include/Managing.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>

int Managing::run() {
  cout << "run" <<endl;
  return 0;
}

void Managing::printSuspiciousPairs() {
  cout << "print" << endl;
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
