#ifndef PIGLATIN_H
#define PIGLATIN_H

#include <iostream>
using namespace std;

int findFirstVowel(const char* word);

bool isVowel(char ch, int position, int length);

void translateWord(const char* english, char* piglatin);

void translateStream(istream& inputStream, ostream& outputStream);


#endif
