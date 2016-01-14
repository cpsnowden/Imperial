#include "Lemming.h"
#include "Direction.h"
#include "Room.h"
using namespace std;

int main() {

  Room r0("r0"), r1("r1"), r2("r2");
  r0.addRoomToLeft(&r1);
  r1.addRoomToLeft(&r2);

  Lemming* lala = new Lemming("Lala", &r0);
  Lemming* lilo = new Lemming("Lilo", &r2);
  
  lilo->wake();
  lilo->wake();
  lala->wake();

  Lemming::dLM = Left;
  
  lilo->wake();
  
  return 0;
}
