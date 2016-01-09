#include "king.h"

king::king(bool whitePlayer) : piece(whitePlayer)
{
 _isKing = true;
}

king* king::clone ()
{
 return new king (this -> whitePlayer());
}

bool king::isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*>* board)
{
 if (fromFR == toFR)
 {
  if(errorCode==1)
  {
   cout <<  "\033[0;31mmoving to same square!! na na na, skipping your move wont work! \033[0m\n";
  }
   return false;
 }

 if (!borderingSquare (fromFR, toFR))
 {
  if(errorCode==1)
  {
   cout << "\033[0;31millegal move pattern for King. \033[0m\n ";             //return false
  }
   return false;
 }

 if (sameColourAtToFR (toFR, board))
 {
  if(errorCode==1)
  {
   cout <<"\033[0;31mthere is a piece of your colour! \033[0m\n";          //return false
  }
   return false;
 }

 return true;                                 //no error
}

string king::printPiece ()
{
 string name (printColour());
 name.append(" King");
 return name;
}

king::~king() {}
