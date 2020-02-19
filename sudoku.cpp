#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"
#include <chrono>
#include <iomanip>

using namespace std;

/* DEFINITION OF PRESUPPLIED FUNCTIONS */
/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}
/* END OF DEFINITION OF PRESUPPLIED FUNCTION */

/* =================== Question 1 ===================  */
/* DEFINITION OF FUNCTION "is_complete" */
bool is_complete(char a_board[MAX_COL][MAX_COL]) {
  
  for (int row = 0; row < MAX_ROW; row++) {
    for (int col = 0; col < MAX_COL; col++){
      if(a_board[row][col] < '1' || a_board[row][col] > '9')
	return false;
    }
  }
  return true;
}
/* END OF FUNCTION DEFINITION */

/* =================== Question 2 =================== */
/* DEFINITION OF FUNCTION "make_move" */
bool make_move(char a_pos[MAX_POS], char a_digit, char a_board[MAX_ROW][MAX_COL]) {

  //declaring variables for square test and position row/col.
  int entry_row, entry_col;
  
 
  //checking if move is good format:
  if(!good_format(a_pos, a_digit))
     return false;
     
  //checking if the move is permissible:
  if (!permissible_move(a_pos, a_digit, a_board))
    return false;
  
  //Ammending a_board with new entry.
  a_board[entry_row][entry_col] = a_digit;

  return true;
}
/* END OF DEFINITION OF FUNCTION */

/* DEFINITION OF FUNCTION "good_format" */
bool good_format(char ent_pos[MAX_POS], char ent_dig){

  char ent_row = ent_pos[0];
  char ent_col = ent_pos[1];

  //Checking the format of digit is correct:
  if( ent_dig > 57 || ent_dig < 49) {
    return false;
  }
  //Checking if row is in range:
  else if (ent_row > 73 || ent_row < 65){
    return false;
  }
  //Checking if col is in range:
  else if (ent_col > 57 || ent_col < 49) {
    return false;
  }

  return true;
}
/* END OF FUNCTION DEFINITION */

/* DEFINITION OF FUNCTION "permissible_move" */
bool permissible_move(char in_pos[MAX_POS], char in_digit, char in_board[MAX_ROW][MAX_COL]) {

  int int_row = static_cast<int>(in_pos[0]) - 65;
  int int_col = static_cast<int>(in_pos[1]) - 49;
  
  //Using following int variables for square test
  int min_col, min_row;

  //Checking if digit exists on current column
  for (int row = 0; row < MAX_ROW; row++) {
    if (in_digit == in_board[row][int_col]) {
      return false;
    }
  }

  //Checking if digit exists on current row
  for (int col = 0; col < MAX_COL; col++) {
    if (in_digit == in_board[int_row][col]) {
      return false;
    }
  }

  //Checking if digit exists in current 3x3 square
  switch(int_row / 3) {
  case 0: min_row = 0; break;
  case 1: min_row = 1; break;
  case 2: min_row = 2; break;
  }

  switch(int_col / 3) {
  case 0: min_col = 0; break;
  case 1: min_col = 1; break;
  case 2: min_col = 2; break;
  }
  
  //Comparing with each entry in respective 3x3 square
  for (int row = 3 * min_row; row <= 3 * min_row + 2; row++) {
    for (int col = 3 * min_col; col <= 3 * min_col + 2; col++){
      if (in_digit == in_board[row][col]) {
	return false;
      }
    }
  }
  return true;
}
/* END OF FUNCTION DEFINITION */

/* =================== Question 3 =================== */
/* DEFINITION OF FUNCTION "save_board" */
bool save_board(char a_filename[MAX_LENGTH_FILENAME], char a_board[MAX_ROW][MAX_COL]) {
  ofstream fout;
  
  fout.open(a_filename);
  
  if (!fout) {
    cout << a_filename << " has not been correctly opened.";
    return false;
  }
  
  for (int row = 0; row < MAX_ROW; row++) {
    for (int col = 0; col < MAX_COL; col++) {
      fout.put(a_board[row][col]);
    }
    fout << endl;
  }
  fout.close();
  
}
/* END OF DEFINITION OF FUNCTION */

/* =================== Question 4 =================== */
/* DEFINITION OF FUNCTION "solve_board" */
bool solve_board(char test_board[MAX_ROW][MAX_COL]) {
  if (is_complete(test_board)) {
    return true;
  }
  //for every row and every column
  for (char row = 'A'; row <= 'I'; row++) {
    for (char col = '1'; col <= '9'; col++) {
      
      //converting to int row and col and formatting pos
      int int_row = static_cast<int>(row) - 65;
      int int_col = static_cast<int>(col) - 49;
      char pos[MAX_POS] = {row, col};
      
      //only enter if empty cell
		if (test_board[int_row][int_col] == '.') {
	//consider number 1-9 (only if empty)
			for (char number = '1'; number <= '9'; number++) {
	  //check if adding number doesn't make the board inconsistent
			if (permissible_move(pos, number, test_board)) {
	    //ammend board with the new 'guess'
				test_board[int_row][int_col] = number;
	    //consider the new board with 'guess' recursively.
	    //guessing terminates when a consistent board has been found.
				if (solve_board(test_board)) {
					return true;
	    }
	  }
	  //for current board and current position, current number does not work - put '.'
	  //and retest for another number.
	  test_board[int_row][int_col] = '.';
	}
	//for current board, current position and for any number 1-9, there is inconsistency.
	return false;
      }
    }
  }
  return false;
}
/* END OF DEFINITION OF FUNCTION */

/* =================== Question 5  =================== */
/* DEFINITION OF FUNCTION "human_difficulty" */
void human_difficulty(char a_board[MAX_ROW][MAX_COL]) {
		   
  int count = 0;
  for (char row = 'A'; row <= 'I'; row++) {
    for (char col = '1'; col <= '9' ; col++) {
      char pos[MAX_POS] = {row, col};
      int int_row = static_cast<int>(row) - 65;
      int int_col = static_cast<int>(col) - 49;
      if (a_board[int_row][int_col] == '.'){
	for (char number = '1'; number <= '9'; number++) {
	  if (permissible_move(pos, number, a_board)){
	    //adds 1 as the blank entry could be of value 'number'
	    count++;
	  }
	}
      }
    }
  }
  cout << count << endl;
}
/* END OF FUNCTION DEFINITION */

/* DEFINITION OF FUNCTION "algo_time" */
void algo_time(char a_board[MAX_ROW][MAX_COL]) {

  //using predefined libraries for measuring time:
  
  //starting the time measuring here
  auto start = chrono::high_resolution_clock::now();
  solve_board(a_board);
  //measuring the time it takes for solve_board to run.
  //stopping the time measurer
  auto stop = chrono::high_resolution_clock::now();
  
  //measuring the time difference between start and stop
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

  long length = static_cast<long>(duration.count());

  cout << length << endl;
}
/* END OF DEFINTION OF FUNCTION */
    
