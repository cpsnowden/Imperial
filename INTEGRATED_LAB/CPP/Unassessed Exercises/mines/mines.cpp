#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include "mines.h"
using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a maze from a file*/
void load_board(const char *filename, char board[9][9]) {

  ifstream input(filename);

  char line[512];

  for (int r = 0; r<9; r++) {
    input.getline(line, 512);
    strcpy(board[r], line);
  }
  input.close();
}

/* pre-supplied function to print a maze */
void display_board(char board[9][9]) {
  cout << setw(4) << " " << "  ";
  for (int c=0; c<9; c++)
    cout << (c +1 % 9);
  cout << endl;

  for (int r=0; r<9; r++) {
    cout << setw(4) << (char) (r + 'A') << " |";    
    for (int c=0; c<9; c++) 
      cout << board[r][c];
    cout << endl;
  }
}

void initialise_board(char board[9][9]) {
  for(int i = 0; i < 9; ++i)
    for(int j = 0; j < 9; ++j)
      board[i][j] = '?';
}

bool is_complete(const char mines[9][9], const char revealed[9][9]){

  for(int r = 0; r < 9; ++r)
    for(int c = 0; c < 9; ++c)
      if(revealed[r][c] == '?') {
	if(mines[r][c] != '*')
	  return false;
      }
  return true;
}

bool validRC(int r, int c) {
  return r >= 0 && r < 9 && c >=0 && c <9;
}

bool getCoordinates(const char* position, int& r, int& c){

  if(strlen(position) < 2)
    return false;

  int tempr = position[0] - 'A';
  int tempc = position[1] - '1';

  if(!validRC(tempr,tempc))
    return false;

  r = tempr;
  c = tempc;
  return true;
}

int count_mines(const char position[3], const char mines[9][9]){

  int r, c, adjR, adjC, numMines = 0;
  
  if(!getCoordinates(position, r, c))
    return 0;

  for(int rowDisp = -1; rowDisp <= 1; ++rowDisp){
    for(int colDisp = -1; colDisp <= 1; ++colDisp) {
      if(colDisp == 0 && rowDisp == 0)
	continue;
      adjR = r + rowDisp;
      adjC = c + colDisp;
      if(validRC(adjR, adjC))
	if(mines[adjR][adjC] == '*')
	  ++numMines;
    }
  }
  return numMines;
}

MoveResult make_move(const char* position, const char mines[9][9], char revealed[9][9]){

  int r, c, adjR, adjC, n;
  bool flag = false;
  char adj[3];
  
  if(!getCoordinates(position, r, c))
    return INVALID_MOVE;
  
  if(strlen(position) == 3) {
    if(position[2] != '*')
      return INVALID_MOVE;
    flag = true;
  }

 
  if(flag) {
    if(revealed[r][c] == '*')
      return REDUNDANT_MOVE;
    revealed[r][c] = '*';
    return VALID_MOVE;
  }

  if(revealed[r][c] != '?' && revealed[r][c] != '*')
    return REDUNDANT_MOVE;

  
  if(mines[r][c] == '*')
    return BLOWN_UP;

  if(!flag) {
    n = count_mines(position, mines);
    revealed[r][c] = (n==0) ? ' ' : ('0' + n);
    if(n == 0) {
      for(int rowDisp = -1; rowDisp <= 1; ++rowDisp){
	for(int colDisp = -1; colDisp <= 1; ++colDisp) {
	  if(colDisp == 0 && rowDisp == 0)
	    continue;
	  adjR = r + rowDisp;
	  adjC = c + colDisp;
	  if(validRC(adjR, adjC)) {
	    adj[0] = 'A' + adjR;
	    adj[1] = '1' + adjC;
	    adj[2] = '\0';
	    make_move(adj, mines, revealed);
	  }
	}
      }
    }
  }

  if(is_complete(mines, revealed))
    return SOLVED_BOARD;

  return VALID_MOVE;
  
}

bool find_safe_move(const char revealed[9][9], char* move){

  char current[3] = "A1", next[3];
  int r, c, adjR, adjC;
  
  while(true) {

    getCoordinates(current, r, c);

    if(revealed[r][c] == '?') {
     
    for(int rowDisp = -1; rowDisp <= 1; ++rowDisp){
      for(int colDisp = -1; colDisp <= 1; ++colDisp) {
	if(colDisp == 0 && rowDisp == 0)
	  continue;
	adjR = r + rowDisp;
	adjC = c + colDisp;
	if(validRC(adjR, adjC)) {
	  Opinion op = squaresOpinion(adjR, adjC, r, c, revealed);
	  if(op != UNKNOWN) {
	    strcpy(move, current);
	    if(op == MINE) {
	      strcat(move, "*");
	    }
	  return true;
	  }
	}
      }
    }
    }
    if(!getNextSquare(current, next))
      break;

    strcpy(current, next);
  }
  
  return false;
  
}


Opinion squaresOpinion(int r, int c, int onR, int onC, const char revealed[9][9]){

  char n = revealed[r][c];
  int num = n - '0';
  int unfound = num;
  int pos = num;
  int adjR, adjC;
  if(num < 0 && num > 8)
    return UNKNOWN;
  
  for(int rowDisp = -1; rowDisp <= 1; ++rowDisp){
      for(int colDisp = -1; colDisp <= 1; ++colDisp) {
	adjR = r + rowDisp;
	adjC = c + colDisp;
	if((colDisp == 0 && rowDisp == 0) || (adjR == onR && adjC == onC))
	  continue;
	if(validRC(adjR, adjC)) {
	  if(revealed[adjR][adjC] == '*') {
	    unfound--;
	    pos--;
	  }
	  if(revealed[adjR][adjC] == '?') {
	    pos--;
	  }
	}
      } 
  }
  if(unfound == 0)
    return NO_MINE;

  if(unfound  > 0 && pos == 1)
    return MINE;

  return UNKNOWN;
}

bool getNextSquare(char prev[3], char next[3]){

  int r, c;

  if(!getCoordinates(prev, r, c)) {
    return false;
  }
 
  if(c < 8) {
    ++c;
  } else {
    ++r;
    c = 0;
  }

  if(!validRC(r,c)) {
    return false;
  }
  next[0] = 'A' + r;
  next[1] = '1' + c;
  next[2] = '\0';
  return true;
  
  
}


