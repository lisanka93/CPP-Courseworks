#include "Rook.h"


Rook::Rook (bool whitePlayer) : Piece (whitePlayer) {}

Rook* Rook::clone ()
{
  return new Rook (this -> whitePlayer());
}

bool Rook::isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*>* board)
{

 if (fromFR == toFR)
 {
  if(errorCode==1)
  {
   cout <<  "moving to same square!! na na na, skipping your move wont work!"<<endl;
  }
  return false;
 }

 if(!(sameFile (fromFR, toFR) || sameRank (fromFR, toFR)))
 {
  if(errorCode==1)
  {
   cout << "illegal move for Rook!!"<<endl;
  }
  return false;
 }

 if ((sameFile (fromFR, toFR) && !noVerticalObstr (fromFR, toFR, board)) || (sameRank (fromFR, toFR) && !noHorizontalObstr (fromFR, toFR, board)))
 {
  if(errorCode==1)
  {
   cout << "there is an obstruction on your way!"<<endl;
  }
  return false;
 }

 if (sameColourAtToFR (toFR, board))
 {
  if(errorCode==1)
  {
   cout << "there is a Piece of your colour!"<<endl;
  }
  return false;
 }
 return true;
}

string Rook::printPiece ()
{
 string name (printColour());
 name.append(" Rook");
 return name;
}

Rook::~Rook () {}
