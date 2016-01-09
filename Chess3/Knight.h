#ifndef Knight_H
#define Knight_H

#include <map>
#include <string>
#include <iostream>

#include "Piece.h"

class Knight : public Piece {

  public:
    Knight (bool whitePlayer);
    ~Knight ();
    Knight* clone ();

    bool isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*>* board);
    string printPiece();

};

#endif
