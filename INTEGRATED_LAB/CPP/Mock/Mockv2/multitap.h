/*********************************************************
 * MSc Mock C++ Lab Exam 2015
 * Multitap
 * Header File: multitap.h
 * Author: Chris Snowden (cps15)
 * Last Modified: 11/01/16
 *********************************************************/

#ifndef MULTITAP_H
#define MULTITAP_H

const char keypad[10][5] = {" ",
			    ".,!?",
			   "abc",
			   "def",
			   "ghi",
			   "jkl",
			   "mno",
			   "pqrs",
			   "tuv",
			   "wxyz"};


/*Encodes a single character ch in Multitap format as string multitap, returning
  the length of the multitap encoding*/
int encode_character(char ch, char* multitap);

/*Encodes plaintext in Multitap format as multitap*/
void encode(const char* plaintext, char* multitap);

char findOnKeyPad(char ch, int& presses);

bool ispunct(char ch); 
#endif
