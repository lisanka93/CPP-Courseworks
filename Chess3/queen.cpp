#include "queen.h"


queen::queen (bool whitePlayer) : piece (whitePlayer) {}

queen* queen::clone ()
{
  return new queen (this -> whitePlayer());
}

bool queen::isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*> *board)
{

 if (fromFR == toFR)
 {
  if(errorCode==1)
  {
   cout <<  "\033[0;31mmoving to same square!! na na na, skipping your move wont work! \033[0m\n";
  }
  return false;
 }

 if (!(sameFile (fromFR, toFR) || sameRank (fromFR, toFR) || sameDiagonal (fromFR, toFR)))
 {
  if(errorCode==1)
  {
   cout << "\033[0;31millegal move pattern for Queen \033[0m\n";
  }
  return false;
 }

 if ((sameFile (fromFR, toFR) && !noVerticalObstr (fromFR, toFR, board)) || (sameRank (fromFR, toFR) && !noHorizontalObstr (fromFR, toFR, board)) || (sameDiagonal (fromFR, toFR) && !noDiagonalObstr (fromFR, toFR, board)))
 {
  if(errorCode==1)
  {
   cout <<"\033[0;31mthere is an obstruction on your way! \033[0m\n";
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

 return true;               //no error
}

string queen::printPiece ()
{
 string name (printColour());
 name.append(" Queen");
 return name;
}

queen::~queen () {}
