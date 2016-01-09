#ifndef ROOK_H
#define ROOK_H

#include <map>
#include <string>
#include <iostream>

#include "piece.h"

class rook : public piece
{
 public:
  rook (bool whitePlayer);
  ~rook ();
  rook* clone ();

  bool isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*>* board);
  string printPiece ();
};

#endif
