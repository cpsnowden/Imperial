piglatin: piglatin.o main.o
	g++ -Wall -g piglatin.o main.o -o piglatin

piglatin.o: piglatin.h piglatin.cpp
	g++ -Wall -g -c piglatin.cpp

main.o: piglatin.h main.cpp
	g++ -Wall -g -c main.cpp

.PHONY:clean
clean:
	rm -f *.o piglatin
