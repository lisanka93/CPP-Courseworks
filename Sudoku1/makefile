sudoku: main.o sudoku.o
	g++ -Wno-write-strings -g main.o sudoku.o -o sudoku

$.o: %.cpp
	g++ -Wall -g -c $<

_PHONY: clean 

clean:
	rm -f main *.o
	echo Done!


