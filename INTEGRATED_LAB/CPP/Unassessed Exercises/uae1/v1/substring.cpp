#include "substring.h"
#include <cstring>
using namespace std;

int substring_position2(const char* substr, const char* str){
  return str -1 - strstr(str,substr);
}

int substring_position(const char* substr, const char* str){
  if(is_prefix(substr, str))
    return 0;
  else if(*str == '\0')
    return -1;
  else {
    int rec_count = substring_position(substr, ++str); 
    if(rec_count != -1)
      return rec_count + 1;
    return -1;
  }
}

bool is_prefix(const char* substr, const char* str) {
  
  if((*str == '\0') && (*substr != '\0'))
    return false;
  
  bool prefix_check = (*substr == '\0') || ((*substr == *str) && is_prefix(++substr, ++str));
  
  if(prefix_check)
      return true;

  return false;
}
