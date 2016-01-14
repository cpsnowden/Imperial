correct: correct.o main.o
	g++ -Wall -g correct.o main.o -o correct

main.o: main.cpp correct.h
	g++ -Wall -g -c main.cpp

correct.o: correct.cpp correct.h
	g++ -Wall -g -c correct.cpp

.PHONY: clean

clean:
	rm -f *.o correct
