#ifndef KNIGHT_H
#define KNIGHT_H

#include <map>
#include <string>
#include <iostream>

#include "piece.h"

class knight : public piece {

  public:
    knight (bool whitePlayer);
    ~knight ();
    knight* clone ();

    bool isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*>* board);
    string printPiece();

};

#endif
