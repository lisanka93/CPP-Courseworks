#include "Pawn.h"

Pawn::Pawn (bool whitePlayer): Piece (whitePlayer) {}

Pawn* Pawn::clone ()
{
  return new Pawn (this -> whitePlayer());
}

bool Pawn::isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*> *board)
{
 if (fromFR == toFR)
 {
  if(errorCode==1)
  {
   cout << "moving to same square!! na na na, skipping your move wont work!"<<endl;
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
      cout<< "you cannot move more than one anymore!"<<endl;       //return false
     }
      return false;
    }
    if (!noVerticalObstr (fromFR, toFR, board))
    {
     if(errorCode==1)
     {
      cout << "there is an obstruction on your way."<<endl;   //return false
     }
     return false;
    }
    break;
   }

   case 1: break;

   default:
    if(errorCode==1)
    {
     cout <<"illegal move for Pawn! "<<endl;        //return false
    }
   return false;
  }

  try
  {
   if (sameColour (board -> at (toFR)))
   {
    if(errorCode==1)
    {
     cout <<"there is a Piece of your colour!"<<endl;     //return false
    }
    return false;
   }
   else
   {
    if(errorCode==1)
    {
     cout << "illegal capture pattern for Pawn."<<endl;   //return false
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
    cout << "illegal move pattern for Pawn."<<endl;        //return false
   }
    return false;
  }
  } catch (const std::out_of_range &err) {
    if(errorCode==1)
    {
     cout <<"you cannot move diagonally if you dont capture!"<<endl;   //return false
    }
      // Pawn cannot move diagonally if it is not capturing a rivalry Piece
   return false;
  }
  }
  //cout << "this is a valid move!";
 return true;
}

string Pawn::printPiece ()
{
 string name (printColour ());
 name.append(" Pawn");
 return name;
}

Pawn::~Pawn () {}
