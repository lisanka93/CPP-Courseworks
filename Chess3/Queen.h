#ifndef Queen_H
#define Queen_H

#include <map>
#include <string>
#include <iostream>

#include "Piece.h"

class Queen : public Piece
{
 public:
  Queen (bool whitePlayer);
  ~Queen ();
  Queen* clone ();

  bool isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*>* board);
  string printPiece ();
};

#endif
