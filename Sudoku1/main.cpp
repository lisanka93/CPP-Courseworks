//Lisa Chalaguine
//C++ LABwork

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;


int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  cout << "====================== Question 1 ======================" << endl << endl;

  load_board("easy.dat", board);            //loads board
  cout << "Board is ";
  if (!is_complete(board))                  //checks if its complete
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);   //same
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  cout << "====================== Question 2 ======================" << endl << endl;

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";       //places numbers into board
  if (!make_move("I8", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);


   //should not be OK
  cout << "Putting '1' into G8 is ";
  if (!make_move("G8", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);


   //should be OK
  cout << "Putting '8' into G8 is ";
  if (!make_move("G8", '8', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);


cout << "====================== Question 3 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))                         //saves copy of file (identical)
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  cout << "====================== Question 4 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (solve_board(board)) {                                      //solve board function without the counter, counter would be 2172
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("medium.dat", board);                               //counter 15662
  if (solve_board(board) ) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  cout << "====================== Question 5 ======================" << endl << endl;


  load_board("mystery1.dat", board);                             //solve board with counter function
  int counter1 = 0;
  if (solve_board(board, counter1)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  cout << counter1 << endl;
  cout << endl;

  load_board("mystery2.dat", board);
  int counter2 = 0;
  if (solve_board(board, counter2)) {
    cout << "The 'mystery2' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  cout << counter2 << endl;
  cout << endl;

  load_board("mystery3.dat", board);
  int counter3 = 0;
  if (solve_board(board, counter3)) {
    cout << "The 'mystery3' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  cout << counter3 << endl;
  cout << endl;


  return 0;
}

