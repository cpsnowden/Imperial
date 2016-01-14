#ifndef CORRECT_H
#define CORRECT_H

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(char *binary);
char parity(int d1, int d2, int d3);
int parity(int d1, int d2, int d3, int d4);
void text_to_binary(const char* str, char* binary);
void binary_to_text(char* binary, char* str);
void add_error_correction(const char* data, char* corrected);
int decode(char* received, char* decoded);

#endif
