/*                                                                                                                                          Lionel Eisenberg                                                                                                                            Sanat Deshpande                                                                                                                             

This file manages the list of files to search, and feeds in                                                                                 appropriate input to the plagerism checker class                                                                                            */


#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

class Managing{

private:
  vector<string> suspiciousFiles;
  string masterfilePath;
  char rigor;

public:
  vector<string> getMasterVector(string masterfilePath); //gets vector of list of files to test
  string getContent(string filePath); //gets content of a file
  void gotcha(string filePathOne, string filePathTwo); //increments suspicious files list
  int run(); //runs all functions and interacts with plagerism checker functions


};
