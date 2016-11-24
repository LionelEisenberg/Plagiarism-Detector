#include "../include/CheckPlagiarism.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

bool CheckPlagiarism::checkAll(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd, char rigor) {
  return isSameFile(oneBegin, oneEnd, twoBegin, twoEnd);
  return checkControlC(oneBegin, oneEnd, twoBegin, twoEnd, rigor);  
}

int CheckPlagiarism::levenshteinDistance(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd) {
  
}

bool CheckPlagiarism::isSameFile(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd) {
  vector<string>::iterator i;
  vector<string>::iterator it = twoBegin;

  if(getLength(oneBegin, oneEnd) != getLength(twoBegin, twoEnd)) {
    return false;
  }
  
  for(i = oneBegin; i != oneEnd; i++) {
    if(*i != *it) {
      return false;
    }
    it++
  }

  return true;
    
}

int CheckPlagiarism::getLength(vector<string>::iterator begin, vector<string>::iterator end) {
  int length = 0;
  for(auto i = begin; i != end; i++) {
    length++;
  }
  return length;
}
