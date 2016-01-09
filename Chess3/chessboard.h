#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <map>
#include <iostream>
#include <string>
#include <stdexcept>

#include "boardlayout.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"

using namespace std;

typedef map<string, piece*> Board;

class chessboard
{
 private:
  Board* board;
  bool isWhiteTurn = true;
  bool isInCheck = false;
  bool hasEnded = false;
  void makeGameInCheck ();
  void makeGameNotInCheck ();
  void beginNewGame ();
  void endThisGame ();
  void makeWhitesTurn ();

 public:
  chessboard();
  ~chessboard();
/* resetboard creates a new board and sets some boolean variables accordingly, see above*/
  void resetboard();
/*submit move first checks whether game has ended, then whether the submitted
moves are correct, whether there actually is a piece at the source, whether
is has the same colour and finally whether it is a valid move for this particular
piece.
Then I clone the board, to not mess up the initial one and check whether the
move follows the rules and doesnt leave the current players king under attack,
if not I confirm the move on the board and delete the cloned one.
I print everything and check whether the current player can attack the king by
making a direct move to the opponents king destination. If he can, the opponent
is in check and in the next move(his) he can save it IF he has a valid move. If
not then its Checkmate*/
  bool submitMove(const char* fromSquare, const char* toSquare);

 private:
  bool withinchessboard (string fileRank);
  bool kingIsUnderAttack (bool isWhiteTurn, Board* board);
  bool playerHasValidMove (bool isWhiteTurn, Board* board);
  string findKingFR (bool isWhiteTurn, Board* board);
  piece* returnCaptured (string sourceFileRank, string destFileRank, Board* board);
  Board* cloneboard (Board* board);
  void cleanall (Board* board);

};

#endif
