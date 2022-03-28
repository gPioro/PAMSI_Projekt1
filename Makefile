

CXXFLAGS= -Wall 


main: main.o algorytmy_sortowania.o
	g++ -Wall -o main main.o algorytmy_sortowania.o

main.o: main.cpp algorytmy_sortowania.hh
	g++ -c ${CXXFLAGS} -o main.o main.cpp

algorytmy_sortowania.o: algorytmy_sortowania.cpp algorytmy_sortowania.hh
	g++ -c ${CXXFLAGS} -o algorytmy_sortowania.o algorytmy_sortowania.cpp
