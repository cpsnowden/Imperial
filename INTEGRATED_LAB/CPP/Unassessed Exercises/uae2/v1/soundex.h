#ifndef SOUNDEX_H
#define SOUNDEX_H

void encode(const char* surname, char* soundex);

bool compare(const char* one,const char* two);

int count(const char* surname, const char* sentence);

bool character_map(const char character, const char* soundexMap);

char character_code(const char* surname);
#endif
