#include "multitap.h"
#include <iostream>
#include <cctype>
#include <cmath>
using namespace std;

int encode_character(const char ch, char* multitap) {

  int numP = 1, num;
  
  if(isupper(ch) != 0) {
    *multitap = '#';
    return numP + encode_character(tolower(ch), ++multitap);
  }

  if(isdigit(ch) != 0) {
    *multitap = '*';
    ++multitap;
    num = ch;
    numP = 2;
  } else if(ispunct(ch, numP) != 0) {
    num = '1';
  } else if(ch == ' ')
    num = '0';
  else if(islower(ch) != 0) {
    num = lowerEncode(ch, numP);
  }

  for(int i = 0; i < numP; ++i)
    *(multitap + i) = num;

  *(multitap + numP) = '\0';

  return numP;
}

char lowerEncode(const char ch, int& nP) {

  if(ch <= 'o') {
    nP = (ch - 'a') % 3 + 1;
    return ceil((ch - 'a') / 3) + '2';
  } else if (ch <= 's') {
    nP = (ch - 'p') % 4 + 1;
    return '7';
  } else if (ch <= 'v') {
    nP = (ch - 't') % 3 + 1;
    return '8';
  } else {
    nP = (ch - 'w') % 4 + 1;
    return '9';
  }
}

bool ispunct(const char ch, int& nP) {
  
  char punct[4] = {'!', '?', '.', ','};
  
  for(int i = 0; i < 4; ++i) {
    if(ch == punct[i]) {
      nP = i + 1;
      return true;
    }
  }
  return false;
}

int encode(const char* plaintex, char* multitap) {

  return  encode(plaintex, multitap, true, false);
  
}

int encode(const char* plaintex, char * multitap, bool first, bool inCap) {

  char current, last, temp[10];
  int extra = 0;
  bool stillInCap;
  
  if(*plaintex == '\0') {
    *multitap = '\0';
    return 0;
  }

  if(isupper(*plaintex))
    stillInCap = true;
  
  if(inCap && stillInCap)
    current = tolower(*plaintex);

  if(inCap && islower(*plaintex)) {
    *multitap = '#';
    ++multitap;
    ++extra;
  }

  int stage = encode_character(*plaintex, temp);

  if(!first) {
    last = *(multitap -1);
    if(last == *temp) {
      *multitap = '|';
      ++multitap;
      ++extra;
    }
  }

  for(int i = 0; i < stage; ++i)
    *(multitap + i) = *(temp + i);
    
  int next = encode(++plaintex, multitap + stage, false, stillInCap);

  return next + extra + stage;
}
