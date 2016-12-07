#include "../include/catch.hpp" // simple unit-testing framework
#include "../include/CheckPlagiarism.hpp" // the functions we want to test
#include "../include/Managing.hpp"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

TEST_CASE("checkAll", "[checkAll]"){
  vector<string> one = {"this","is","a","test"};
  vector<string> two = {"this","is","a","test"};
  vector<string> three = {"very","different","collection","of","strings"};
  CHECK(checkAll(one.begin(),one.end(),two.begin(),two.end(),'h') == true);
  CHECK(checkAll(one.begin(),one.end(),three.begin(),three.end(),'h') == false);
}


TEST_CASE("levenshteinDistance","[levenshteinDistance]"){
  string one = "test";
  string two = "test";
  string three = "taste";
  string four = "froggy";
  CHECK(levenshteinDistance(one,two) == 0);
  CHECK(levenshteinDistance(one,three) == 2);
  CHECK(levenshteinDistance(one,four) == 6);
}

TEST_CASE("getLength","[getLength]"){
  vector<string> one = {"this","is","a","test"};
  CHECK(getLength(one.begin(),one.end()) == 4);
}

TEST_CASE("sameFile","[isSameFile]"){
  vector<string> one = {"this","is","a","test"};
  vector<string> two = {"this","is","a","test"};
  vector<string> three = {"very","different","collection","of","strings"};
  CHECK(isSameFile(one.begin(),one.end(),two.begin(),two.end()) == true);
  CHECK(isSameFile(one.begin(),one.end(),three.begin(),three.end()) == false);
}

TEST_CASE("control-c","[checkControlC]"){
  vector<string> one = {"this","is","a","test"};
  vector<string> two = {"this","is","a","taste"};
  vector<string> three = {"very","different","collection","of","strings"};
  CHECK(checkControlC(one.begin(),one.end(),two.begin(),two.end(),'h') == true);
  CHECK(checkControlC(one.begin(),one.end(),three.begin(),three.end(),'h') == false);
  
}

TEST_CASE("checkNgram","[checkNgram]"){
  vector<string> one = {"this","is","a","word","test","string"};
  vector<string> two = {"this","is","a","dinosaurs","test","string"};
  vector<string> three = {"very","different","collection","of","strings"};
  CHECK(checkControlC(one.begin(),one.end(),two.begin(),two.end(),'h') == true);
  CHECK(checkControlC(one.begin(),one.end(),three.begin(),three.end(),'h') == false);
}

TEST_CASE("run","[run]") {
  Managing h = Managing("../data/test2_file_list.txt", 'h');
  Managing m = Managing("../data/test2_file_list.txt", 'm');
  Managing l = Managing("../data/test2_file_list.txt", 'l');
  CHECK(h.run() == 0);
  CHECK(m.run() == 0);
  CHECK(l.run() == 0);

  vector<string> high = h.printSuspiciousPairs();
  CHECK(high.at(0) == "../data/test_doc_set/file1.txt, ../data/test_doc_set/file2.txt");
  CHECK(high.at(1) == "../data/test_doc_set/file1.txt, ../data/test_doc_set/file3.txt");
  CHECK(high.at(2) == "");

  vector<string> medium = m.printSuspiciousPairs();
  CHECK(medium.at(0) == "../data/test_doc_set/file1.txt, ../data/test_doc_set/file2.txt");
  CHECK(medium.at(1) == "../data/test_doc_set/file1.txt, ../data/test_doc_set/file3.txt");
  CHECK(medium.at(2) == "../data/test_doc_set/file2.txt, ../data/test_doc_set/file3.txt");

  vector<string> low = l.printSuspiciousPairs();
  CHECK(low.empty() == true);
}

