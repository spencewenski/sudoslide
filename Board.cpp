#include "Board.h"
#include "Model.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>
using std::cout; using std::endl;

using std::vector;
using std::make_shared;

struct Square {
  Square(int num_) : num{num_} {}
  int num;
};


Board::Board(int id_, int size_)
: id{id_}, size{size_}, board(size)
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
  if (col_num > size)
    throw Error{"Column does not exist!"};
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

  Model::get().notify_row(id, col_num, slide_amount, 
    Square_vector_to_int_vector(new_col));

  cout << "After:" << endl;
  print_board();
}

void Board::slide_row(int row_num, int slide_amount)
{
  if (row_num > size)
    throw Error{"Row does not exist!"};
  if (slide_amount < 0)
    slide_amount = convert_neg_to_pos(slide_amount);
  cout << "Before:" << endl;
  print_board();
  Square_vector_t new_row(size);
  for (int i = 0; i < size; ++i) {
    new_row[(slide_amount + i) % size] = board[row_num][i];
  }
  board[row_num] = new_row;

  Model::get().notify_row(id, row_num, slide_amount, 
    Square_vector_to_int_vector(new_row));

  cout << "After:" << endl;
  print_board();
}

vector<int> Board::Square_vector_to_int_vector(const Square_vector_t& square_vector)
{
  vector<int> new_vector;
  for (auto square_ptr : square_vector)
    new_vector.push_back(square_ptr->num);
  return new_vector;
}

vector<vector<int>> Board::Board_to_int_board()
{
  vector<vector<int>> int_board;
  for (const auto& row : board) {
    int_board.push_back(Square_vector_to_int_vector(row));
  }
  return int_board;
}


int Board::convert_neg_to_pos(int neg_val)
{
  return size + neg_val;
}

void Board::scramble_board()
{
  
}

void Board::broadcast_state()
{
  Model::get().notify_state(id, size, Board_to_int_board());
}


void Board::print_board()
{
  for (const auto& row : board) {
    for (const auto square_ptr : row) {
      cout << std::setw(2) << square_ptr->num << ' ';
    }
    cout << endl;
  }
}
