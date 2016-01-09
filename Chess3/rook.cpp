#include "rook.h"


rook::rook (bool whitePlayer) : piece (whitePlayer) {}

rook* rook::clone ()
{
  return new rook (this -> whitePlayer());
}

bool rook::isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*>* board)
{

 if (fromFR == toFR)
 {
  if(errorCode==1)
  {
   cout <<  "\033[0;31mmoving to same square!! na na na, skipping your move wont work! \033[0m\n";
  }
  return false;
 }

 if(!(sameFile (fromFR, toFR) || sameRank (fromFR, toFR)))
 {
  if(errorCode==1)
  {
   cout << "\033[0;31millegal move for Rook!! \033[0m\n";     //return false
  }
  return false;
 }

 if ((sameFile (fromFR, toFR) && !noVerticalObstr (fromFR, toFR, board)) || (sameRank (fromFR, toFR) && !noHorizontalObstr (fromFR, toFR, board)))
 {
  if(errorCode==1)
  {
   cout << "\033[0;31mthere is an obstruction on your way! \033[0m\n";         //return false
  }
  return false;
 }

 if (sameColourAtToFR (toFR, board))
 {
  if(errorCode==1)
  {
   cout << "\033[0;31mthere is a piece of your colour! \033[0m\n";
  }
  return false;
 }
//cout <<"yep is valid move";    //no errors
 return true;
}

string rook::printPiece ()
{
 string name (printColour());
 name.append(" Rook");
 return name;
}

rook::~rook () {}
