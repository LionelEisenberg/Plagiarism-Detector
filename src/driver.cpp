#include "../include/Managing.hpp"
#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  if(argc != 2 || argc != 3) {
    cout << "ERROR: THe number of supplied arguments is not correct" << endl;
    return 0;
  }

  string filePath = argv[1];
  if(argc == 3) {
    char suspicionStrength = argv[2];
  }

  else {
    char suspicionStrength = 'm';
  }

  Managing m = Managing(filePath, suspiciousStrength);
  m.run();

  return 0;
}
