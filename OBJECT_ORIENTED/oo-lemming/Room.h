

#ifndef ROOM_H
#define ROOM_H

#include "Lemming.h"
#include <iostream>
#include <string>
using namespace std;

class Room {

public:
  string name;
  Room* rTL;
  Room* rTR;
  Room(string _name ,Room* _rTL = NULL, Room* _rTR = NULL):
    name(_name),
    rTL(_rTL),
    rTR(_rTR) {};
  
  bool addRoomToLeft(Room* _rTL) {
    if(rTL == NULL) {
      rTL = _rTL;
      (_rTL->rTR) = this;
      return true;
    } else {
      cout << "Already a room connected to the left" << endl;
      return false;
    }
  }

  bool addRommToRight(Room* _rTR) {
    if(rTR == NULL) {
      rTR = _rTR;
       (_rTR->rTL) = this;
      return true;
    } else {
      cout << "Already a room connected to the right" << endl;
      return false;
    }
  }
};




#endif
