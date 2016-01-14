#include "braille.h"
#include <cctype>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
using namespace std;


int encode_character(char ch, char* braille){
  
  char cap[6] = {'.','.','.','.','.','0'};
  char num[6] = {'.','.','0','0','0','0'};
  char def[7] = "......";
  char* temp = braille;
  
  if(isupper(ch)) {
    strcpy(braille, cap);
    ch = tolower(ch);
    temp += 6;
  }

  if (isdigit(ch)) {
    strcpy(braille, num);
    temp += 6;
    if(!encode_num(ch, temp))
      strcpy(temp, def);
  } else if(isalpha(ch) || ispunct(ch)) {
    if(!encode_alpha_punc(ch, temp))
      strcpy(temp, def);
  } else {
    strcpy(temp, def);
  }
  
  return strlen(braille);
}

bool encode_num(char ch, char* braille){
  if(ch == '0')
    return encode_alpha_punc('j', braille);
  return encode_alpha_punc(ch - '1' + 'a', braille);
}

bool encode_alpha_punc(char ch, char* braille) {

  map<char,string> charMap;
  charMap['a'] = "0.....";
  charMap['b'] = "00....";
  charMap['c'] = "0..0..";
  charMap['d'] = "0..00.";
  charMap['e'] = "0...0.";
  charMap['f'] = "00.0..";
  charMap['g'] = "00.00.";
  charMap['h'] = "00..0.";
  charMap['i'] = ".0.0..";
  charMap['j'] = ".0.00.";
  charMap['k'] = "0.0...";
  charMap['l'] = "000...";
  charMap['m'] = "0.00..";
  charMap['n'] = "0.000.";
  charMap['o'] = "0.0.0.";
  charMap['p'] = "0000..";
  charMap['q'] = "00000.";
  charMap['r'] = "000.0.";
  charMap['s'] = ".000..";
  charMap['t'] = ".0000.";
  charMap['u'] = "0.0..0";
  charMap['v'] = "000..0";
  charMap['w'] = ".0.000";
  charMap['x'] = "0.00.0";
  charMap['y'] = "0.0000";
  charMap['z'] = "0.0.00";
  charMap['.'] = ".0..00";
  charMap[','] = ".0....";
  charMap[';'] = ".00...";
  charMap['-'] = "..0..0";
  charMap['!'] = ".00.0.";
  charMap['?'] = ".00..0";
  charMap['('] = ".00.00";
  charMap[']'] = ".00.00";
  map<char,string>::iterator it;
  it = charMap.find(ch);
  if(it != charMap.end()) {
    strcpy(braille, (it->second).c_str());
    return true;
  }
  return false;
}

int encode(const char* plaintext, char* braille){

  if(*plaintext == '\0') {
    *braille = '\0';
    return 0;
  }
  int stage = encode_character(*plaintext, braille);

  int remainder = encode(++plaintext, braille + strlen(braille));
  
  return remainder + stage;
}

void print_braille(const char* plaintext, ostream& output){

  char braille[strlen(plaintext) * 12];
  int len = encode(plaintext, braille), j;
  for(int i = 0; i < 3; ++i) {
    j = i;
    while(j < len) {
      output << *(braille + j);
      output << *(braille + j + 3);
      output << ' ';
      j += 6;
    }
    output << endl;
  }

  while(*plaintext != '\0') {
    
    if(isupper(*plaintext) || isdigit(*plaintext)) {
      output << "   ";
    }
    
    output << *plaintext << "  ";
    ++plaintext;
  }
  
}
