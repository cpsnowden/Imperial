enum MoveResult {INVALID_MOVE = -3, REDUNDANT_MOVE, BLOWN_UP, SOLVED_BOARD, VALID_MOVE};
enum Opinion{NO_MINE, MINE, UNKNOWN};

void load_board(const char *filename, char board[9][9]);
void display_board(char board[9][9]);
void initialise_board(char board[9][9]);

bool is_complete(const char mines[9][9], const char revealed[9][9]);

int count_mines(const char position[3], const char mines[9][9]);

MoveResult make_move(const char* postion, const char mines[9][9], char revealed[9][9]);

bool find_safe_move(const char revealed[9][9], char* move);

bool getCoordinates(const char* position, int& r, int& c);

bool validRC(int r, int c);

Opinion squaresOpinion(int r, int c, int onR, int onC, const char revealed[9][9]);

bool getNextSquare(char prev[3], char next[3]);
