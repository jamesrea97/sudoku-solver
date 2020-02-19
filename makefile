sudoku: sudoku.o main.o
	g++ -Wall -g sudoku.o main.o -o sudoku
main.o: main.cpp sudoku.h
	g++ -Wall -g -c main.cpp
sudoku.0: sudoku.cpp sudoku.h
	g++ -Wall -g -c sudoku

clean:
	rm -f *.o sudoku
