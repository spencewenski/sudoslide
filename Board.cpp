#include "Board.h"

using std::vector;
using std::make_shared;

struct Square {
  Square(int num_) : num{num_} {}
  int num;
};

Board::Board(int size_)
: size{size_}, board(size)
{
  int count{};
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      board[i].push_back(make_shared<Square>(count++));
    }
  }
}

void Board::col_slide(int col_num, int slide_amount)
{
  Row_t new_col(size);
  for (int i = 0; i < size; ++i) {
    new_col[slide_amount % size] = board[col_num][i];
  }
}

void Board::row_slide(int /*row_num*/, int /*slide_amount*/)
{

}

void Board::scramble_board()
{
  
}
