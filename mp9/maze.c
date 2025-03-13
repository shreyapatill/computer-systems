#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/*partner: nbadam2, mp31
    Given the name of the file containing the maze, createMaze  allocates memory for the maze_t structure and allocate memory for the cells. Then, it parse the given file and fills in all the parameters of the maze structure, including the cells parameter. It returns a pointer to the maze structure you allocate and fill. Given a pointer to a maze structure destroyMaze frees all memory associated with the maze. Given the structure that represents the maze, printMaze prints out the maze in a human readable format to the console (stdout). This means the maze should be printed in the same format as the mazes shown in the introduction section. Each row is followed by a newline. Given the structure containing the maze and a current row and column recursively, solveMazeDFS solves the maze from this position using the DFS  algorithm. This is a recursive function. It changes the contents of the 2D array (cells) by indicating which cells are along the solution path and which cells were visited during the search. If the maze is unsolvable it returns 0 otherwise it returns 1.
 */	
	
/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
  FILE *read = fopen(fileName, "r");
  maze_t *createdmaze = malloc(sizeof(maze_t));
  int rows;
  int cols;
  char c;
  int i,j;
  fscanf(read, "%d%d", &cols, &rows);
  createdmaze -> width= cols;
  createdmaze -> height = rows;
  createdmaze-> cells = malloc(sizeof(createdmaze ->cells)* (createdmaze ->height));
	
  for( i=0; i< createdmaze-> height; i++){
    createdmaze->cells[i]= malloc(sizeof(createdmaze->cells[i])* createdmaze->width);
  }
	
  fscanf(read, "%c", &c);
	
	
  for( i=0; i<createdmaze->height; i++){
    for( j=0; j<createdmaze->width;j++){
      fscanf(read, "%c", &c);
      createdmaze->cells[i][j] = c;
      if(createdmaze->cells[i][j] == 'S'){
	createdmaze->startRow = i;
	createdmaze->startColumn = j;
      }
      if(createdmaze->cells[i][j] == 'E'){
      createdmaze->endRow = i;
      createdmaze-> endColumn = j;
    }
  }
  fscanf(read, "%c", &c);
}

  fclose(read);
  return createdmaze;
	
	
}
	
/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
  int i;
  for(i=0; i<maze->height; i++){
    free(maze->cells[i]); // free cells memory
  }
	
  free(maze->cells);
  free(maze); // free whole struct
	
}
	
/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
  int row= maze->height;
  int col= maze-> width;
  int i,j;
  for( i=0; i<row; i++){
    for( j=0; j<col; j++){
      printf("%c", maze->cells[i][j]);
    }
    printf("\n");
  }
}
	
/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
  if(row<0 || col<0 || row>= maze->height || col>= maze->width){ //check if its outside of range
    return 0;
  }
  if(maze->cells[row][col]!='S' && maze->cells[row][col]!= 'E'){ // check if its at start or end
    if(maze->cells[row][col]!= ' '){ // if not empty, return 0
      return 0;
    }
  }
	
  if(maze->cells[row][col] == 'E'){ // if reached end, restore the starting position
    maze->cells[maze->startRow][maze->startColumn]= 'S';
    return 1;
  }
	
  maze->cells[row][col]= '*';
	
	
  if(solveMazeDFS(maze, col,row+1)){
      return 1;
  }
  if(solveMazeDFS(maze,col, row-1)){
    return 1;
  }
  if(solveMazeDFS(maze, col-1, row)){
    return 1;
  }
  if(solveMazeDFS(maze, col+1, row)){
    return 1;
  }
  
  maze->cells[row][col]= '~';
  return 0;
}
	    
