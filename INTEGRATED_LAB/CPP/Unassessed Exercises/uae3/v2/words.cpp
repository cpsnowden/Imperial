/******************************************************
 * MSc C++ Programming Unassessed Exercise 3 Palindrome
 * Implementation File: words.cpp
 * Author: Chris Snowden (cps15)
 * Last Modified: 07/01/16 34mins
 *****************************************************/

#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

#include "words.h"

void reverse(const char* str1, char* str2){

  int n = strlen(str1);

  for(int i = 0; i < n; ++i)
    str2[i] = str1[n - 1 - i];
  
  str2[n] = '\0';
}

bool compare(const char* one, const char* two){

  if(*one == '\0' && *two == '\0')
    return true;

  if(isalpha(*one) && isalpha(*two)) {
    if(tolower(*one) != tolower(*two))
      return false;
    else {
      ++one;
      ++two;
    }
  }

  if(!isalpha(*one) && *one != '\0')
    ++one;
  if(!isalpha(*two) && *two != '\0')
    ++two;

  return compare(one, two);
}


bool palindrome(const char* sentence){

  int n = strlen(sentence);
  char* reversed = new (nothrow) char[n + 1]; //allocate new array with space for sentinal
  if(!reversed)
    cerr << "Memory fault, could allocate memory for reversed array" << endl;

  reverse(sentence, reversed);
  return compare(sentence, reversed);
}

bool anagram(const char* str1, const char* str2){

  int n1 = strlen(str1);
  int n2 = strlen(str2);
  char* sort1 = new (nothrow) char[n1 + 1]; //allocate new array with space for sentinal
  char* sort2 = new (nothrow) char[n2 + 1]; //allocate new array with space for sentinal

  if(!sort1 || !sort2)
    cerr << "Memory fault, could allocate memory for reversed array" << endl;

  strcpy(sort1, str1);
  strcpy(sort2, str2);
 
  sort(sort1);
  sort(sort2);

  return compare(sort1, sort2);

  
}

void sort(char* str1){

  int n = strlen(str1);
  for(int i = 0; i < n; ++i) {
    for(int j = i + 1; j < n; ++j) {
      if(tolower(str1[i]) > tolower(str1[j]))
	swap(str1[i], str1[j]);
    }
  }

  str1[n] = '\0';

}

void swap(char& one, char& two){
  char temp = one;
  one = two;
  two = temp;
}
