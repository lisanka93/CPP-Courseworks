#ifndef PIECE_H
#define PIECE_H

#include <map>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iostream>

#include "boardlayout.h"

using namespace std;

class Piece
{
 protected:
  bool _whitePlayer;               //true = white, false = black (on map)
  bool _isKing = false;            //for King Piece
  bool firstMove = true;          //we need first move for Pawn class since move pattern differs on first move

 public:
  Piece(bool whitePlayer);       //true = white, false = black (on map)
  bool whitePlayer();
  void movePiece();               //sets firstMove to false after first submitMove functioncall
  bool isKing();

/*my virtual functions*/
  virtual ~Piece() = 0;
  virtual Piece* clone() = 0;   //return a different object with same information of itself
  virtual bool isValidMove(int errorCode, string fromFR, string toFR, map<string, Piece*> *board) = 0;

  string printColour ();
  virtual string printPiece () = 0;

 protected:
 /*all functions I need to check the move patterns of the different Pieces. I know that I could have put the last three
 in the individual classes and not let others inherit them but maybe I will invent a new game with another Piece that will
 move L-like (because L is an awesome letter) then I can directly inherit it*/
  bool sameColour(Piece* that);
  bool sameRank(string fromFR, string toFR);
  bool sameFile(string fromFR, string toFR);
  bool sameColourAtToFR(string toFR, map<string, Piece*> *board);
  bool sameDiagonal(string fromFR, string toFR);
  bool noVerticalObstr(string fromFR, string toFR, map<string, Piece*> *board);
  bool noHorizontalObstr(string fromFR, string toFR, map<string, Piece*> *board);
  bool noDiagonalObstr(string fromFR, string toFR, map<string, Piece*>* board);
  bool borderingSquare(string fromFR, string toFR);                                     //King
  bool borderingFile(string fromFR, string toFR);                                      //Pawn
  bool movesInL(string fromFR, string toFR);                                     //Knight
};

#endif // Piece_H
