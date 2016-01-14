/******************************************************
 * MSc C++ Programming Unassessed Exercise 3 Palindrome
 * Header File: words.h
 * Author: Chris Snowden (cps15)
 * Last Modified: 07/01/16
 *****************************************************/

/*Results in str2 being a reversed copy of str1. Ensure that str2 has sufficient
  memory to hold the reversed contents of str1*/
void reverse(const char* str1, char* str2);

/*Compares two strings. Returns true if both strings are the same ignoring
  punctuation and letter case*/
bool compare(const char* one, const char* two);

/*Returns true if the sentence is a palindrome*/
bool palindrome(const char* sentence);

/*Returns true if str1 is an anagram of str2*/
bool anagram(const char* str1, const char* str2);

/*Performs in-place sort of str, ignoring case*/
void sort(char* str);

/*Swaps character one and two*/
void swap(char& one, char& two);
