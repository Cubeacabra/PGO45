#Making Different Builds

#Optimizer Off, ASAN/UBSAN Off
baseNoAsan: main.o crab.o dataset.o
	g++ main.o crab.o dataset.o -o baseNoAsan

#Optimizer off, ASAN/UBSAN On
baseAsan: main.o crab.o dataset.o
	g++ -fsanitize=address -fsanitize=undefined -g main.o crab.o dataset.o -o baseAsan

#Optimizer Off, ASAN/UBSAN Off
O3NoAsan: main.o crab.o dataset.o
	g++ -O3 main.o crab.o dataset.o -o O3NoAsan

#Optimizer On, ASAN/UBSAN On
O3Asan: main.o crab.o dataset.o
	g++ -O3 -fsanitize=address -fsanitize=undefined -g main.o crab.o dataset.o -o O3Asan

OFastNoAsan: main.o crab.o dataset.o
	g++ -Ofast main.o crab.o dataset.o -o OFastNoAsan

genPGO: main.o crab.o dataset.o
	g++ -O3 -fprofile-generate main.o crab.o dataset.o -o genPGO
	#add all the tests
usePGO: main.o crab.o dataset.o
	g++ -O3 -fprofile-use main.o crab.o dataset.o -o usePGO

useLTO: main.o crab.o dataset.o
	g++ -flto main.o crab.o dataset.o -o useLTO
	#use make clean before using this

usePerf: main.o crab.o dataset.o
	g++ -O3 -fno-omit-frame-pointer main.o crab.o dataset.o -o usePerf
	#Run with: perf record -g usePerf
	#add all the tests
#Making Object Files Is Normal
main.o: main.cc crab.h dataset.h
	g++ -g -c main.cc 

crab.o: crab.cc crab.h
	g++ -c crab.cc

dataset.o: dataset.cc dataset.h crab.h
	g++ -c dataset.cc

#Clean
clean:
	rm -f *.o a.out *.gcda *.gcno *.gcov baseAsan baseNoAsan O3Asan O3NoAsan OFastNoAsan genPGO usePGO useLTO usePerf
	
