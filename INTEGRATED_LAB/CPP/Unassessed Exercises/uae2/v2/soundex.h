/*****************************************************
 * MSc C++ Programming Unassessed Exercise 2 - Soundex
 * Header File - soundex.h
 * Author - Chris Snowden (cps15)
 * Last Modified - 07/01/15
 ****************************************************/

const char mapping[6][9] = {"bfpv",
			    "cgjkqsxz",
			    "dt",
			    "l",
			    "mn",
			    "r"};

/* Encodes surname using the Soundex encoding system as soundex*/
void encode(const char* surname, char* soundex);

/* Compares two Soundex codes, if they are the same return true, else false*/
bool compare(const char* one, const char* two);

/* Returns true if valid mapping of c to the Soundex digit, s is updated to
   null terminated string with first character as Soundex digit*/
bool getMapping(char c, char& s);

/* Retruns the number of words in a given sentence that hve the same Soundex
   encoding as surname*/
int count(const char* surname, const  char* sentence);

