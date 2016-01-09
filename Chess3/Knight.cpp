#include "Knight.h"

Knight::Knight (bool whitePlayer) : Piece (whitePlayer) {}

Knight* Knight::clone ()
{
 return new Knight (this -> whitePlayer ());
}

bool Knight::isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*>* board)
{
 if (fromFR == toFR)
 {
  if(errorCode==1)
  {
   cout <<  "moving to same square!! na na na, skipping your move wont work!"<<endl;
  }
   return false;
 }

 if(!movesInL(fromFR, toFR))
 {
  if(errorCode==1)
  {
   cout <<"illegal movepattern for Knight!" << endl;
  }
   return false;
 }

 if(sameColourAtToFR (toFR, board))
 {
  if(errorCode==1)
  {
   cout << "there is a Piece of your colour!" << endl;
  }
   return false;
 }
 return true;
 }

string Knight::printPiece ()
{
 string name (printColour ());
 name.append(" Knight");
 return name;
}

Knight::~Knight () {}
