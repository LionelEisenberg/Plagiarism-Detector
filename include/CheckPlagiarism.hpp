/*
Lionel Eisenberg
Sanat Deshpande

This class contains methods used by Managing.cpp to check for various types of plagerism. 
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

bool checkAll(vector<string>::iterator one, vector<string>::iterator two, char rigor); //goes through and checks to string vectors for plagerism by calling various methods
int levenshteinDistance(vector<string>::iterator one, vector<string>::iterator two); //returns levenshtein distance between two string vectors

bool checkControlC(vector<string>::iterator one, vector<string>::iterator two, char rigor); //checks two string vector for "Control-C" type plagerism 
