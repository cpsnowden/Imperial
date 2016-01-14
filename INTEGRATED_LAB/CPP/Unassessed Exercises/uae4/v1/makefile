braille: main.o braille.o
	g++ -Wall -g braille.o main.o -o braille

main.o: main.cpp braille.h
	g++ -Wall -g -c main.cpp

braille.o: braille.cpp braille.h
	g++ -Wall -g -c braille.cpp

.PHONY: clean

clean:
	rm -f *.o braille
