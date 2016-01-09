#include "chessboard.h"
#include <iostream>
#include <string>

using namespace std;


chessboard::chessboard()
{
 board = new Board();
 resetboard();
}

void chessboard::resetboard()
{
 cleanall(this -> board);
 board = new Board();

 beginNewGame();               //hasended = false
 makeWhitesTurn();            //whiteturn = true
 makeGameNotInCheck();        //isincheck = false

 board->insert ({string("A2"), new pawn (true)});
 board->insert ({string("B2"), new pawn  (true)});
 board->insert ({string("C2"), new pawn  (true)});
 board->insert ({string("D2"), new pawn  (true)});
 board->insert ({string("E2"), new pawn  (true)});
 board->insert ({string("F2"), new pawn  (true)});
 board->insert ({string("G2"), new pawn  (true)});
 board->insert ({string("H2"), new pawn  (true)});

 board->insert ({string("A1"), new rook (true)});
 board->insert ({string("B1"), new knight (true)});
 board->insert ({string("C1"), new bishop (true)});
 board->insert ({string("D1"), new queen (true)});
 board->insert ({string("E1"), new king (true)});
 board->insert ({string("F1"), new bishop (true)});
 board->insert ({string("G1"), new knight (true)});
 board->insert ({string("H1"), new rook (true)});

 board->insert ({string("A7"), new pawn  (false)});
 board->insert ({string("B7"), new pawn  (false)});
 board->insert ({string("C7"), new pawn  (false)});
 board->insert ({string("D7"), new pawn (false)});
 board->insert ({string("E7"), new pawn  (false)});
 board->insert ({string("F7"), new pawn  (false)});
 board->insert ({string("G7"), new pawn  (false)});
 board->insert ({string("H7"), new pawn (false)});

 board->insert ({string("A8"), new rook (false)});
 board->insert ({string("B8"), new knight (false)});
 board->insert ({string("C8"), new bishop (false)});
 board->insert ({string("D8"), new queen (false)});
 board->insert ({string("E8"), new king (false)});
 board->insert ({string("F8"), new bishop (false)});
 board->insert ({string("G8"), new knight (false)});
 board->insert ({string("H8"), new rook (false)});

 cout << "who feels like playing a bit of chess?" << endl;
}

