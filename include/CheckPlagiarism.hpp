/*
Lionel Eisenberg
Sanat Deshpande

This class contains methods used by CheckPlagiarism.cpp to check for various types of plagerism. 
*/

#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

bool checkAll(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd, char rigor); //goes through and checks to string vectors for plagerism by calling various methods
int levenshteinDistance(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd); //returns levenshtein distance between two string vectors
int getLength(vector<string>::iterator begin, vector<string>::iterator end); //returns length of vector based on begin and end iterators

bool isSameFile(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd);
bool checkControlC(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd, char rigor); //checks two vectors for "Control-C" plagiarism using levenshtein distance method
bool checkNgram(vector<string>::iterator oneBegin, vector<string>::iterator oneEnd,vector<string>::iterator twoBegin,vector<string>::iterator twoEnd, char rigor); //checks for "Control-C plagiarism using Ngram method

void swap(vector<string>::iterator* oneBegin, vector<string>::iterator* oneEnd,vector<string>::iterator* twoBegin,vector<string>::iterator* twoEnd); //makes "one" iterators refer to "two" iterators
