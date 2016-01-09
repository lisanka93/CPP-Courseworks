#ifndef Pawn_H
#define Pawn_H

#include <map>
#include <string>
#include <iostream>

#include "Piece.h"

class Pawn : public Piece
{
 public:
  Pawn (bool whitePlayer);
  ~Pawn ();
  Pawn* clone ();

  bool isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*>* board);
  string printPiece ();
};

#endif
