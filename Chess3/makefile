chess: ChessMain.o ChessBoard.o Bishop.o King.o Knight.o Pawn.o Piece.o Queen.o Rook.o
	g++ -std=c++0x -g ChessMain.o ChessBoard.o Bishop.o King.o Knight.o Pawn.o Piece.o Queen.o Rook.o -o chess
	

ChessMain.o: ChessMain.cpp ChessBoard.h boardlayout.h
	g++ -std=c++0x -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h boardlayout.h Piece.h King.h Queen.h Bishop.h Rook.h Knight.h Pawn.h
	g++ -std=c++0x -g -c ChessBoard.cpp

Piece.o: Piece.cpp Piece.h boardlayout.h
	g++ -std=c++0x -g -c Piece.cpp

Bishop.o: Bishop.cpp Bishop.h
	g++ -std=c++0x -g -c Bishop.cpp

King.o: King.cpp King.h
	g++ -std=c++0x -g -c King.cpp

Knight.o: Knight.cpp Knight.h
	g++ -std=c++0x -g -c Knight.cpp

Pawn.o: Pawn.cpp Pawn.h
	g++ -std=c++0x -g -c Pawn.cpp

Queen.o: Queen.cpp Queen.h
	g++ -std=c++0x -g -c Queen.cpp

Rook.o: Rook.cpp Rook.h
	g++ -std=c++0x -g -c Rook.cpp

.PHONY:clean

Clean:
	rm-f chess-*.o
