#include "piglatin.h"
#include <iostream>
#include <cctype>
using namespace std;

int findFirstVowel(const char* word){
  int len = strlen(word);
  for(int i = 0; i < len; ++i) {
    if(isVowel(word[i],i,len))
      return i;
  }
  return -1;
}

bool isVowel(char ch, int position, int length){
  if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
    return true;
  else if(ch == 'y' && ( position != 0 ) && (position != length - 1))
    return true;
  
  return false;
}

void translateWord(const char* english, char* piglatin){

  if(isdigit(*english)) {
    strcpy(piglatin, english);
    return;
  }

  int firstVowelPos = findFirstVowel(english);
  strcpy(piglatin, english);
  switch(firstVowelPos) {
  case 0:
    //Begins with vowel
    strcat(piglatin, "way");
    break;
  case -1:
    //Contains no vowel
    strcat(piglatin, "ay");
    break;
  default:
    if(isupper(*piglatin))
    *piglatin = tolower(*piglatin);
    strncat(piglatin, piglatin, firstVowelPos);
    strcpy(piglatin, piglatin + firstVowelPos);
    strcat(piglatin,"ay");
    break;
  }

  if(isupper(*english))
    *piglatin = toupper(*piglatin);
  
  return;
}

void translateStream(istream& inputStream, ostream& outputStream){

  char c;
  char buf[65], pigbuf[68];
  
  if(inputStream.eof())
    return;

  inputStream.get(c);
  
  if(!isalpha(c))
    outputStream << c;
  else if(isalpha(c)) {
    int i;
    for(i = 0; isalpha(c) || inputStream.eof(); ++i) {
      buf[i] = c;
      inputStream.get(c);
    }
    buf[i] = '\0';

    //    cout << "Word " << buf << endl;
    
    inputStream.putback(c);
    translateWord(buf, pigbuf);
    outputStream << pigbuf;
  }

  translateStream(inputStream, outputStream);
}
