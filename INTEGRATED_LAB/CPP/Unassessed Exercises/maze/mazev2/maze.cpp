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
  
  // ifstream input(filename);
  ifstream input;
  input.open(filename);

  if (input.fail()) {
    cerr << "couldn't open file" << endl;
    return false;
  }

  height = width = 0;

  input.getline(line,512);  

  cerr << "succeeded in extracting data from file" << endl;

  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  cerr << "dimensions: " << height << ", " << width << endl;

  if (height > 0) {
    cerr << "(get_maze_dimensions) all good, about to return true" << endl;
    return true;
  }
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  cerr << "starting load maze" << endl;

  bool success = get_maze_dimensions(filename, height, width);

  cerr << "dimensions of this maze: " << height << ", " << width << endl;
  
  if (!success) {
    cerr << "couldn't get hold of this maze's dimensions!" << endl;
    return NULL;
  }

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }

  input.close();  

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

bool find_marker(char ch, char** maze, int height, int width, int& row, int& column){
  
  for(row = 0; row < height; ++row)
    for(column = 0; column < width; ++column)
      if(maze[row][column] == ch)
	return true;

  row = column = -1;
  return false;
  
}

bool valid_solution(const char* path, char** maze, int height, int width){

  int row, col, endRow, endCol;
  
  if(!find_marker('>', maze, height, width, row, col))
    return false;
  if(!find_marker('X', maze, height, width, endRow, endCol))
    return false;
  
  while(*path != '0') {
    if(row == endRow && col == endCol)
      return true;

    if(!move(*path++, maze, height, width, row, col))
      return false;
  }

  return false;
  
}

bool move(char dir, char** maze, int height, int width, int& row, int& col) {

  switch(dir) {
  case 'N':
    --row;
    break;
  case 'S':
    ++row;
    break;
  case 'E':
    ++col;
    break;
  case 'W':
    --col;
    break;
  default:
    cerr << "Invalid character " << dir << " found" << endl;
  }
    
  if(!inBound(height, row) || !inBound(width, col))
    return false;

  if(maze[row][col] == '|' ||
     maze[row][col] == '-' ||
     maze[row][col] == '.' ||
     maze[row][col] == '+' ||
     maze[row][col] == '#')
    return false;
  
  return true;
}

bool inBound(int max, int ind) {
  return ind >= 0 && ind < max;
}

void clearNoSteps(char** maze, int height, int width) {
  for(int r = 0; r < height; ++r)
    for(int c = 0; c < width; ++c)
      if(maze[r][c] == '.')
	maze[r][c] = ' ';
}

char* find_path(char** maze, int height, int width, char start, char end){

  static char ns[12] = "no solution";
  int row, col, endRow, endCol;
  
  if(!find_marker(start, maze, height, width, row, col))
    return ns;
  if(!find_marker(end, maze, height, width, endRow, endCol))
    return ns;

  static char path[200];
  if(!isSolution(maze, path, height, width, row, col, endRow, endCol))
    return ns;

  clearNoSteps(maze, height, width);
  
  return path;
  
}

bool isSolution(char** maze, char* path, int height, int width, int row, int col, int endRow, int endCol){
  if(row == endRow && col == endCol) {
    *path = '\0';
    return true;
  }

  int trialRow = row, trialCol = col;
  char directions[5] = "ENSW";
  char *dir, *tempPath = path;
  int i = 0;
  for(dir = directions; *dir != '\0'; ++dir) {
    if(move(*dir, maze, height, width, row, col)) {
      *path = *dir;
      if(row != endRow || col != endCol)
	maze[row][col] = '#';
      if(isSolution(maze, ++path, height, width, row, col, endRow, endCol))
	return true;
      path = tempPath;
     
    }
    row = trialRow;
    col = trialCol;
    ++i;
  }
  
  maze[row][col] = '.';
  return false;
  
}
