#include "Queen.h"


Queen::Queen (bool whitePlayer) : Piece (whitePlayer) {}

Queen* Queen::clone ()
{
  return new Queen (this -> whitePlayer());
}

bool Queen::isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*> *board)
{

 if (fromFR == toFR)
 {
  if(errorCode==1)
  {
   cout <<  "moving to same square!! na na na, skipping your move wont work!"<<endl;
  }
  return false;
 }

 if (!(sameFile (fromFR, toFR) || sameRank (fromFR, toFR) || sameDiagonal (fromFR, toFR)))
 {
  if(errorCode==1)
  {
   cout << "illegal move pattern for Queen"<<endl;
  }
  return false;
 }

 if ((sameFile (fromFR, toFR) && !noVerticalObstr (fromFR, toFR, board)) || (sameRank (fromFR, toFR) && !noHorizontalObstr (fromFR, toFR, board)) || (sameDiagonal (fromFR, toFR) && !noDiagonalObstr (fromFR, toFR, board)))
 {
  if(errorCode==1)
  {
   cout <<"there is an obstruction on your way! \033[0m\n"<<endl;
  }
  return false;
 }

 if (sameColourAtToFR (toFR, board))
 {
  if(errorCode==1)
  {
   cout << "there is a Piece of your colour! \033[0m\n"<<endl;
  }
  return false;
 }

 return true;
}

string Queen::printPiece ()
{
 string name (printColour());
 name.append(" Queen");
 return name;
}

Queen::~Queen () {}
