#include "Functions.h"


bool solution_p(int sudoku[][SIZE], int row[][SIZE], int colum[][SIZE], int box[][SIZE], vector<vector<vector<int>>> possibility)
{
  int local_row   [SIZE][SIZE];
  int local_colum [SIZE][SIZE];
  int local_box   [SIZE][SIZE];
  int local_sudoku[SIZE][SIZE];
  copy_arr(local_sudoku, sudoku);
  copy_arr(local_row,       row);
  copy_arr(local_colum,   colum);
  copy_arr(local_box,       box);
  set_row(local_row,     local_sudoku);
  set_colum(local_colum, local_sudoku);
  set_box(local_box,     local_sudoku);

  vector<vector<vector<int>>> local_possibility;
  local_possibility =  which_digit_p(local_row, local_colum, local_box, local_sudoku);

  for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if(local_sudoku[i][j] == 0)
      {
        for(int h = 0; h < local_possibility[i][j].size(); h++)
        {
			if(local_row[i][local_possibility[i][j][h] - 1] && local_colum[j][local_possibility[i][j][h] - 1] && local_box[which_box(j, i) - 1][local_possibility[i][j][h] - 1])
			{
            
            local_sudoku[i][j] = local_possibility[i][j][h];
            local_row[i][local_possibility[i][j][h] - 1] = 0;
            local_colum[j][local_possibility[i][j][h] - 1] = 0;
            local_box[which_box(i, j) - 1][local_possibility[i][j][h] - 1] = 0;
            break;
			}
        }
      }
    }
  } 
  if(no_zero(local_sudoku))
  {
    print_sudoku(local_sudoku);
  }
  return true;
}

int which_digit(int x, int y, int row[][SIZE], int colum[][SIZE], int box[][SIZE])
{
  int digit = -1;
  for (int i = 0; i < SIZE; i++) 
  {
    if (row[y][i] && colum[x][i] && box[which_box(x, y) - 1][i])
    {
      digit = i;
      row[y][i] = 0;
      colum[x][i] = 0;
      box[which_box(x, y) - 1][i] = 0;
      break;
    }
  }
  return digit;
}

int which_box(int x, int y)
{
  int box_nu;
  /*
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
    if (x < 3)
      box_nu = 1;
    else if(x >= 3 && x < 6)
      box_nu = 2;
    else 
      box_nu = 3;
  }
  else if (y >= 3 && y < 6)
  {
    if (x < 3)
      box_nu = 4;
    else if(x >= 3 && x < 6)
      box_nu = 5;
    else 
      box_nu = 6;
  }
  else
  {
    if (x < 3)
      box_nu = 7;
    else if(x >= 3 && x < 6)
      box_nu = 8;
    else 
      box_nu = 9;
  }

  return box_nu;
}

void set_row(int row[][SIZE], int sudoku[][SIZE])
{
  for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      row[i][j] = 1;
    }
  }
  for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (sudoku[i][j] != 0)
      {
        row[i][sudoku[i][j] - 1] = 0;
      }
    }
  }
}

void set_colum(int colum[][SIZE], int sudoku[][SIZE])
{
  for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      colum[i][j] = 1;
    }
  }
  for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if(sudoku[j][i] != 0)
        colum[i][sudoku[j][i] - 1] = 0;
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
    for (int j = 0; j < SIZE; j++)
    {
      box[i][j] = 1;
    }
  }
  for (int i = 0; i < SIZE; i++)
  {
    for( int j = 0; j < SIZE; j++)
    {
      if(sudoku[i][j] != 0)
        box[which_box(j, i) - 1][sudoku[i][j] - 1] = 0;
    }
  }
}

bool no_zero(int sudoku[][SIZE])
{
  bool no = true;

  for(int i = 0; i < SIZE; i++)
  {
    for(int j = 0; j < SIZE; j++)
    {
      if(sudoku[i][j] == 0)
      {
        no = false;
      }
    }
  }
  
  return no;
}

vector<vector<vector<int>>> which_digit_p(int row[][SIZE], int colum[][SIZE], int box[][SIZE], int sudoku[][SIZE])
{
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

void solution(int sudoku[][SIZE], int row[][SIZE], int colum[][SIZE], int box[][SIZE])
{
  for(int i = 0; i < SIZE; i++)
  {
    for(int j = 0; j < SIZE; j++)
    {
      if(sudoku[i][j] == 0)
      {
        //cout << which_digit(j, i, row, colum, box) << endl;
        sudoku[i][j] = which_digit(j, i, row, colum, box) + 1;
      }
    }
  }
}

vector<vector<vector<int>>> solution_basic(int sudoku[][SIZE], int row[][SIZE], int colum[][SIZE], int box[][SIZE], vector<vector<vector<int>>> possibility)
{
   for(int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
     if (possibility[i][j].size() == 1)
     {
       sudoku[i][j] = possibility[i][j][0];
       row[i][possibility[i][j][0] - 1] = 0;
       colum[j][possibility[i][j][0] - 1] = 0;
       box[which_box(i, j) - 1][possibility[i][j][0] - 1] = 0; 
       possibility = which_digit_p(row, colum, box, sudoku);
       solution_basic(sudoku, row, colum, box, possibility);
     }
    }
  } 
  return possibility;
}

void copy_arr(int arr_1[][SIZE], int arr_2[][SIZE])
{
  for(int i = 0; i < SIZE; i++)
  {
    for(int j = 0; j < SIZE; j++)
    {
      arr_1[i][j] = arr_2[i][j];
    }
  } 
}

