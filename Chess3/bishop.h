#ifndef BISHOP_H
#define BISHOP_H

#include <map>
#include <string>
#include <iostream>

#include "piece.h"

class bishop : public piece
{
  public:
    bishop (bool whitePlayer);
    ~bishop ();
    bishop* clone ();

    bool isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*>* board);
    string printPiece ();
};

#endif
