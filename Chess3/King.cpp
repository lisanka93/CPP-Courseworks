#include "King.h"

King::King(bool whitePlayer) : Piece(whitePlayer)
{
 _isKing = true;
}

King* King::clone ()
{
 return new King (this -> whitePlayer());
}

bool King::isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*>* board)
{
 if (fromFR == toFR)
 {
  if(errorCode==1)
  {
   cout <<  "moving to same square!! na na na, skipping your move wont work!"<<endl;
  }
   return false;
 }

 if (!borderingSquare (fromFR, toFR))
 {
  if(errorCode==1)
  {
   cout << "illegal move pattern for King."<<endl;
  }
   return false;
 }

 if (sameColourAtToFR (toFR, board))
 {
  if(errorCode==1)
  {
   cout <<"there is a Piece of your colour!"<<endl;
  }
   return false;
 }

 return true;
}

string King::printPiece ()
{
 string name (printColour());
 name.append(" King");
 return name;
}

King::~King() {}
