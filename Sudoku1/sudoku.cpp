//Lisa Chalaguine
//C++ LABwork

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++)
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

//my function1

bool is_complete(char board[9][9]) {

  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++)
      if ((board[i][j] == '.') && (!(board[i][j] >= '1' && board[i][j] <= '9')))  //checks whether there is a "dot", then it is obviously not complete and whether any weird characters or numbers out of the 1-9 range
      return false;
  }

  return true;                     //returns true if only numbers from 1-9, however obviously doesnt check whether its correctly solved
}


//my function 2

bool make_move(char position[], char digit, char board[9][9]) {
  int x = position[0] - 'A';          //position in array 0-8 using ASCI
  int y = position[1] - '1';          //position in array 0-8 using ASCI
  int x_top = x - (x%3);
  int y_left = y - (y%3);             //subarray 3x3, needed for later


  if ((x > 8 || y > 8) || (board[x][y] != '.'))                //out of range or space already  taken by other number array goes from 0-8
    return false;

  for (int index = 0; index < 9; index++){                    //same number already exists in row or column
    if ((board[x][index] == digit) || (board[index][y] == digit))
    return false;
  }

  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++)
      if(board[i+x_top][j+y_left] == digit)
      return false;                                        //same number in subarray already exists
  }

  return board[x][y] = digit;                               // if true place digit in cell in array

//note: i could have used helper functions but I decided to put them all in one, and will use separate helper functions for question 4
}


//my function 3

bool save_board(const char *filename2, char board[9][9]) {

  ofstream out_stream;            //filename eg. "copy" as outstream
  out_stream.open(filename2);

  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++)
      out_stream << board [i][j];     //write board into the outstream
      out_stream << endl;
  }

  out_stream.close();
  return true;

  return false;
}


//my function 4

bool solve_board (char board[9][9]){

  int row, col;

  if (!find_free_spot(board, row, col))    //find free spot not taken by number
  return true;                             //function loops through the array, if true, next column/row incremented, if false continues...

  for (char num = '1'; num <= '9'; num++){   //...checks for numbers 1-9 at this free spot  eg.1
    if (safe_move(board, row, col, num)){    //...whether its a save move (not in row, column or subarray)
      board[row][col] = num;                 //and puts the number into the cell  eg. A1 = 1
        if (solve_board(board))              //each loop will call the function again and start the same process for the next free cell eg. A2, then the next free cell, then next etc.
        return true;

        board[row][col] = '.';               //the cell is set to '.' and number is incremented eg 2- then 2 placed A1
    }
  }
  return false;                              //this way the function tries out all possible combinations and exits those where at some point no safe moves are possible. In the end the correct solution stays and is printed on screen
}

//overloaded function with counter

bool solve_board (char board[9][9], int &counter){    //the same function with a counter

  ++counter;
  int row, col;

  if (!find_free_spot(board, row, col))
  return true;

  for (char num = '1'; num <= '9'; num++){
    if (safe_move(board, row, col, num)){
      board[row][col] = num;
        if (solve_board(board, counter))
        return true;

        board[row][col] = '.';
    }
  }
  return false;
}



//searches the board to find an entry that is still unassigned.

bool find_free_spot(char board[9][9], int &row, int &col){
  for (row = 0; row < 9; row++)
    for (col = 0; col < 9; col++)
      if (board[row][col] == '.')
      return true;

      return false;
}



//Returns whether any assigned entry in the specified row matches the given number.

bool used_row(char board[9][9], int row, char num){
  for (int col = 0; col < 9; col++)
    if (board[row][col] == num)
    return true;

    return false;
}



// Returns whether any assigned entry in the specified column matches the given number.

bool used_col(char board[9][9], int col, char num){
  for (int row = 0; row < 9; row++)
    if (board[row][col] == num)
    return true;

    return false;
}


//Returns whether any assigned entry within the specified 3x3 subarray matches the given number.

bool used_subarray (char board[9][9], int x_top, int y_left, char num){
  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      if (board[row+x_top][col+y_left] == num)
      return true;

      return false;

}


// Returns whether it will be legal to assign num to the given row,col location.

bool safe_move(char board[9][9], int row, int col, char num){
  return !used_row(board, row, num) && !used_col(board, col, num) && !used_subarray(board, row - row % 3 , col - col % 3, num);

}

