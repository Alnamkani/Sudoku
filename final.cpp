/****************************************

*Author: Mohammed Alnamkani

*Date: 12/14/2019

*This program finds one solution for a sudoku.

*****************************************/
#include <iostream>
#include <vector>
using namespace std;
#define SIZE 9

bool is_safe( int row[][SIZE], int colum[][SIZE], int box[][SIZE], int num, int x, int y);
bool solution(int sudoku[][SIZE], int row[][SIZE], int colum[][SIZE], int box[][SIZE]);
bool find_loc(int sudoku[][SIZE], int &x, int &y);
void set_row(int row[][SIZE], int sudoku[][SIZE]);
void set_colum(int colum[][SIZE], int sudoku[][SIZE]);
void set_box(int box[][SIZE], int sudoku[][SIZE]);
void print_sudoku(int sudoku[][SIZE]);
int which_box(int x, int y);
vector<vector<vector<int>>> which_digit(int row[][SIZE], int colum[][SIZE], int box[][SIZE], int sudoku[][SIZE]);

int main()
{
  int sudoku[SIZE][SIZE] = {{0, 0, 0, 7, 0, 2, 4, 5, 3},
                            {9, 0, 0, 0, 0, 8, 0, 0, 0}, 
                            {7, 4, 0, 0, 0, 5, 0, 1, 0}, 
                            {1, 9, 5, 0, 8, 0, 0, 0, 0},
                            {0, 7, 0, 0, 0, 0, 0, 2, 5}, 
                            {0, 3, 0, 5, 7, 9, 1, 0, 8}, 
                            {0, 0, 0, 6, 0, 1, 0, 0, 0}, 
                            {3, 6, 0, 9, 0, 0, 0, 0, 1}, 
                            {0, 0, 0, 0, 0, 0, 0, 0, 6}};
  int row     [SIZE][SIZE];
  int colum   [SIZE][SIZE];
  int box     [SIZE][SIZE];
  
  cout << "This is the original Sudoku: " << endl;
  print_sudoku(sudoku);

  solution(sudoku, row, colum, box);
  
  cout << "This is the solved Sudoku: " << endl;
  print_sudoku(sudoku);

}

bool solution(int sudoku[][SIZE], int row[][SIZE], int colum[][SIZE], int box[][SIZE])
{
  set_row(row,     sudoku);
  /*
	each row in the two dimensional array corresponds to a row in the sudoku,
	if we can't use Value in the sudoku we place zero if we can use it we put 1  
  */
  set_colum(colum, sudoku); // ^^ same 
  set_box(box,     sudoku); //^^ same 
  
  vector<vector<vector<int>>> pos; //this is a three dimensional vector that has all of the possible value that we can put in one cell 
  
  pos = which_digit(row, colum, box, sudoku); // set the vector
  
  int x,y;
  
  if (!find_loc(sudoku, x, y)){return true;} //pass by address
    for (int h = 0; h < pos[y][x].size(); h++)
    {
      if (is_safe(row, colum, box, pos[y][x][h], x, y)) // if it's safe to place the value 
	    {
        sudoku[y][x] = pos[y][x][h];
        if (solution(sudoku, row, colum, box)){return true;} // if it's fine to place the value then place otherwise we restore every thing.
        sudoku[y][x] = 0;
        row[y][pos[y][x][h] - 1] = 1;
        colum[x][pos[y][x][h] - 1] = 1;
        box[which_box(x, y) - 1][pos[y][x][h] - 1] = 1;
	    }
    }
  return false;
  
}

vector<vector<vector<int>>> which_digit(int row[][SIZE], int colum[][SIZE], int box[][SIZE], int sudoku[][SIZE])
{
  /*
  this function return a three dimensional array with [y][x].size() = all the possible values to place in this cell
  */
	
  vector<vector<vector<int>>> what_to_put;
  
  for (int i = 0; i < SIZE; i++) 
  {
    vector<vector<int>> y;
	
    for(int j = 0; j < SIZE; j++)
    {
      vector<int> x;
	  
      if (sudoku[i][j] == 0)
      {
        for(int h = 0; h < SIZE; h++)
        {
          if (row[i][h] && colum[j][h] && box[which_box(j, i) - 1][h])
          {
            x.push_back(h + 1);
          }
        }
      }
      y.push_back(x);
    }
    what_to_put.push_back(y);
  }

  return what_to_put;
}

bool find_loc(int sudoku[][SIZE], int &x, int &y)
{
	//this function finds a cell that doesn't have a value in it
  for(y = 0; y < SIZE; y++)
  {
    for (x = 0; x < SIZE; x++)
    {
      if (sudoku[y][x] == 0) {return true;}
    }
  }
  return false;
}

bool is_safe( int row[][SIZE], int colum[][SIZE], int box[][SIZE], int num, int x, int y)
{
  num -= 1; // because the indexing is one less than the value
  
  if (row[y][num] && colum[x][num] && box[which_box(x, y) - 1][num]) {return true;}

  return false;
}


int which_box(int x, int y)
{
  int box_nu;
  /*
  box map:
  
  *---------------------------------------*
  |         |              |              |
  |    1    |       2      |       3      |
  |         |              |              |
  |---------------------------------------|
  |         |              |              |
  |    4    |       5      |       6      |
  |         |              |              |
  |---------------------------------------|
  |         |              |              |
  |    7    |       8      |      9       |
  |         |              |              |
  *---------------------------------------*
  */
  if (y < 3)
  {
    if (x < 3) {box_nu = 1;}
    else if(x >= 3 && x < 6) {box_nu = 2;}
    else {box_nu = 3;}
  }
  else if (y >= 3 && y < 6)
  {
    if (x < 3) {box_nu = 4;}
    else if(x >= 3 && x < 6) {box_nu = 5;}
    else {box_nu = 6;}
  }
  else
  {
    if (x < 3) {box_nu = 7;}
    else if(x >= 3 && x < 6) {box_nu = 8;}
    else {box_nu = 9;}
  }

  return box_nu;
}

void set_row(int row[][SIZE], int sudoku[][SIZE])
{
	
  for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++) {row[i][j] = 1;}
  }
  for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (sudoku[i][j] != 0) {row[i][sudoku[i][j] - 1] = 0;}
    }
  }
}

void set_colum(int colum[][SIZE], int sudoku[][SIZE])
{
	
  for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++) {colum[i][j] = 1;}
  }
  for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if(sudoku[j][i] != 0) {colum[i][sudoku[j][i] - 1] = 0;}
    }
  }
}

void print_sudoku(int sudoku[][SIZE])
{
  
  cout << endl << endl;
  
  for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      cout << sudoku[i][j] << "  ";
    }
  
	cout << endl << endl;
  }
}

void set_box(int box[][SIZE], int sudoku[][SIZE])
{
  
  for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++) {box[i][j] = 1;}
  }
  for (int i = 0; i < SIZE; i++)
  {
    for( int j = 0; j < SIZE; j++)
    {
      if(sudoku[i][j] != 0) {box[which_box(j, i) - 1][sudoku[i][j] - 1] = 0;}
    }
  }
}




