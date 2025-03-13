#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

/*
Partners: mp
This program solves a Sudoku puzzles using recursive backtracking. Each number 1 through 9 can only occur once in each 3x3 zone, row, and column of the grid. Unfilled locations are set to 0. The functions is_val_in_row, is_val_in_col, and is_val_in_3x3_zone checks if the given number val has already been filled in the row i, column j, and the 3x3 zone corresponding to the cell (i, j). Using these three function, we check the legality of the cell (i, j) with a given number val in function is_val_valid. Then, using is_val_valid, we implement the recursive backtrackign algorithm in solve_sudoku.
 */

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for( int col = 0; col < 9; col++){
    if( sudoku[i][col] == val ) // if val already exists in ith row, return true
      return 1;
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for( int row = 0; row < 9; row++){
    if( sudoku[row][j] == val ) //if val already exists in jth row, return true
      return 1;
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int r = i/3*3; //removes remainder
  int c = j/3*3;

  for( int row = r; row < r+3; row++ ){ //iterates through 0th, 3rd, or 6th row
    for( int col = c; col < c+3; col++ ){ //iterates through 0th, 3rd, or 6th column
      if( sudoku[row][col] == val )
	return 1;
    }
  }
  
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if ( is_val_in_row(val, i, sudoku) ) //checks if val is in row
    return 0;
  else if ( is_val_in_col(val, j, sudoku) ) //checks if val in col
    return 0;
  else if ( is_val_in_3x3_zone(val, i, j, sudoku) ) //check if val is in 3x3
    return 0;

  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j;
  int count = 0;
  for( int r = 0; r < 9; r++ ){
    for( int c = 0; c < 9; c++ ){
      if( sudoku[r][c] == 0 ){
	count = 1; // count becomes 1 if there is an empty cell
	i = r; // store non-fillled (0) cell in (i, j)
	j = c;
	break;
      }
    }
  }
  if( count==0 ) // check if all cells are assigned a number
    return 1;
    
  for( int num = 1; num <= 9; num++ ){
    if( is_val_valid( num, i, j, sudoku ) ){ //check if num can be filled in (i, j)
	sudoku[i][j] = num;
	if( solve_sudoku(sudoku)) //recursivley call this method
	  return 1;
      }
    sudoku[i][j] = 0; //check if num cannot be filled in (i, j), we backtrack
  }  
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





