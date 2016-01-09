#include "ChessBoard.h"
#include <iostream>
#include <string>

using namespace std;


ChessBoard::ChessBoard()
{
 board = new Board();
 resetBoard();
}

void ChessBoard::resetBoard()
{
 cleanall(this -> board);
 board = new Board();

 beginNewGame();               //hasended = false
 makeWhitesTurn();            //whiteturn = true
 makeGameNotInCheck();        //isincheck = false

 board->insert ({string("A2"), new Pawn (true)});
 board->insert ({string("B2"), new Pawn  (true)});
 board->insert ({string("C2"), new Pawn  (true)});
 board->insert ({string("D2"), new Pawn  (true)});
 board->insert ({string("E2"), new Pawn  (true)});
 board->insert ({string("F2"), new Pawn  (true)});
 board->insert ({string("G2"), new Pawn  (true)});
 board->insert ({string("H2"), new Pawn  (true)});

 board->insert ({string("A1"), new Rook (true)});
 board->insert ({string("B1"), new Knight (true)});
 board->insert ({string("C1"), new Bishop (true)});
 board->insert ({string("D1"), new Queen (true)});
 board->insert ({string("E1"), new King (true)});
 board->insert ({string("F1"), new Bishop (true)});
 board->insert ({string("G1"), new Knight (true)});
 board->insert ({string("H1"), new Rook (true)});

 board->insert ({string("A7"), new Pawn  (false)});
 board->insert ({string("B7"), new Pawn  (false)});
 board->insert ({string("C7"), new Pawn  (false)});
 board->insert ({string("D7"), new Pawn (false)});
 board->insert ({string("E7"), new Pawn  (false)});
 board->insert ({string("F7"), new Pawn  (false)});
 board->insert ({string("G7"), new Pawn  (false)});
 board->insert ({string("H7"), new Pawn (false)});

 board->insert ({string("A8"), new Rook (false)});
 board->insert ({string("B8"), new Knight (false)});
 board->insert ({string("C8"), new Bishop (false)});
 board->insert ({string("D8"), new Queen (false)});
 board->insert ({string("E8"), new King (false)});
 board->insert ({string("F8"), new Bishop (false)});
 board->insert ({string("G8"), new Knight (false)});
 board->insert ({string("H8"), new Rook (false)});

 cout << "A new chess game is started!";
}

