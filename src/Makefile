CXX = g++
CXXFLAGS = -std=c++11 -pedantic -O3 -Wall -Wextra -g

default: all

all: finalProject unitTest

test: unitTest
	./unitTest

finalProject: driver.o Managing.o CheckPlagiarism.o
	g++ -std=c++11 -pedantic -Wall -Wextra -O3 -o finalProject driver.o Managing.o CheckPlagiarism.o

driver.o: driver.cpp ../include/Managing.hpp
	g++ -std=c++11 -pedantic -Wall -Wextra -O3 -c driver.cpp ../include/Managing.hpp

Managing.o: Managing.cpp ../include/Managing.hpp ../include/CheckPlagiarism.hpp
	g++ -std=c++11 -pedantic -Wall -Wextra -O3 -c Managing.cpp ../include/Managing.hpp ../include/CheckPlagiarism.hpp

CheckPlagiarism.o: CheckPlagiarism.cpp ../include/CheckPlagiarism.hpp
	g++ -std=c++11 -pedantic -Wall -Wextra -O3 -c CheckPlagiarism.cpp ../include/CheckPlagiarism.hpp

unitTest: Managing.cpp CheckPlagiarism.cpp unitTestDriver.cpp unitTest-PlagiarismCheck.cpp ../include/CheckPlagiarism.hpp
	$(CXX) $(CXXFLAGS) -o unitTest Managing.cpp CheckPlagiarism.cpp unitTestDriver.cpp unitTest-PlagiarismCheck.cpp

clean:
	rm -f all finalProject *.o
