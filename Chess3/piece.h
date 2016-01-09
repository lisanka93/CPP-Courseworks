#ifndef PIECE_H
#define PIECE_H

#include <map>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iostream>

#include "boardlayout.h"

using namespace std;

class piece
{
 protected:
  bool _whitePlayer;               //true = white, false = black (on map)
  bool _isKing = false;            //for king piece
  bool firstMove = true;          //we need first move for pawn class since move pattern differs on first move

 public:
  piece(bool whitePlayer);       //true = white, false = black (on map)
  bool whitePlayer();
  void movePiece();               //sets firstMove to false after first submitMove functioncall
  bool isKing();

/*my virtual functions*/
  virtual ~piece() = 0;
  virtual piece* clone() = 0;   //return a different object with same information of itself
  virtual bool isValidMove(int errorCode, string fromFR, string toFR, map<string, piece*> *board) = 0;

  string printColour ();
  virtual string printPiece () = 0;

 protected:
 /*all functions I need to check the move patterns of the different pieces. I know that I could have put the last three
 in the individual classes and not let others inherit them but maybe I will invent a new game with another piece that will
 move L-like (because L is an awesome letter) then I can directly inherit it*/
  bool sameColour(piece* that);
  bool sameRank(string fromFR, string toFR);
  bool sameFile(string fromFR, string toFR);
  bool sameColourAtToFR(string toFR, map<string, piece*> *board);
  bool sameDiagonal(string fromFR, string toFR);
  bool noVerticalObstr(string fromFR, string toFR, map<string, piece*> *board);
  bool noHorizontalObstr(string fromFR, string toFR, map<string, piece*> *board);
  bool noDiagonalObstr(string fromFR, string toFR, map<string, piece*>* board);
  bool borderingSquare(string fromFR, string toFR);                                     //king
  bool borderingFile(string fromFR, string toFR);                                      //pawn
  bool movesInL(string fromFR, string toFR);                                     //knight
};

#endif // piece_H
