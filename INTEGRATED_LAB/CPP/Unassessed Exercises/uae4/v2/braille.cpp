/**********************************************************
 * MSc Computing Science Unassessed Exercise 4 Braille
 * Header File: braille.h
 * Author: Chris Snowden (cps15)
 * Last Modified: 07/01/16 1hr25
 *********************************************************/

#include <cctype>
#include <cstring>
using namespace std;

#include "braille.h"

int encode_character(char c, char* braille){
  
  if(isupper(c)) {
    strcpy(braille, simpleMap[10]);
    return encode_character(tolower(c), braille + len) + 1;
  }

  if( c >= 'a' && c <= 'j') {
    strcpy(braille, simpleMap[c - 'a']);
  } else if( c >= 'k' && c <= 't') {
    strcpy(braille, simpleMap[c - 'k']);
    braille[2] = '0';
  } else if( c >= 'u' && c <= 'z') {
    strcpy(braille, simpleMap[c - 'u']);
    braille[2] = '0';
    braille[5] = '0';
  } else if(isdigit(c)) {
    strcpy(braille, simpleMap[11]);
    return encode_character(c - 'a', braille + len) + 1;
  } else if(encode_punct(c, braille)) {

  } else {
    strcpy(braille, simpleMap[19]);
  }
  return 1;

}

int encode_punct(char c, char* braille){
  
  switch(c) {
  case '.':
    strcpy(braille, simpleMap[12]);
    break;
  case ',':
    strcpy(braille, simpleMap[13]);
    break;
  case ';':
    strcpy(braille, simpleMap[14]);
    break;
  case '-':
    strcpy(braille, simpleMap[15]);
    break;
  case '!':
    strcpy(braille, simpleMap[16]);
    break;
  case '?':
    strcpy(braille, simpleMap[17]);
    break;
  case '(':
    strcpy(braille, simpleMap[18]);
    break;
  case ')':
    strcpy(braille, simpleMap[18]);
    break;
  default:
    return 0;
  }

  return 1;

}

bool ispunct(char c) {
  return c == '.' || c == ',' || 
    c == ';' || c == '-' 
    || c == '!' || c == '?' 
    || c == '(' || c == ')';
}

void encode(const char* plaintext, char* braille){
  
  if(*plaintext == '\0') {
    *braille = '\0';
    return;
  }

  int chars = encode_character(*plaintext, braille);
  encode(++plaintext, braille + chars * len);

}

void print_braille(const char* plaintext, ostream& output){
  
  int nPlaintext = strlen(plaintext);
  char* braille = new (nothrow) char[nPlaintext * 2 * len + 1];
  if(!braille) {
    cerr << "Could not allocate memory on the heap"
      " for the braille conversion" << endl;
  }
  
  encode(plaintext, braille);

  for(int row = 0; row < len/2; ++row) {
    for(int i = 0; i < (int) strlen(braille); i+=len) {
    
      output << braille[(i + row)];
      output << braille[(i + len/2 + row)];
      output << " ";
    }
    output << endl;
  }

  while(*plaintext != '\0') {
    if(isupper(*plaintext) || isdigit(*plaintext))
      output << "   "; 
    output << *plaintext++ << "  ";
  }
}
