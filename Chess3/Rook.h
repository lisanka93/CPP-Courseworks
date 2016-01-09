#ifndef Rook_H
#define Rook_H

#include <map>
#include <string>
#include <iostream>

#include "Piece.h"

class Rook : public Piece
{
 public:
  Rook (bool whitePlayer);
  ~Rook ();
  Rook* clone ();

  bool isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*>* board);
  string printPiece ();
};

#endif
