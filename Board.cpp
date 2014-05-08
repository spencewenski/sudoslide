#include "Board.h"
#include "Model.h"
#include <iostream>
#include <iomanip>
using std::cout; using std::endl;

using std::vector;
using std::make_shared;

struct Square {
  Square(int num_) : num{num_} {}
  int num;
};

void Board::print_board()
{
  for (const auto& row : board) {
    for (const auto square_ptr : row) {
      cout << std::setw(2) << square_ptr->num << ' ';
    }
    cout << endl;
  }
}

Board::Board(int size_)
: size{size_}, board(size)
{
  int count{};
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      board[i].push_back(make_shared<Square>(count++));
    }
  }
  print_board();
}

void Board::slide_col(int col_num, int slide_amount)
{
  if (slide_amount < 0)
    slide_amount = convert_neg_to_pos(slide_amount);
  cout << "Before:" << endl;
  print_board();
  Square_vector_t new_col(size);
  for (int i = 0; i < size; ++i) {
    new_col[(slide_amount + i) % size] = board[i][col_num];
  }
  for (int i = 0; i < size; ++i) {
    board[i][col_num] = new_col[i];
  }

  Model::get().notify_row(col_num, slide_amount, 
    Square_vector_to_int_vector(new_col));

  cout << "After:" << endl;
  print_board();
}

void Board::slide_row(int row_num, int slide_amount)
{
  if (slide_amount < 0)
    slide_amount = convert_neg_to_pos(slide_amount);
  cout << "Before:" << endl;
  print_board();
  Square_vector_t new_row(size);
  for (int i = 0; i < size; ++i) {
    new_row[(slide_amount + i) % size] = board[row_num][i];
  }
  board[row_num] = new_row;

  Model::get().notify_row(row_num, slide_amount, 
    Square_vector_to_int_vector(new_row));

  cout << "After:" << endl;
  print_board();
}

vector<int> Board::Square_vector_to_int_vector(Square_vector_t square_vector)
{
  vector<int> new_vector;
  for (auto square_ptr : square_vector)
    new_vector.push_back(square_ptr->num);
  return new_vector;
}


int Board::convert_neg_to_pos(int neg_val)
{
  return size + neg_val;
}

void Board::scramble_board()
{
  
}
