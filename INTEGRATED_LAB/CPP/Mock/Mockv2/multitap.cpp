/*********************************************************
 * MSc Mock C++ Lab Exam 2015
 * Multitap
 * Implementation File: multitap.cpp
 * Author: Chris Snowden (cps15)
 * Last Modified: 11/01/16
 *********************************************************/

#include <cctype>
#include <iostream>
using namespace std;

#include "multitap.h"


int encode_character(char ch, char* multitap){

  if(isupper(ch)) {
    *multitap++ = '#';
    return 1 + encode_character(tolower(ch),multitap);
  }
  int presses = 0;
  
  if(isdigit(ch)) {
    *multitap++ = '*';
    *multitap++ = ch;
    presses += 2;
  } else if (ispunct(ch) || islower(ch) || ch == ' ') {
    char num = findOnKeyPad(ch, presses);
    for(int i = 0; i < presses; ++i)
      *multitap++ = num;
  }

  *multitap = '\0';
  
  return presses;

}

char findOnKeyPad(char ch, int& presses) {

  for(int j = 0; j < 10; ++j) {
    for(presses = 1; keypad[j][presses - 1] != '\0'; ++presses) {
      if(keypad[j][presses - 1] == ch) {
	return '0' + j;
      }
    }
  }
  return '?';
}

bool ispunct(char ch) {
  return ch == '.' || ch == ',' || ch == '!' || ch == '?';
}

void encode(const char* plaintext, char* multitap){

  bool inCap = false;
  char c;
  int temp;
  
  c = *plaintext++;
  
  while(c != '\0') {

    if(isupper(c)) {
      if(inCap)
	c = tolower(c);
      inCap = true;
    } else if( inCap && islower(c)) {
      c = toupper(c);
      inCap = false;
    }
    
    multitap += encode_character(c, multitap);
    
    if(*plaintext != '\0' && islower(*plaintext))
      if(findOnKeyPad(tolower(c),temp) == findOnKeyPad(*plaintext,temp))
	*multitap++ = '|';
    
    c = *plaintext++;
  }
}
