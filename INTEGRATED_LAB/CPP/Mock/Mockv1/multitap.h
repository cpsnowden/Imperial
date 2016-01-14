#ifndef MULTITAP_H
#define MULTITAP_H

int encode_character(const char ch, char* multitap);

int encode(const char* plaintex, char* multitap);

int encode(const char* plaintex, char * multitap,
		    bool first, bool inCap);

bool ispunct(const char ch, int& nP);

char lowerEncode(const char ch, int& nP);

#endif
