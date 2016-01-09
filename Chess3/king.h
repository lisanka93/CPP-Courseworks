#ifndef KING_H
#define KING_H

#include <map>
#include <string>
#include <iostream>

#include "piece.h"

class king : public piece
{
 public:
  king(bool whitePlayer);
  ~king();
  king* clone();

  bool isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*>* board);
  string printPiece ();
};

#endif
