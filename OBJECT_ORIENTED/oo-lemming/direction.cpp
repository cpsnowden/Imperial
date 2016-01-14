
#include "direction.h"
using namespace std;

string printDirection(Direction direction) {

  switch(direction) {
  case Left:
    return "Left";
    break;
  case Right:
    return "Right";
    break;
  }
}
