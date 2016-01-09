#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <map>
#include <iostream>
#include <string>
#include <stdexcept>

#include "boardlayout.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"

using namespace std;

typedef map<string, Piece*> Board;

class ChessBoard
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
  ChessBoard();
  ~ChessBoard();
/* resetboard creates a new board and sets some boolean variables accordingly, see above*/
  void resetBoard();
/*submit move first checks whether game has ended, then whether the submitted
moves are correct, whether there actually is a Piece at the source, whether
is has the same colour and finally whether it is a valid move for this particular
Piece.
Then I clone the board, to not mess up the initial one and check whether the
move follows the rules and doesnt leave the current players King under attack,
if not I confirm the move on the board and delete the cloned one.
I print everything and check whether the current player can attack the King by
maKing a direct move to the opponents King destination. If he can, the opponent
is in check and in the next move(his) he can save it IF he has a valid move. If
not then its Checkmate*/
  bool submitMove(const char* fromSquare, const char* toSquare);

 private:
  bool withinChessBoard (string fileRank);
  bool KingIsUnderAttack (bool isWhiteTurn, Board* board);
  bool playerHasValidMove (bool isWhiteTurn, Board* board);
  string findKingFR (bool isWhiteTurn, Board* board);
  Piece* returnCaptured (string sourceFileRank, string destFileRank, Board* board);
  Board* cloneboard (Board* board);
  void cleanall (Board* board);

};

#endif
