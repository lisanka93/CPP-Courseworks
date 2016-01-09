#ifndef QUEEN_H
#define QUEEN_H

#include <map>
#include <string>
#include <iostream>

#include "piece.h"

class queen : public piece
{
 public:
  queen (bool whitePlayer);
  ~queen ();
  queen* clone ();

  bool isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*>* board);
  string printPiece ();
};

#endif
