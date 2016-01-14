#ifndef BRAILLE_H
#define BRAILLE_H

#include<iostream>
using namespace std;

int encode_character(char ch, char* braille);

int encode(const char* plaintext, char* braille);

bool encode_alpha_punc(char ch, char* braille);
bool encode_num(char ch, char* braille);

void print_braille(const char* plaintext, ostream& output);

#endif
