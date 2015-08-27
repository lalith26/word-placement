#include<stdio.h>
#include<stdlib.h>

#define NO_OF_ROWS 5
#define NO_OF_COLUMNS 20
#define NO_OF_WORDS 10

void initializeGrid(char grid[])
{
  int i,j;
  for(i=0;i<NO_OF_ROWS*NO_OF_COLUMNS;i++)
  {
      grid[i] = '-';
  }
}


void printGrid(char grid[])
{
  int i,j;
  for(i=0;i<NO_OF_ROWS;i++)
  {
    for(j=0;j<NO_OF_COLUMNS;j++)
    {
      printf("%c ",grid[i*NO_OF_COLUMNS+j]);
    }
    printf("\n");
  }
}

void calculateSurroundingPositions(char grid[], int targetCell, int results[])
{
  int counter = 0;
  //populating the surrounding squares
  //right
  if((targetCell + 1 < NO_OF_COLUMNS) && (grid[targetCell+1] == '-' ) && (targetCell + 1 % NO_OF_COLUMNS != 0))
    results[counter++] = targetCell+1;
  //left
  if((targetCell - 1 > 0) && (grid[targetCell-1] == '-') && (targetCell % NO_OF_COLUMNS != 0))
    results[counter++] = targetCell - 1;
  //top
  if((targetCell - NO_OF_COLUMNS >=0) && (grid[targetCell - NO_OF_COLUMNS] == '-'))
    results[counter++] = targetCell - NO_OF_COLUMNS;
  //bottom
  if((targetCell + NO_OF_COLUMNS >=0) && (grid[targetCell + NO_OF_COLUMNS] == '-'))
    results[counter++] = targetCell + NO_OF_COLUMNS;
  //top right diagnol
  if((targetCell - (NO_OF_COLUMNS + 1) >= 0) && (grid[targetCell-(NO_OF_COLUMNS + 1)] == '-') && (targetCell % NO_OF_COLUMNS != 0) && (targetCell+1 % NO_OF_COLUMNS != 0))
    results[counter++] = targetCell - (NO_OF_COLUMNS+1);
  //top left diagnol
  if((targetCell - (NO_OF_COLUMNS - 1) >= 0) && (grid[targetCell-(NO_OF_COLUMNS - 1)] == '-'))
    results[counter++] = targetCell - (NO_OF_COLUMNS-1);
  //bottom left diagnol
  if((targetCell + (NO_OF_COLUMNS - 1) >= 0) && (grid[targetCell+(NO_OF_COLUMNS - 1)] == '-'))
    results[counter++] = targetCell + (NO_OF_COLUMNS-1);
  //bottom right diagnol
  if((targetCell + (NO_OF_COLUMNS + 1) >= 0) && (grid[targetCell+(NO_OF_COLUMNS + 1)] == '-'))
    results[counter++] = targetCell + (NO_OF_COLUMNS+1);

}

void fillGrid(char grid[],char word[])
{
//  printf("%s\n",word);

  int i,j, rand_row_cell, rand_col_cell,noOfAvailableCells=0;
  //calculate starting position first time
  do
  {
    rand_row_cell = rand() % NO_OF_ROWS;
    rand_col_cell = rand() % NO_OF_COLUMNS;
  }while(grid[(rand_row_cell*NO_OF_COLUMNS)+(rand_col_cell)] != '-');

  //printf("row and col index:%d,%d\n",rand_row_cell,rand_col_cell);
  for(i=0;word[i]!='\0';i++)
  {

  //  printf("letter:%c\n",word[i]);
    noOfAvailableCells = 0;
    int results[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
    grid[(rand_row_cell * NO_OF_COLUMNS)+(rand_col_cell)] = word[i];
    //printGrid(grid);
    calculateSurroundingPositions(grid, (rand_row_cell*NO_OF_COLUMNS)+(rand_col_cell),results);
    for(j=0;j<9;j++)
    {
      if(results[j] != -1)
      {
        ++noOfAvailableCells;
        //printf("%d ",results[j]);
      }
    }
    //printf("\n");
    int temp = 0 ;
    if(noOfAvailableCells != 1)
     temp = rand()%(noOfAvailableCells-1);
    else
      temp = rand()%noOfAvailableCells;
    //printf("no of available cells is %d, array index value is %d\n",noOfAvailableCells, temp);
    int selectedCell = results[temp];
    //printf("The selected cell is %d\n",selectedCell);
    rand_row_cell = selectedCell/NO_OF_COLUMNS;
    rand_col_cell = selectedCell%NO_OF_COLUMNS;

  }



}

int main()
{
  char grid[NO_OF_ROWS * NO_OF_COLUMNS];
  int i;
  char inputList[NO_OF_WORDS][100]={"one","two","three","four","five","six","seven","eight","nine","ten"};


  initializeGrid(grid);
  for(i=0;i<NO_OF_WORDS;i++)
  {
    fillGrid(grid, inputList[i]);
  }
  printGrid(grid);
  return 0;
}
