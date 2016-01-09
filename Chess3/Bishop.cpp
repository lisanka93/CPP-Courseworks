#include "Bishop.h"

Bishop::Bishop (bool whitePlayer) : Piece (whitePlayer) {}        //constructor with bool whitePlayer one true one false in map

Bishop* Bishop::clone()
{
 return new Bishop (this -> whitePlayer());
}

bool Bishop::isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*> *board)
{
 if (fromFR == toFR)
 {
  if(errorCode==1){
  cout <<  "moving to same square!! na na na, skipping your move wont work!" << endl;
  }
  return false;
 }

 if(!sameDiagonal(fromFR, toFR))
 {
  if(errorCode==1){
 cout <<  "illegal movepattern for Bishop" << endl;
 }
  return false;
 }

if(!noDiagonalObstr(fromFR, toFR, board))
 {
  if(errorCode==1){
 cerr<<  "there is an obstruction on the way for Bishop" << endl;

 }
  return false;
 }

if(sameColourAtToFR(toFR, board))
 {
  if(errorCode==1){
  cout <<  "there is Bishops friendly Piece at destination!" << endl;
  }
  return false;
 }

    return true;
}

string Bishop::printPiece()
{
  string name(printColour());
  name.append(" Bishop");
  return name;
}

Bishop::~Bishop () {}
