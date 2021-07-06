CC=g++
DEV=-Wall -g -std=c++14
OPT=-O3 -std=c++14

JSON=json.hpp

all: consistentresultverification sortedverification timealgorithms

consistentresultverification: consistentresultverification.cpp
	g++ -std=c++14 consistentresultverification.cpp -o consistentresultverification

sortedverification: sortedverification.cpp
	g++ -std=c++14 sortedverification.cpp -o sortedverification

timealgorithms: timealgorithms.cpp insertionsort.o mergesort.o quicksort.o
	g++ -std=c++14 timealgorithms.cpp insertionsort.o mergesort.o quicksort.o -o timealgorithms

insertionsort.o: insertionsort.cpp insertionsort.h json.hpp extern.h
	g++ -std=c++14 -c insertionsort.cpp

mergesort.o: mergesort.cpp mergesort.h json.hpp extern.h
	g++ -std=c++14 -c mergesort.cpp

quicksort.o: quicksort.cpp quicksort.h json.hpp extern.h
	g++ -std=c++14 -c quicksort.cpp

clean:
	rm -f *.o
	rm -f *.csv
	rm -rf *.dSYM
	rm -f consistentresultverification
	rm -f sortedverification
	rm -f timealgorithms
