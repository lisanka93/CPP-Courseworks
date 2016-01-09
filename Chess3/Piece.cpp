#include "Piece.h"
#include<stdexcept>



Piece::Piece(bool whitePlayer) //put in map true or false, sets _whitePlayer for current Piece to black or white
{
 _whitePlayer = whitePlayer;
}

bool Piece::whitePlayer()
{
 return(_whitePlayer);
}

void Piece::movePiece()            //except for very first time it is never first move. after first submitMove() firstMove is changed to false and the Pawn cannot move two squares anymore
{
 firstMove = false;
}

bool Piece::isKing()               //except for King always false
{
 return _isKing;
}

bool Piece::sameColourAtToFR(string toFR, map<string, Piece*> *board)        // return true if Piece on the toFR is a friendly,false otherwise (rivalry on dest or emptyP square)
{
 std::map<string, Piece*>::iterator it;
 it = board -> find(toFR);
 if(it == board->end())
 {
  return false;
 }
 if (sameColour(board->at(toFR)))
 {
  return true;
 }
}

/*helperfunction*/
bool Piece::sameColour(Piece* that)                                         //if both boolean function return true the Piece has same colour
{
  return this->whitePlayer() == that->whitePlayer();
}


///so those are the different checks that I need for the different Pieces. I will pick those that I need for the validMove() function for child Pieces from this parent function ///

bool Piece::sameRank(string fromFR, string toFR)
{
  return fromFR.at(boardlayout::Rindex) == toFR.at(boardlayout::Rindex);
}

bool Piece::sameFile(string fromFR, string toFR)
{
  return fromFR.at(boardlayout::Findex) == toFR.at(boardlayout::Findex);
}

bool Piece::sameDiagonal(string fromFR, string toFR)                                  //diagonal means it moved from one corner to square to opposite one, thus the distance from fromFile to toFile and ditance from fromRank to toRank has to be the same
{
  return abs (fromFR.at(boardlayout::Findex) - toFR.at(boardlayout::Findex)) == abs (fromFR.at(boardlayout::Rindex) - toFR.at(boardlayout::Rindex));
}

bool Piece::noHorizontalObstr(string fromFR, string toFR, map<string, Piece*> *board)
{
  char fromRank = fromFR.at(boardlayout::Rindex);
  char fromFile = fromFR.at(boardlayout::Findex);
  char toFile = toFR.at(boardlayout::Findex);
  char lowFile = (fromFile < toFile) ? fromFile : toFile;
  char highFile = (fromFile < toFile) ? toFile : fromFile;

  for (char i = lowFile + 1; i < highFile; i++)
  {
   string between("00");
   between[1]=fromRank;
   between[0]=i;
    try {
      board -> at(between);
      return false;
    } catch (const std::out_of_range &err) {
    }
  }
   return true;
}


bool Piece::noVerticalObstr(string fromFR, string toFR, map<string, Piece*>* board)
{
 char fromFile = fromFR.at(boardlayout::Findex);
 char fromRank = fromFR.at(boardlayout::Rindex);
 char toRank = toFR.at(boardlayout::Rindex);
 char lowRank = (fromRank < toRank) ? fromRank : toRank;
 char highRank = (fromRank < toRank) ? toRank : fromRank;

 for (char i = lowRank + 1; i < highRank; i++)
 {
  string between("00");
  between[0]=fromFile;
  between[1]=i;
    try {
      board -> at(between);
      return false;
    } catch (const std::out_of_range &err) {
    }
 }
  return true;
}


bool Piece::noDiagonalObstr(string fromFR, string toFR, map<string, Piece*> *board)
{
 char fromRank = fromFR.at(boardlayout::Rindex);
 char toRank = toFR.at(boardlayout::Rindex);
 char lowRank = (fromRank < toRank) ? fromRank : toRank;
 char highRank = (fromRank < toRank) ? toRank : fromRank;

 char fromFile = fromFR.at(boardlayout::Findex);
 char toFile = toFR.at(boardlayout::Findex);
 char lowFile = (fromFile < toFile) ? fromFile : toFile;
 char highFile = (fromFile < toFile) ? toFile : fromFile;

 bool isPositiveSlope = (toFile - fromFile) == (toRank - fromRank);

 string between("00");

 for (int i = 1; i < (highFile - lowFile); i++)
 {
  if (isPositiveSlope)
  {
   between[0] = lowFile + i;
   between[1] = lowRank + i;
   }
   else
   {
    between[0] = lowFile + i;
    between[1] = highRank - i;
   }

   try {
   board -> at (between);
   return false;
   } catch (const std::out_of_range &err) {
    }
 }
  return true;
}


bool Piece::borderingSquare(string fromFR, string toFR)                //for King
{
 char fromFile = fromFR.at(boardlayout::Findex);
 char fromRank = fromFR.at(boardlayout::Rindex);
 char toFile = toFR.at(boardlayout::Findex);
 char toRank = toFR.at(boardlayout::Rindex);

 return max (abs (toFile - fromFile), abs (toRank - fromRank)) == 1;
}

bool Piece::borderingFile (string fromFR, string toFR)              //for Pawn
{
 char fromFile = fromFR.at(boardlayout::Findex);
 char toFile = toFR.at (boardlayout::Findex);
 return abs (toFile - fromFile) == 1;
}


bool Piece::movesInL(string fromFR, string toFR)              //it is an L if either the file difference number is one and rank is two or vice versa
{
 char fromFile = fromFR.at(boardlayout::Findex);
 char fromRank = fromFR.at(boardlayout::Rindex);
 char toFile = toFR.at(boardlayout::Findex);
 char toRank = toFR.at(boardlayout::Rindex);

 return abs (fromFile - toFile) * abs (fromRank - toRank) == 2;
}

string Piece::printColour ()
{
 return _whitePlayer? string("White's") : string("Black's");
}

Piece::~Piece () {}

