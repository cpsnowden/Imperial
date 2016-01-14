/********************************************************************
 * MSc Lab Exam 2011-2012 Sonnet
 * Implementation File: sonnet.cpp
 * Author: Chris Snowden (cps15)
 * Last Modified: 08/01/16
 *******************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>

using namespace std;

#include "sonnet.h"

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

/* START WRITING YOUR FUNCTION BODIES HERE */

int count_words(const char* line){

  int i, n = strlen(line);
  char* word = new (nothrow) char[n + 1];
  if(word == NULL)
    cerr << "Could not allocate " << n + 1 << "bytes on the heap" << endl;

  for(i = 1; get_word(line, i, word); ++i);
  return i - 1;
}

bool find_phonetic_ending(const char* word, char* phonetic_ending){

  ifstream i_stream;
  i_stream.open("dictionary.txt");
  if(!i_stream)
    cerr << "Could not open dictionary.txt" << endl;

  char line[200];
  int wLength = strlen(word);
  
  while(i_stream.getline(line, 200)) {
    if(!strncmp(line, word, wLength)) {
      getPhoneticEnding(line, phonetic_ending);
      i_stream.close();
      return true;
    }
 
  }
  i_stream.close();
  return false;
}

void getPhoneticEnding(const char* line, char* phonetic_ending) {

  char word[100];  
  int i, n = count_words(line);

  *phonetic_ending = '\0';
  
  for(i = n; i > 1; --i) {
    get_word(line, i, word);
    if(containsVowel(word))
      break;
  }
  
  for(; i <= n; ++i) {
    get_word(line, i, word);
    strcat(phonetic_ending,word);
  }
}

bool containsVowel(const char* word){
  if(strcspn(word, "AEIOU") == strlen(word))
    return false;
  return true;
}

bool find_rhyme_scheme(const char* filename, char* scheme){

  rhyming_letter(RESET);
  
  ifstream i_stream;
  i_stream.open(filename);
  if(!i_stream) {
    cerr << "Could not open " << filename << endl;
    return false;
  }
  char line[512], word[20], phonetic_ending[20], n;
  
  while(i_stream.getline(line, 512)) {
    lineToUpper(line);
    n = count_words(line);
    get_word(line, n, word);
    if(!find_phonetic_ending(word, phonetic_ending)) {
      cerr << "Could not find phonetic ending for " << word << endl;
      i_stream.close();
      return false;
    }
    *scheme++ = rhyming_letter(phonetic_ending);
  }
  *scheme = '\0';
  i_stream.close();
  
  return true;
}

void lineToUpper(char* line) {
  if(*line == '\0')
    return;

  *line = toupper(*line);
  lineToUpper(++line);
}

const char* identify_sonnet(const char* filename){

  static const char shk[14] = "Shakespearean";
  static const char pet[11] = "Petrarchan";
  static const char spe[11] = "Spenserian";
  static const char unk[8] = "Unknown";

  char scheme[100];
  
  find_rhyme_scheme(filename, scheme);

  if(!strcmp(scheme,"ababcdcdefefgg")) {
    return shk;
  } else if(!strcmp(scheme,"abbaabbacdcdcd")) {
    return pet;
  } else if(!strcmp(scheme,"ababbcbccdcdee")) {
    return spe;
  } else {
    return unk;
  }
}
