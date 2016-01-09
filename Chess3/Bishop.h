#ifndef Bishop_H
#define Bishop_H

#include <map>
#include <string>
#include <iostream>

#include "Piece.h"

class Bishop : public Piece
{
  public:
    Bishop (bool whitePlayer);
    ~Bishop ();
    Bishop* clone ();

    bool isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*>* board);
    string printPiece ();
};

#endif
