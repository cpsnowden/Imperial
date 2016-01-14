#include <iostream>
#include "substring.h"

using namespace std;

int main() {
  
  char some[9];
  some[0] = 'A';
  some[1] = 'Q';

  cout << &some[0] << endl;
  cout << &some[1] << endl;

  cout << substring_position("this", "this is a simple exercise") << endl;
  cout << substring_position("is", "this is a simple exercise") << endl;
  cout << substring_position("is a", "this is a simple exercise") << endl;
  cout << substring_position("is an", "this is a simple exercise") << endl;
  cout << substring_position("exercise", "this is a simple exercise") << endl;
  cout << substring_position("simple exercise", "this is a simple") << endl;
  cout << substring_position("", "this is a simple exercise") << endl;
  cout << substring_position("", "") << endl;
  return 0;
}
