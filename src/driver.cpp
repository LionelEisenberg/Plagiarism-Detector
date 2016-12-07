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
  if(argc != 2 && argc != 3) {
    cout << "ERROR: THe number of supplied arguments is not correct" << endl;
    return 0;
  }

  string masterfilePath = argv[1];
  char rigor;

    
  if(argc == 3) {
    if(!argv[2][1] == '\0') {
      cout << "ERROR: Wrong Format for rigor parameter" << endl;
      return 0;
    }
    rigor = tolower(argv[2][0]);
  }

  else {
    rigor = 'm';
  }

  Managing m = Managing(masterfilePath, rigor);
  m.run();
  m.printSuspiciousPairs();

  return 0;
}
