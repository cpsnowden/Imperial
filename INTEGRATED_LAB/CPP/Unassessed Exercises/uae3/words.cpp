#include "words.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

void reverse(const char* str1, char* str2) {

  int len = strlen(str1);
  
  *(str2 + len) = '\0';
  
  for(int i = len - 1; i >= 0; --i)
    *(str2 + i) = *(str1 + len - 1 - i);

}

bool compare(const char* one, const char* two){
  
 

  while(isalpha(*one) == 0 && *one != '\0')
    ++one;

  while(isalpha(*two) == 0 && *two != '\0')
    ++two;

  if(*one == '\0' && *two == '\0')
    return true;
  
  if(*one == '\0' || *two == '\0')
    return false;
  
  if(toupper(*one) != toupper(*two))
    return false;

  return compare(++one,++two);
  
}

bool palindrome(const char* sentence){

  int len = strlen(sentence);
  ++len;
  bool isTrue = false;
  char* reversed = new char[len];

  reverse(sentence, reversed);
  isTrue = compare(sentence, reversed);
  
  delete[] reversed;
  
  return isTrue;
}

bool anagram(const char* str1, const char* str2){

  int len1 = strlen(str1) + 1;
  int len2 = strlen(str2) + 1;
  
  char* sorted1 = new char[len1];
  char* sorted2 = new char[len2];
  sortString(str1, sorted1);
  sortString(str2, sorted2);
 
  bool isTrue = compare(sorted1, sorted2);
  delete [] sorted1;
  delete [] sorted2;

  return isTrue;
}

void sortString(const char* str, char* str1) {

  char temp;
  strcpy(str1,str);
  int len = strlen(str1);
  int i, j;

  for(i = 0; i < len - 1; ++i) {
    for(j = i + 1; j < len; ++j) {
      if(toupper(str1[i]) < toupper(str1[j])) {
	temp = str1[i];
	str1[i] = str1[j];
	str1[j] = temp;
      }
    }
  }
}
