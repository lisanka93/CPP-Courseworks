//Lisa Chalaguine
//C++ LABwork


//given functions
void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);


//my functions
bool is_complete(char board[9][9]);
bool make_move(char position[], char digit, char board[9][9]);
bool save_board(const char *filename2, char board[9][9]);

bool solve_board(char board[9][9]);
bool solve_board(char board[9][9], int &counter); //overloaded function with a counter
bool find_free_spot(char board[9][9], int &row, int &col);
bool safe_move(char board[9][9], int row, int col, char num);
