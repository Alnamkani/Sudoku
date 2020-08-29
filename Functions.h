#include <iostream>
#include <vector>
using namespace std;
#define SIZE 9
#pragma onec



bool solution_p(int sudoku[][SIZE], int row[][SIZE], int colum[][SIZE], int box[][SIZE], vector<vector<vector<int>>> possibility);
void copy_arr(int arr_1[][SIZE], int arr_2[][SIZE]);
void set_row(int row[][SIZE], int sudoku[][SIZE]);
void set_colum(int colum[][SIZE], int sudoku[][SIZE]);
void set_box(int box[][SIZE], int sudoku[][SIZE]);
void print_sudoku(int sudoku[][SIZE]);
int which_box(int x, int y);
void solution(int sudoku[][SIZE], int row[][SIZE], int colum[][SIZE], int box[][SIZE]);
int which_digit(int x, int y, int row[][SIZE], int colum[][SIZE], int box[][SIZE]);
bool no_zero(int sudoku[][SIZE]);
vector<vector<vector<int>>> which_digit_p(int row[][SIZE], int colum[][SIZE], int box[][SIZE], int sudoku[][SIZE]);
vector<vector<vector<int>>> solution_basic(int sudoku[][SIZE], int row[][SIZE], int colum[][SIZE], int box[][SIZE], vector<vector<vector<int>>> possibility);