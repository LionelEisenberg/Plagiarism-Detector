finalProject: driver.o Managing.o CheckPlagiarism.o
	 g++ -std=c++11 -pedantic -Wall -Wextra -o finalProject driver.o Managing.o CheckPlagiarism.o

driver.o: driver.cpp ../include/Managing.hpp
	g++ -std=c++11 -pedantic -Wall -Wextra  -c driver.cpp ../include/Managing.hpp

Managing.o: Managing.cpp ../include/Managing.hpp ../include/CheckPlagiarism.hpp
	g++ -std=c++11 -pedantic -Wall -Wextra  -c Managing.cpp ../include/Managing.hpp ../include/CheckPlagiarism.hpp

CheckPlagiarism.o: CheckPlagiarism.cpp ../include/CheckPlagiarism.hpp
	g++ -std=c++11 -pedantic -Wall -Wextra  -c CheckPlagiarism.cpp ../include/CheckPlagiarism.hpp

clean:
	rm -f *.o 
