#include "View_board_list.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>

using std::cout; using std::endl;
using std::setw;
using std::vector;

void View_board_list::draw()
{
  cout << setw(5) << "id" << setw(5) << "size" << endl;
  for (auto board_info : board_info_map) {
    cout << setw(5) << board_info.first;
    cout << setw(5) << board_info.second.size;
    cout << endl;
    draw_board(board_info.second.board);
    cout << endl;
  }
}

void View_board_list::update_row(int id, int row_num, int /*slide_amount*/, vector<int> row)
{
  assert(board_info_map.find(id) != board_info_map.end());
  auto& board = board_info_map[id].board;
  assert(!(static_cast<int>(board.size()) < row_num));
  assert(board.size() == row.size());

  board[row_num] = row;
}

void View_board_list::update_col(int id, int col_num, int /*slide_amount*/, vector<int> col)
{
  assert(board_info_map.find(id) != board_info_map.end());
  auto& board = board_info_map[id].board;
  assert(!(static_cast<int>(board.size()) < col_num));
  assert(board.size() == col.size());

  for (int i = 0; i < static_cast<int>(col.size()); ++i)
    board[i][col_num] = col[i];
}

void View_board_list::update_board(int id, int size, vector<vector<int>> board)
{
  board_info_map[id] = Board_info{size, board};
}

void View_board_list::draw_board(vector<vector<int>> board)
{
  for (const auto& row : board) {
    for (auto square : row) {
      cout << setw(3) << square;
    }
    cout << endl;
  }
}

void View_board_list::update_remove(int id)
{
  board_info_map.erase(id);
}