#ifndef SUDOKU_H

#define SUDOKU_H

const int MAX_COL = 9, MAX_ROW = 9, MAX_POS = 2, MAX_LENGTH_FILENAME = 80;
/* DECLARATION OF PRESUPPLIED FUNCTIONS */
void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/* =================== Question 1 =================== */
/* DECLARATION OF FUNCTION "is_complete" */
//PRE: a sudoku board
//POST: true if board has no empty entries; false otherwise
bool is_complete(char a_board[MAX_ROW][MAX_COL]);

/* =================== Question 2 =================== */
/* DECLARATION OF FUNCTION "make_move" */
//PRE: a character position (row: A-I; col:1-9), a digit: 1-9, a sudoku board
//POST: false if false format of digit/position OR not permisible move; true otherwise (and changes the value of the position.
bool make_move(char a_pos[MAX_POS], char a_digit, char a_board[MAX_ROW][MAX_COL]);

/* DECLARATION OF FUNCTION "correct_format" */
//PRE: int row, int col and int digit.
//POST: true if in range; false otherwise
bool good_format(char ent_pos[MAX_POS], char ent_digit);

/* DECLARATION OF FUNCTION "permissible_move" */
//PRE: int position row, int position col , int entry
//POST: true if the entry does not exist in the row, column or box of the sudoku; false otherwise.
bool permissible_move(char in_pos[MAX_POS], char in_digit, char in_board[MAX_ROW][MAX_COL]);

/* =================== Question 3 =================== */
/* DECLARATION OF FUNCTION "save_board" */
//PRE: a name for a file, a board
//POST: true if the board was successfully saved on filename; false otherwise
bool save_board(char a_filname [MAX_LENGTH_FILENAME], char a_board[MAX_ROW][MAX_COL]);

/* =================== Question 4 =================== */
/* DECLARATION OF FUNCTION "solve_board" */
//PRE: a board
//POST: true if the board is solvable; false otherwise.
bool solve_board(char test_board[MAX_ROW][MAX_COL]);

/* =================== Question 5 =================== */
/* DECLARATION OF FUNCTION "human_difficulty" */
//PRE: a board
//POST: prints out the total of all permissible moves for all empty entries for the initial sudoku.
void human_difficulty(char a_board[MAX_ROW][MAX_COL]);

/* DECLARATION OF FUNCTION "algo_time" */
//PRE: a board
//POST: prints out the total time for function "solve_board" from Question 4 to run.
void  algo_time(char a_board[MAX_ROW][MAX_COL]);
#endif



