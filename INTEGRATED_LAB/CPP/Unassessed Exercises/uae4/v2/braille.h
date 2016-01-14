/**********************************************************
 * MSc Computing Science Unassessed Exercise 4 Braille
 * Header File: braille.h
 * Author: Chris Snowden (cps15)
 * Last Modified: 07/01/16
 *********************************************************/

#include <iostream>
using namespace std;

const int len = 6;
const char simpleMap[20][len + 1] = {"0.....", //a
				     "00....", //b
				     "0..0..", //c
				     "0..00.", //d
				     "0...0.", //e
				     "00.0..", //f
				     "00.00.", //g
				     "00...0", //h
				     ".0.0..", //i
				     ".0.00.", //j
				     ".....0", //Cap
				     "..0000", //Num
				     ".0.0..", //.
				     ".0....", //,
				     ".00...", //;
				     "..0..0", //-
				     ".00.0.", //!
				     ".00..0", //?
				     ".00.00", // ( or )
				     "......"}; //default

/*Encodes the character c using Braille as braille*/
int encode_character(char c, char* braille);

/*Encodes the punctuation character c using Braille as braille*/
int encode_punct(char c, char* braille);

/*Encodes the plaintext using Braille as braille*/
void encode(const char* plaintext, char* braille);

/*Writes the Braille representation of the plaintext to output stream output*/
void print_braille(const char* plaintext, ostream& output);
