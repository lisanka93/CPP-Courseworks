#include "knight.h"

knight::knight (bool whitePlayer) : piece (whitePlayer) {}

knight* knight::clone ()
{
 return new knight (this -> whitePlayer ());
}

bool knight::isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*>* board)
{
 if (fromFR == toFR)
 {
  if(errorCode==1)
  {
   cout <<  "\033[0;31mmoving to same square!! na na na, skipping your move wont work! \033[0m\n";
  }
   return false;
 }

 if(!movesInL(fromFR, toFR))
 {
  if(errorCode==1)
  {
   cout <<"\033[0;31millegal movepattern for Knight! \033[0m\n" << endl;
  }
   return false;
 }

 if(sameColourAtToFR (toFR, board))
 {
  if(errorCode==1)
  {
   cout << "\033[0;31mthere is a piece of your colour! \033[0m\n" << endl;
  }
   return false;
 }
 return true;
 }

string knight::printPiece ()
{
 string name (printColour ());
 name.append(" Knight");
 return name;
}

knight::~knight () {}
