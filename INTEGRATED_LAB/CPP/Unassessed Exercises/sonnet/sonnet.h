/********************************************************************
 * MSc Lab Exam 2011-2012 Sonnet
 * Header File: sonnet.h
 * Author: Chris Snowden (cps15)
 * Last Modified: 08/01/16
 *******************************************************************/

// RESET is a constant used by function rhyming_letter(...)
#define RESET NULL

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int number, char *output_word);

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending);

/* Returns the number of words the string line*/
int count_words(const char* line);

/* Uses the phonetic dictionary dictionary.txt to construct the
   phonetic ending of the uppercase word contained in word. If the
   word is found in dictionary.txt, the phonetic ending is stored in
   phonetic_ending and the fuction returns true, else it returns
   false*/
bool find_phonetic_ending(const char* word, char* phonetic_ending);

/* Produces the output parameter scheme which is the rhyming scheme
   for the sonnet contained in the file filename. If the file does not
   exist, the function returns false*/
bool find_rhyme_scheme(const char* filename, char* scheme);

/* Returns the the rhyming scheme:
   "Shakespearean",
   "Petrarchan",
   "Spenserian" or
   "Unknown" for the sonnet in file filename*/
const char* identify_sonnet(const char* filename);

/* Retruns the phonetic ending from the dictionary entry line by
   concatinating the last phoneme of the word which contains a vowel
   with all subsequent phonemes of the word*/
void getPhoneticEnding(const char* line, char* phonetic_ending);

void lineToUpper(char* line);

bool containsVowel(const char* word);
