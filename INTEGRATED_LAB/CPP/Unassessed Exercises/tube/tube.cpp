#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
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

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}

bool get_symbol_position(char** map, int height, int width, char target, int& r, int&c){

  for( r = 0; r < height; ++r ) {
    for( c = 0; c < width; ++c ) {
      if(map[r][c] == target)
	return true;
    }
  }

  r = -1;
  c = -1;
  return false;

}

char get_symbol_for_station_or_line(const char* name){

  char c;
    
  if(get_symbol(name, "lines.txt", c))
    return c;
  
  get_symbol(name, "stations.txt", c);
  return c;
}

bool get_symbol(const char* name, const char* fName, char& c) {

  ifstream i_stream;
  i_stream.open(fName);
  char line[30];
  
  for(i_stream.getline(line, 30); i_stream; i_stream.getline(line, 30)) {
    if(!strcmp(line + 2, name)) {
      c = *line;
      i_stream.close();
      return true;
    }
  }
    i_stream.close();
    c = ' ';
    return false;
}

bool get_name(char* name, const char* fName, char c){
  ifstream i_stream;
  i_stream.open(fName);
  char line[30];
  
  for(i_stream.getline(line, 30); i_stream; i_stream.getline(line, 30)) {
    if(*line == c) {
      strcpy(name, line + 2);
      i_stream.close();
      return true;
    }
  }
  i_stream.close();
  name = NULL;
  
  return false;
}

int validate_route(char** map, int height, int width, const char* station, char* route, char* destination){

  int pRow = -1, pCol = -1, cRow = -1, cCol = -1, p2Row = -1, p2Col = -1, lineChanges = -1;
  char pPos = ' ', cPos, p2Pos = ' ';
  Direction direction;
  cPos = get_symbol_for_station_or_line(station);
  
  if(!isalnum(cPos) || !get_symbol_position(map, height, width, cPos, cRow, cCol))
    return ERROR_START_STATION_INVALID;
  
  char* d = strtok(route, " ,");
  while(d != NULL) {

    p2Row = pRow;
    p2Col = pCol;
    p2Pos = pPos;
    pRow = cRow;
    pCol = cCol;
    pPos = cPos;
    
    direction = string_to_direction(d);
    int state = valid_move(map, height, width, direction, cRow, cCol, cPos);
    if(state < 0)
      return state;
    
    if(!isalnum(pPos) && p2Row == cRow && p2Col == cCol)
      return ERROR_BACKTRACKING_BETWEEN_STATIONS;
    if(isalnum(pPos) && ispunct(cPos))
      ++lineChanges;

    d = strtok(NULL, " ,");
  }

  
  if(!get_name(destination, "stations.txt", cPos))
    return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;
  
  return lineChanges;
}

int valid_move(char** map, int height, int width, Direction dir, int& r, int& c , char& pos) {

  char last = pos;
  
  switch(dir) {
  case N:
    --r;
    break;
  case NE:
    --r;
    ++c;
    break;
  case E:
    ++c;
    break;
  case SE:
    ++c;
    ++r;
    break;
  case S:
    ++r;
    break;
  case SW:
    ++r;
    --c;
    break;
  case W:
    --c;
    break;
  case NW:
    --r;
    --c;
    break;
  case END:
    return 0; 
    break;
  default:
    return ERROR_INVALID_DIRECTION;
  }

  if(r < 0 || r > height || c < 0 || c > width) {
    return ERROR_OUT_OF_BOUNDS;
  }

  pos = map[r][c];

  if(pos == ' ')
    return ERROR_OFF_TRACK;
  
  if(!isalnum(last) && !isalnum(pos) && pos != last)
    return ERROR_LINE_HOPPING_BETWEEN_STATIONS;

  return 0;
}
