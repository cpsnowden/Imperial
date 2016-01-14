/********************************************************
 * MSc C++ Programming Unassessed Exercise 1 - Substring
 * Implementation File - substring.c
 * Author - Chris Snowden (cps15) (23mins)
 ********************************************************/

#include <cstring>
using namespace std;

#include "substring.h"

bool is_prefix(const char* prefixStr, const char* str){

  return *prefixStr == '\0' ||
    ((*prefixStr == *str) && is_prefix(++prefixStr, ++str));

}

int substring_position(const char* subStr, const char* str){

  if(*str == '\0' && *subStr != '\0')
    return -1;

  if(is_prefix(subStr,str))
    return 0;

  int s = substring_position(subStr, ++str);
  return (s < 0) ? -1 : s + 1;

}

int substring_position2(const char* a, const char* s){

  return strstr(s,a)?strstr(s,a)-s:-1;

}

