#include <iostream>
#include <cassert>
#include "mines.h"

using namespace std;

int main() {

  /* this section illustrates the use of the pre-supplied functions */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  char mines[9][9], revealed[9][9];

  load_board("mines.dat",mines);
  display_board(mines);

  initialise_board(revealed);
  display_board(revealed);

  cout << "====================== Question 1 ======================" << endl << endl;

  load_board("partial.dat",revealed);
  display_board(revealed);
  cout << "is ";
   if(!is_complete(mines, revealed))
     cout << "not ";
   cout << "complete" << endl;
  

   load_board("solution.dat",revealed);
   display_board(revealed);
   cout << "is ";
   if(!is_complete(mines, revealed))
     cout << "not ";
   cout << "complete" << endl;
  
  cout << "====================== Question 2 ======================" << endl << endl;
  
  load_board("mines.dat",mines);
  display_board(mines);

  cout << "Found " << count_mines("A7", mines) << " mine(s) around square 'A7'" << endl;

  cout << "Found " << count_mines("E5", mines) << " mine(s) around square 'E5'" << endl;
  
  cout << "Found " << count_mines("H9", mines) << " mine(s) around square 'H9'" << endl;

  cout << "====================== Question 3 ======================" << endl << endl;

 load_board("mines.dat",mines);
  display_board(mines);

  initialise_board(revealed);
  display_board(revealed);

  cout <<  make_move("B6", mines, revealed);
  display_board(revealed);
  cout << make_move("E5", mines, revealed);
  display_board(revealed);
  cout <<  make_move("H3*", mines, revealed);
  display_board(revealed);

  
  cout << "=================== Question 4 =====================" << endl << endl;

  load_board("mines.dat",mines);
  display_board(mines);
  load_board("partial.dat",revealed);
  display_board(revealed);

  cout << "Safe move sequence: " << endl;
  char move[512];
  while(find_safe_move(revealed, move)) {
    cout << move << " ";
    make_move(move, mines, revealed);
    cout << endl;
    display_board(revealed);
  }
  cout << endl;

  return 0;
}