bool ChessBoard::submitMove(const char* fromSquare, const char* toSquare)
{
 string fromFR (fromSquare);
 string toFR (toSquare);
 int printError = 1;                                                                                      //need this to print valid move error messages, otherwise it print all errors in the "player have valid move" loop

if (hasEnded)                                                                                            //checks whether game has ended
{
 cout << "the game has ended, want to start a new one?" << endl;
  return false;
}

if (fromFR.length() != boardlayout::FRlength|| toFR.length() != boardlayout::FRlength)   //checks that its two characters (one file and one rank) (length is set to 2)
{
 cout << "please type in file and rank for both your source and your destination." << endl;
  return false;
}

if (!withinChessBoard(fromFR) || !withinChessBoard(toFR))                                //checks that its within ChessBoard (so letters from A-H and numbers from 1-8)
{
 cout << "you are not moving within the ChessBoard." << endl;
  return false;
}

Board::iterator it;                                                                                      //checks that there is a Piece at the source FR
it = board -> find(fromFR);

if (it ==   board -> end())
{
 cout << "there is no Piece at " << fromFR << endl;
  return false;
}

Piece* piece = board->at(fromFR);                                                       //initialises Piece

bool isYourPiece = isWhiteTurn == piece -> whitePlayer ();                         //checks whether its current players Piece

if (!isYourPiece)
{
 cout << "this is not your Piece! " << endl;
  return false;
}

if (!piece -> isValidMove (printError, fromFR, toFR, board))               //checks whether valid move, use print error=1 so print error message in the Piece
{
  return false;
}

Board* clone = cloneboard(board);                                                            //clone the board

Piece* capturedPiece = returnCaptured (fromFR, toFR, clone);               //move, in case there is a capture it returns the captured

if (!KingIsUnderAttack (isWhiteTurn, clone))                                             //checks whether the King is safe from rivalry if player moves like that
{
 cout << "ALLOWS YOUR King IN CHECK!! DONT MOVE LIKE THAT!" << endl;
  return false;
}

Piece* movingPiece = board -> at (fromFR);           //confirming on board

try
{
 Piece* toPiece = board -> at (toFR);      //checks whether there is a Piece at the destination and deletes the Piece at destination
 delete toPiece;
 board -> at (toFR) = movingPiece;          //inserts the moving Piece
}
catch (const std::out_of_range &err)
{
  board -> insert ({ toFR, movingPiece });     //if there was nothing then it catches the out of range error and immediately inserts
}

movingPiece -> movePiece();                                 //makes first move = false needed for Pawn
board -> erase (fromFR);
makeGameNotInCheck();

 ///PRINTING
cout << endl;
cout << piece -> printPiece() << " moves from " << fromFR << " to " << toFR;
if (capturedPiece )
{
 cout << " taking " << capturedPiece -> printPiece();
}

if (!KingIsUnderAttack (!isWhiteTurn, board))                   //if oponents King is under attack print check
{
 cout << endl;
 cout << (!isWhiteTurn? "White" : "Black") << " is in check";
 makeGameInCheck();
}

if (!playerHasValidMove (!isWhiteTurn, board))                //if player has no valid move to safe King - check mate!
{
 if (isInCheck)
 {
  cout << "mate ";
  // << (!isWhiteTurn? "White" : "Black") << " loses." << endl;
 }
 else
 {
  cout << "stalemate, boooooring!" << endl;
 }

endThisGame();

return false;
}

isWhiteTurn = !(isWhiteTurn);

delete capturedPiece;
cleanall(clone);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
/*need those to change the bool values directly in the class, otherwise resetBoard doesnt work as intended*/
void ChessBoard::makeGameInCheck()
{
  isInCheck = true;
}

void ChessBoard::makeGameNotInCheck()
{
  isInCheck = false;
}

void ChessBoard::beginNewGame()
{
  hasEnded = false;
}

void ChessBoard::endThisGame()
{
  hasEnded = true;
}

void ChessBoard::makeWhitesTurn()
{
  isWhiteTurn = true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*helperfunction to check whether move is within ChessBoard*/
bool ChessBoard::withinChessBoard (string fileRank)
{
  char file = fileRank.at(boardlayout::Findex);
  char rank = fileRank.at(boardlayout::Rindex);

  return boardlayout::minFile <= file && file <= boardlayout::maxFile && boardlayout::minRank <= rank && rank <= boardlayout::maxRank;
}


bool ChessBoard::KingIsUnderAttack (bool isWhiteTurn, Board* board)
{
 int notPrintError = 0;                                                       //dont want error messages to be printed for every possible move loop tries
 string KingFileRank = findKingFR(isWhiteTurn, board) ;

 for (Board::const_iterator it = board -> begin(); it != board -> end(); it++)
 {
  string challengingFileRank = it -> first;
  Piece* challengingPiece = it -> second;
  if ((challengingPiece -> whitePlayer() != isWhiteTurn) && (challengingPiece -> isValidMove(notPrintError, challengingFileRank, KingFileRank, board)) == true)  //challenging Piece not same boolean value since opponents Piece, if has vald move to Kings position then the King is under attack
  {
   return false;
  }
 }
  return true;
}

/*helperfunction to find Kings file and rank*/
string ChessBoard::findKingFR (bool isWhiteTurn, Board* board)
{
 for (Board::const_iterator it = board -> begin (); it != board -> end (); it++)
 {
 string possibleFileRank = it -> first;
 Piece* possiblePiece = it -> second;
  if (possiblePiece -> whitePlayer () == isWhiteTurn && possiblePiece -> isKing () == true)
  {
   return possibleFileRank;
  }
 }
  return NULL;                                          //there is always a King on board, so should never reach until here
}

/*checks whether player has a valid move to save his King, otherwise checkmate*/
bool ChessBoard::playerHasValidMove (bool isWhiteTurn, Board* board)
{
int notPrintError = 0;
 for (Board::const_iterator it = board -> begin (); it != board -> end (); ++it)
 {
  string possibleSource = it -> first;
  Piece* possiblePiece = it -> second;

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
      Piece* captured = returnCaptured (possibleSource, possibleDest, clone);         //move and return captured if there was one
      bool haveValidMove = KingIsUnderAttack (isWhiteTurn, clone);               //if King is not under attack its a valid move

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


/*since used in submitmove and within player have valid move function - helperfunction to return captured Piece in the cloned board*/
Piece* ChessBoard::returnCaptured (string fromFR, string toFR, Board* board)
{
 Piece* fromPiece = board -> at(fromFR);
 Piece* toPiece;

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
void ChessBoard::cleanall (Board* board)
{
 for (Board::iterator it = board -> begin() ; it != board -> end(); it++)
 {
  delete it -> second;
 }
  delete board;
}

/*clone function for board*/
Board* ChessBoard::cloneboard (Board* board)
{
 Board* clone = new Board;
 for (Board::iterator it = board -> begin() ; it != board -> end(); it++)
 {
  clone -> insert ({ it -> first, it -> second -> clone()});
 }
  return clone;
}

/*destructor*/
ChessBoard::~ChessBoard()
{
 cleanall(board);
}
