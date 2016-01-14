#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include "maze.h"
using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}


bool find_marker(char c, char** maze, int height, int width, int& row, int& column){

  for(row = 0; row < height; ++row) {
    for(column = 0; column < width; ++column) {
      if(maze[row][column] == c) {
	return true;
      }
    }
  }

  row = -1;
  column = -1;
  return false;
}

bool valid_solution(const char* path, char** maze, int height, int width){
  
  int startRow, startCol, endRow, endCol;

  if(!find_marker('>', maze, height, width, startRow, startCol))
    return false;
  if(!find_marker('X', maze, height, width, endRow, endCol))
    return false;


  if(!validPath(path, maze, height, width, 
		startCol, startRow,
		endCol, endRow))
    return false;

  return true;
}

bool validPath(const char* path, char** maze, int height, int width,
	       int fromCol, int fromRow,
	       int toCol, int toRow){
  // cout << *path << endl;
  if(fromCol == toCol && fromRow == toRow)
    return true;

  if(*path == '\0' || !validMove(*path, maze, height, width, fromCol, fromRow))
    return false;

  return validPath(++path, maze, height, width, fromCol, fromRow, toCol, toRow);
}

bool validMove(char c, char** maze, int height, int width, int& fromCol, int& fromRow){

  switch(c) {
  case 'N':
    --fromRow;
    break;
  case 'S':
    ++fromRow;
    break;
  case 'E':
    ++fromCol;
    break;
  case 'W':
    --fromCol;
    break;
  default:
    return false;
    break;
  }

  if(!isValidCoordinate(height, width, fromRow, fromCol)) {
    // cout << "Invalid coordinate: " << fromRow << fromCol << endl;
     return false;
  }  
  if(isHedge(maze[fromRow][fromCol])) {
    // cout << "Found hedge" << endl;
    return false;
  }
  if(maze[fromRow][fromCol] == '.' || maze[fromRow][fromCol] == '#')
    return false;

  return true;
}
  
bool isValidCoordinate(int height, int width, int row, int col) {

  if( row >= 0 && row < height && col >= 0 && col < width)
    return true;
  return false;
}

bool isHedge(char c) {
  if( c == '|' || c == '-' || c == '+')
    return true;
  return false;
}

const char* find_path(char** maze, int height, int width, char start, char end){

  int startRow, startCol, endRow, endCol;

  if(!find_marker(start, maze, height, width, startRow, startCol))
    return no_path_found();
  if(!find_marker(end, maze, height, width, endRow, endCol))
    return no_path_found();

  char* path = new char[100];
  
  if(!rec(maze, path, startRow, startCol, endRow, endCol, height, width))
    return no_path_found();

  return path;

}

bool rec(char** maze, char* path, int row, int col, int endRow, int endCol, int height, int width) {

  // print_maze(maze,9,9);

  if(col == endCol && row == endRow) {
    *path = '\0';
    return true;
  }

  int tempRow = row, tempCol = col;
  char* tempPath = path;
  char directions[5] = "NESW";

  for(int i = 0; i < 4; ++i) {
    if(validMove(directions[i], maze, height, width, tempCol, tempRow)) {
      maze[tempRow][tempCol] = '#';
      *path = directions[i];
      if(rec(maze, ++tempPath, tempRow, tempCol, endRow, endCol, height, width))
	return true;
    }
    
    tempRow = row;
    tempCol = col;
    tempPath = path;
  }
  maze[row][col] = '.';
  return false;
}

const char* no_path_found() {
  char* error = new char[12];
  strcpy(error,"no solution");
  return error;
}


