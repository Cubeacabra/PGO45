a.out: main.o crab.o dataset.o
	g++ main.o crab.o dataset.o

main.o: main.cc crab.h dataset.h
	g++ -c main.cc 

crab.o: crab.cc crab.h
	g++ -c crab.cc
dataset.o: dataset.cc dataset.h crab.h
	g++ -c dataset.cc