bool chessboard::submitMove(const char* fromSquare, const char* toSquare)
{
 string fromFR (fromSquare);
 string toFR (toSquare);
 int printError = 1;                                                                                      //need this to print valid move error messages, otherwise it print all errors in the "player have valid move" loop

if (hasEnded)                                                                                            //checks whether game has ended
{
 cout << "\033[0;31m he game has ended, want to start a new one?\033[0m\n" << endl;
  return false;
}

if (fromFR.length() != boardlayout::FRlength|| toFR.length() != boardlayout::FRlength)   //checks that its two characters (one file and one rank) (length is set to 2)
{
 cout << "\033[0;31mplease type in file and rank for both your source and your destination.\033[0m\n" << endl;
  return false;
}

if (!withinchessboard(fromFR) || !withinchessboard(toFR))                                //checks that its within chessboard (so letters from A-H and numbers from 1-8)
{
 cout << "\033[0;31myou are not moving within the chessboard. \033[0m\n" << endl;
  return false;
}

Board::iterator it;                                                                                      //checks that there is a piece at the source FR
it = board -> find(fromFR);

if (it ==   board -> end())
{
 cout << "\033[0;31mthere is no piece at \033[0m" << fromFR << endl;
  return false;
}

piece* Piece = board->at(fromFR);                                                       //initialises piece

bool isYourPiece = isWhiteTurn == Piece -> whitePlayer ();                         //checks whether its current players piece

if (!isYourPiece)
{
 cout << "\033[0;31mthis is not your piece! \033[0m\n" << endl;
  return false;
}

if (!Piece -> isValidMove (printError, fromFR, toFR, board))               //checks whether valid move, use print error=1 so print error message in the piece
{
  return false;
}

Board* clone = cloneboard(board);                                                            //clone the board

piece* capturedPiece = returnCaptured (fromFR, toFR, clone);               //move, in case there is a capture it returns the captured

if (!kingIsUnderAttack (isWhiteTurn, clone))                                             //checks whether the king is safe from rivalry if player moves like that
{
 cout << "\033[0;31mALLOWS YOUR KING IN CHECK!! DONT MOVE LIKE THAT!\033[0m\n" << endl;
  return false;
}

piece* movingPiece = board -> at (fromFR);           //confirming on board

try
{
 piece* toPiece = board -> at (toFR);      //checks whether there is a piece at the destination and deletes the piece at destination
 delete toPiece;
 board -> at (toFR) = movingPiece;          //inserts the moving piece
}
catch (const std::out_of_range &err)
{
  board -> insert ({ toFR, movingPiece });     //if there was nothing then it catches the out of range error and immediately inserts
}

movingPiece -> movePiece();                                 //makes first move = false needed for pawn
board -> erase (fromFR);
makeGameNotInCheck();

 ///PRINTING
cout << endl;

cout << Piece -> printPiece() << "\033[1;36m moves from \033[0m" << fromFR << "\033[1;36m to \033[0m" << toFR;
if (capturedPiece )
{
 cout << "\033[1;36m taking \033[0m" << capturedPiece -> printPiece();
}

if (!kingIsUnderAttack (!isWhiteTurn, board))                   //if oponents king is under attack print check
{
 cout << "\033[1;33m CHECK\033[0m";
 makeGameInCheck();
}

if (!playerHasValidMove (!isWhiteTurn, board))                //if player has no valid move to safe king - check mate!
{
 if (isInCheck)
 {
  cout << "\033[1;33mMATE!!! \033[0m\n" << (!isWhiteTurn? "White" : "Black") << "\033[1;36m loses \033[0m\n" << endl;
 }
 else
 {
  cout << "\033[1;32mSTALEMATE, boooooring! \033[0m\n" << endl;
 }

endThisGame();

return false;
}

isWhiteTurn = !(isWhiteTurn);

delete capturedPiece;
cleanall(clone);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
/*need those to change the bool values directly in the class, otherwise resetboard doesnt work as intended*/
void chessboard::makeGameInCheck()
{
  isInCheck = true;
}

void chessboard::makeGameNotInCheck()
{
  isInCheck = false;
}

void chessboard::beginNewGame()
{
  hasEnded = false;
}

void chessboard::endThisGame()
{
  hasEnded = true;
}

void chessboard::makeWhitesTurn()
{
  isWhiteTurn = true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*helperfunction to check whether move is within chessboard*/
bool chessboard::withinchessboard (string fileRank)
{
  char file = fileRank.at(boardlayout::Findex);
  char rank = fileRank.at(boardlayout::Rindex);

  return boardlayout::minFile <= file && file <= boardlayout::maxFile && boardlayout::minRank <= rank && rank <= boardlayout::maxRank;
}


bool chessboard::kingIsUnderAttack (bool isWhiteTurn, Board* board)
{
 int notPrintError = 0;                                                       //dont want error messages to be printed for every possible move loop tries
 string kingFileRank = findKingFR(isWhiteTurn, board) ;

 for (Board::const_iterator it = board -> begin(); it != board -> end(); it++)
 {
  string challengingFileRank = it -> first;
  piece* challengingPiece = it -> second;
  if ((challengingPiece -> whitePlayer() != isWhiteTurn) && (challengingPiece -> isValidMove(notPrintError, challengingFileRank, kingFileRank, board)) == true)  //challenging piece not same boolean value since opponents piece, if has vald move to kings position then the king is under attack
  {
   return false;
  }
 }
  return true;
}

/*helperfunction to find kings file and rank*/
string chessboard::findKingFR (bool isWhiteTurn, Board* board)
{
 for (Board::const_iterator it = board -> begin (); it != board -> end (); it++)
 {
 string possibleFileRank = it -> first;
 piece* possiblePiece = it -> second;
  if (possiblePiece -> whitePlayer () == isWhiteTurn && possiblePiece -> isKing () == true)
  {
   return possibleFileRank;
  }
 }
  return NULL;                                          //there is always a king on board, so should never reach until here
}

/*checks whether player has a valid move to save his king, otherwise checkmate*/
bool chessboard::playerHasValidMove (bool isWhiteTurn, Board* board)
{
int notPrintError = 0;
 for (Board::const_iterator it = board -> begin (); it != board -> end (); ++it)
 {
  string possibleSource = it -> first;
  piece* possiblePiece = it -> second;

  if (possiblePiece -> whitePlayer() == isWhiteTurn)
  {
   for (char i = boardlayout::minFile ; i <= boardlayout::maxFile; i++)
   {
    for (char j = boardlayout::minRank; j <= boardlayout::maxRank; j++)
    {
     string possibleDest("00");
     possibleDest[0]=i;
     possibleDest[1]=j;

     if (possiblePiece -> isValidMove (notPrintError, possibleSource, possibleDest, board) == true)
     {
      Board* clone = cloneboard(board);                                               //clone the board to not mess up initial board
      piece* captured = returnCaptured (possibleSource, possibleDest, clone);         //move and return captured if there was one
      bool haveValidMove = kingIsUnderAttack (isWhiteTurn, clone);               //if king is not under attack its a valid move

      delete captured;
      cleanall(clone);

      if (haveValidMove)
       return true;
      }
     }
    }
   }
  }
 return false;
}


/*since used in submitmove and within player have valid move function - helperfunction to return captured piece in the cloned board*/
piece* chessboard::returnCaptured (string fromFR, string toFR, Board* board)
{
 piece* fromPiece = board -> at(fromFR);
 piece* toPiece;

 Board::iterator it;
 it = board -> find(toFR);
 if (it ==   board -> end())
 {
  board -> insert({ toFR, fromPiece });
  toPiece = NULL;
 }

 if (it == board -> find(toFR))
 {
 toPiece = board -> at (toFR);
 board -> at(toFR) = fromPiece;
 }

 board -> erase(fromFR);
 return toPiece;
}

/*cleanfunction for board*/
void chessboard::cleanall (Board* board)
{
 for (Board::iterator it = board -> begin() ; it != board -> end(); it++)
 {
  delete it -> second;
 }
  delete board;
}

/*clone function for board*/
Board* chessboard::cloneboard (Board* board)
{
 Board* clone = new Board;
 for (Board::iterator it = board -> begin() ; it != board -> end(); it++)
 {
  clone -> insert ({ it -> first, it -> second -> clone()});
 }
  return clone;
}

/*destructor*/
chessboard::~chessboard()
{
 cleanall(board);
}
