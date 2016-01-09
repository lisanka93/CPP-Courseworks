#include "bishop.h"

bishop::bishop (bool whitePlayer) : piece (whitePlayer) {}        //constructor with bool whitePlayer one true one false in map

bishop* bishop::clone()
{
 return new bishop (this -> whitePlayer());
}

bool bishop::isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*> *board)
{
 if (fromFR == toFR)
 {
  if(errorCode==1){
  cout <<  "\033[0;31mmoving to same square!! na na na, skipping your move wont work! \033[0m" << endl;
  }
  return false;
 }

 if(!sameDiagonal(fromFR, toFR))
 {
  if(errorCode==1){
 cout <<  "\033[0;31millegal movepattern for bishop \033[0m\n" << endl;
 }
  return false;
 }

if(!noDiagonalObstr(fromFR, toFR, board))
 {
  if(errorCode==1){
 cerr<<  "\033[0;31mthere is an obstruction on the way for bishop \033[0m\n" << endl;

 }
  return false;
 }

if(sameColourAtToFR(toFR, board))
 {
  if(errorCode==1){
  cout <<  "\033[0;31mthere is bishops friendly piece at destination! \033[0m\n" << endl;
  }
  return false;
 }

    return true;          //no error
}

string bishop::printPiece()
{
  string name(printColour());
  name.append(" Bishop");
  return name;
}

bishop::~bishop () {}
