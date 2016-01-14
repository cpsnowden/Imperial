/*****************************************************
 * MSc C++ Programming Unassessed Exercise 2 - Soundex
 * Implementation File - soundex.cpp
 * Author - Chris Snowden (cps15)
 * Last Modified - 07/01/15 1h20
 ****************************************************/

#include <iostream>
#include <cctype>
using namespace std;

#include "soundex.h"

void encode(const char* surname, char* soundex){
  
  int length = 1;
  *soundex++  = *surname++;

  for(; *surname != '\0' && length <= 3; ++surname) {
    if(getMapping(*surname,*soundex) && *soundex != *(soundex - 1)) {
      ++soundex;
      ++length;
    }
  }

  for(;length <=3; ++length)
    *soundex++ = '0';

  *soundex = '\0';
}

bool getMapping(char c, char& s) {
  for(int i = 0; i < 6; ++i) {
    for(int j = 0; mapping[i][j] != '\0'; ++j) {
      if(mapping[i][j] == c) {
	s = '1' + i;
	return true;
      }
    }
  }
    return false;
}

bool compare(const char* one, const char* two){
  if(*one == '\0' && *two == '\0')
    return true;

  return (*one == *two) && compare(++one, ++two);
}

int count(const char* surname, const char* sentence){

  if(*sentence == '\0')
    return 0;
  
  char surSoundex[5], testSoundex[5], testSurname[20];
  int i = 0;
  encode(surname, surSoundex);
  
  while(*sentence != '\0' && isalpha(*sentence) && i < 19) {
    testSurname[i++] = *sentence++;
  }

  testSurname[i] = '\0';
  encode(testSurname, testSoundex);

  while(*sentence != '\0' && !isalpha(*sentence))
    ++sentence;

  return compare(testSoundex,surSoundex) + count(surname, sentence);

}

