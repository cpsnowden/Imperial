#include <cctype>
#include <iostream>
#include "soundex.h"
using namespace std;

void encode(const char* surname, char* soundex){
 
  *soundex = toupper(*surname);
  soundex++;
  surname++;
  
  int  count = 1;
  char code;

  while(*surname != '\0') {
    
    code = character_code(surname);
    if((code != *(soundex-1)) && code != '0') {
	*soundex = code;
	soundex++;
	count++;
      }
    surname++;
  }

  for(;count <= 3; count++) {
    *soundex = '0';
    soundex++;
  }
  *soundex = '\0';
}

char character_code(const char* surname) {

  char one[4] = {'b', 'f', 'p', 'v'};
  char two[8] = {'c', 'g', 'j', 'k', 'q', 's', 'x', 'z'};
  char three[2] = {'d', 't'};
  char four[1] = {'l'};
  char five[2] = {'m', 'n'};
  char six[1] = {'r'};
   if(character_map(*surname, one))
     return '1';
   else if(character_map(*surname, two))
     return '2';
   else if(character_map(*surname, three))
     return '3';
   else if(character_map(*surname, four))
     return '4';
   else if(character_map(*surname, five))
     return '5';
   else if(character_map(*surname, six))
     return '6';
   else
     return '0';
}

bool character_map(const char character, const char* soundexMap) {
  while(*soundexMap != '\0') {
    if((character == *soundexMap) || (character == toupper(*soundexMap)))
      return true;
    soundexMap++;
  }
  return false;
}

bool compare(const char* one, const char* two){
  
  if((*one != *two))
    return false;
  else if((*one == '\0' && *two == '\0') || compare(++one, ++two))
    return true;
  return false;
}

int count(const char* surname, const char* sentence){

  int counter = 0;
  char surSoundex[5], wordSoundex[5],  word[10];
  char* word_ptr;
  bool flag = false;
  word_ptr= word;
  encode(surname, surSoundex);

while(*sentence != '\0') {
    if(isalpha(*sentence)) {
	*word_ptr = *sentence;
	word_ptr++;
	flag = true;
    }
    else if(flag) {
      *word_ptr = '\0';
      encode(word, wordSoundex);
     
      if(compare(surSoundex, wordSoundex))
	counter++;
     word_ptr = word;
     flag = false;
    }
    sentence++;
 }

  return counter;
}

