#include "pawn.h"

pawn::pawn (bool whitePlayer): piece (whitePlayer) {}

pawn* pawn::clone ()
{
  return new pawn (this -> whitePlayer());
}

bool pawn::isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*> *board)
{
 if (fromFR == toFR)
 {
  if(errorCode==1)
  {
   cout << "\033[0;31mmoving to same square!! na na na, skipping your move wont work! \033[0m\n";
  }
   return false;
 }

 char toRank = toFR.at(boardlayout::Rindex);
 char fromRank = fromFR.at(boardlayout::Rindex);
 int rankAdvancement =_whitePlayer ? toRank - fromRank : fromRank - toRank;     //depending whether black or white

 if (sameFile (fromFR, toFR))
 {
  switch (rankAdvancement)
  {
   case 2:
   {
    if (!firstMove)
    {
     if(errorCode==1)
     {
      cout<< "\033[0;31myou cannot move more than one anymore! \033[0m\n";       //return false
     }
      return false;
    }
    if (!noVerticalObstr (fromFR, toFR, board))
    {
     if(errorCode==1)
     {
      cout << "\033[0;31mthere is an obstruction \033[0m\n";   //return false
     }
     return false;
    }
    break;
   }

   case 1: break;

   default:
    if(errorCode==1)
    {
     cout <<"\033[0;31millegal move for this piece! \033[0m\n";        //return false
    }
   return false;
  }

  try
  {
   if (sameColour (board -> at (toFR)))
   {
    if(errorCode==1)
    {
     cout <<"\033[1;36mthere is a piece of your colour! \033[0m\n";     //return false
    }
    return false;
   }
   else
   {
    if(errorCode==1)
    {
     cout << "\033[0;31millegal capture pattern for Pawn \033[0m\n";   //return false
    }
    return false;
   }
  }catch(const std::out_of_range& e){
  }

 }
 else
 {
 try
 {
  if (!(rankAdvancement == 1 && borderingFile(fromFR, toFR) && !sameColour(board -> at (toFR))))
  {
   if(errorCode==1)
   {
    cout << "\033[0;31millegal move pattern for Pawn \033[0m\n";        //return false
   }
    return false;
  }
  } catch (const std::out_of_range &err) {
    if(errorCode==1)
    {
     cout <<"\033[0;31myou cannot move diagonally if you dont capture! \033[0m\n";   //return false
    }
      // pawn cannot move diagonally if it is not capturing a rivalry piece
   return false;
  }
  }
  //cout << "this is a valid move!";
 return true;
}

string pawn::printPiece ()
{
 string name (printColour ());
 name.append(" Pawn");
 return name;
}

pawn::~pawn () {}
