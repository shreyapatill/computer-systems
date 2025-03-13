/*This program implements a Game of Life.Every cell in the 2D array of cells
 *interacts with its eight neighbor cells that are vertically, horizontally,
 * and diagonally adjacent. The game board is represented as 1D arrays that 
 * have width*height cells where 0 means dead and 1 means alive for each cell.
 *We implement three functions in this program. The first, called
 * countLiveNeighor returns the number of alive neighbors. The second function
 * called updateBoard, updates the game board according to the rules given. 
 *The last function, called aliveStable, returns 1 if the current game board 
 *stays the same for the next step. Otherwise it returns 0.
 *
 *
 * partners: nbadam2, mp31
 */










/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  int liveNeighbors = 0;
  for( int currRow = row-1; currRow <= row+1; currRow++){
    if( currRow < boardRowSize && currRow >= 0 ){
      for( int currCol = col-1; currCol <= col+1; currCol++ ){
	if( currCol < boardColSize && currCol >= 0 ){
	  if( !(currRow==row && currCol==col) ){
	    int newIndex = currRow * boardColSize + currCol;
	    if( board[newIndex]==1 ){
	      liveNeighbors++;
	    }
	  }
	}
      }
    }
  }
  return liveNeighbors;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int size = boardRowSize*boardColSize;
  int temp[size];
  for( int row = 0; row < boardRowSize; row++ ){
    for( int col = 0; col < boardColSize; col++ ){
      int liveNeighbors = countLiveNeighbor( board, boardRowSize, boardColSize, row, col );
      int currIndex = row * boardColSize + col;
      if( board[currIndex]==1 && ( liveNeighbors==2 || liveNeighbors==3 ))
	temp[currIndex] = 1;
      else
	temp[currIndex] = 0;
      
      if( board[currIndex]==0 && liveNeighbors==3 )
	temp[currIndex] = 1;
    }
  }
  for( int i = 0; i < size; i++ ){
    board[i] = temp[i];
  }

}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  //copy board
  int size = boardRowSize*boardColSize;
  int nextStep[size];
  for( int i = 0; i < size; i++ ){
    nextStep[i] = board[i];
  }
  //update board
  updateBoard( nextStep, boardRowSize, boardColSize );
  //check if the boards are the same
  for( int i = 0; i < size; i++ ){
    if (nextStep[i] != board[i]){
      return 0;
    }
  }
  return 1;
}

				
				
			

