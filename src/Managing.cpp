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
  //int countOne = 0;
  //int countTwo = 0;
  for(vector<string>::iterator i = fileList.begin(); i != fileList.end() - 1; i++){
    //countOne++;
    //cout<<"outer loop file: "<<countOne<<endl;
    //cout<<"one"<<endl;
    contentOne = getContent(*i);
    //printvector(contentOne);
    //cout<<"two"<<endl;
    for(vector<string>::iterator j = i + 1; j != fileList.end(); j++){
      //countTwo++;
      //cout<<"inner loop file: "<<countTwo<<endl;
      //cout<<"three"<<endl;
      contentTwo = getContent(*j);      
      //cout<<"four"<<endl;
      if(checkAll(contentOne.begin(),contentOne.end(),contentTwo.begin(), contentTwo.end(), rigor)) {
	//cout<<"pre-gotcha"<<endl;
	gotcha(*i,*j);
	//cout<<"post-gotcha"<<endl;
      }
    }
    //countTwo = countOne;
  }
  cout<<"we gucci"<<endl;
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

