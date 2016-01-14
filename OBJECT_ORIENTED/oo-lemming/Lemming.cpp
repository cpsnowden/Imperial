
#include "Lemming.h"
#include "Direction.h"
#include <string>
#include <iostream>
using namespace std;


Direction Lemming::dLM = Right;

Lemming::Lemming(string _name, Room* _room) :
  name(_name),
  inRoom(_room),
  awake(false) {
  cout << name << " created in " << inRoom->name << endl;

};

bool Lemming::wake() {

  if(awake) {
    cout << name << " is already awake" << endl;
    return false;
  } else {
    awake = true;
    move();
    awake = false;
    return true;
  }
}

bool Lemming::move() {
  cout << name << " is in " << inRoom->name << " trying to move " << endl;
  switch(dLM) {
  case Left:
    if(inRoom->rTL != NULL) {
      inRoom = inRoom->rTL;
      cout << "moved " << printDirection(dLM) << " to " << inRoom->name << endl;
      return true;
    }
    else {
      cout << "No room to left" << endl;
      return false;
    }
    break;
  case Right:
    if(inRoom->rTR != NULL) {
      inRoom = inRoom->rTR;
      cout << "moved " << printDirection(dLM) << " to " << inRoom->name << endl;
      return true;
    }
    else {
      cout << "No room to right" << endl;
      return false;
    }
      break;
  }
};

