#ifndef King_H
#define King_H

#include <map>
#include <string>
#include <iostream>

#include "Piece.h"

class King : public Piece
{
 public:
  King(bool whitePlayer);
  ~King();
  King* clone();

  bool isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*>* board);
  string printPiece ();
};

#endif
