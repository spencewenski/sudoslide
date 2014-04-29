#include "Board.h"
#include <utility>

using std::vector;
using std::unique_ptr;
using std::move;

struct Square {
  int val;
};

Board::Board(int size_)
: size{size_}
{
  int count{};
  for (int i = 0; i < size; ++i) {
    board.push_back(Row_t{});
    for (int j = 0; j < size; ++i)
      board[i].push_back(unique_ptr<Square>{new Square{count++}});
  }
}


void Board::slide_row(int row_num, int slide_amount)
{
  assert(row_num < size);
  Row_t& row = board[row_num];
  Square tmp;
  for (int i = 0; i < size; ++i) {
    tmp = move(row[i]);
    
  }

}
