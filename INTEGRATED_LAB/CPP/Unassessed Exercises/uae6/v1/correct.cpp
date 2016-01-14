#include <iostream>
#include "correct.h"
using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary);

/* converts a binary string representation into a character */
char binary_to_ascii(char *binary);

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */
void text_to_binary(const char* str, char* binary){

  if(*str == '\0')
    return;

  char temp[9];
  ascii_to_binary(*str, temp);
  strcat(binary,temp);
  text_to_binary(++str, binary);
}
void binary_to_text(char* binary, char* str){

  if(*binary == '\0') {
    *str = '\0';
    return;
  }
  
  *str++ = binary_to_ascii(binary);
  binary_to_text(binary + 8,str);
}
void add_error_correction(const char* data, char* corrected){

  if(*data == '\0') {
    *corrected = '\0';
    return;
  }

  int d1 = data[0];
  int d2 = data[1];
  int d3 = data[2];
  int d4 = data[3];

  char c1 = parity(d1, d2, d4);
  char c2 = parity(d1, d3, d4);
  char c3 = parity(d2, d3, d4);
  
  corrected[0] = c1;
  corrected[1] = c2;
  corrected[2] = d1;
  corrected[3] = c3;
  corrected[4] = d2;
  corrected[5] = d3;
  corrected[6] = d4;

  add_error_correction(data + 4, corrected + 7);
  
}

char parity(int d1, int d2, int d3){
  return ((d1 + d2 + d3) % 2) == 0? '0': '1';
}

int parity(int d1, int d2, int d3, int d4){
  return ((d1 + d2 + d3 + d4) % 2) == 0? 0: 1;
}

int decode(char* received, char* decoded){

  if(*received == '\0') {
    *decoded = '\0';
    return 0;
  }

 
  int b1 =  received[0];
  int b2 =  received[1];
  int b3 =  received[2];
  int b4 =  received[3];
  int b5 =  received[4];
  int b6 =  received[5];
  int b7 =  received[6];

  int p1 = parity(b4, b5, b6, b7);
  int p2 = parity(b2, b3, b6, b7);
  int p3 = parity(b1, b3, b5, b7);

  int error = 0;
  int loc = 0;
  if(p1 != 0 || p2 != 0 || p3 != 0) {
    int loc = 4 * p1 + 2 * p2 + p3 - 1;
    error = 1;
    received[loc] = received[loc] == '0' ? '1' : '0';
  }
  
  decoded[0] = received[2];
  decoded[1] = received[4];
  decoded[2] = received[5];
  decoded[3] = received[6];

  if(error)
    received[loc] = received[loc] == '0' ? '1' : '0';
  
  return decode(received + 7, decoded + 4) + error;
}
