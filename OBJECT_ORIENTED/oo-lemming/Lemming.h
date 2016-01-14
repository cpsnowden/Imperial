

#ifndef LEMMING_H
#define LEMMING_H

#include <string>
#include "Room.h"
#include "Direction.h"
using namespace std;

class Lemming {

private:
  string name;
  Room* inRoom;
  bool awake;
  
public:

  static Direction dLM;
  
  Lemming(string _name, Room* _room);

  bool move();
  bool wake();

};

#endif
