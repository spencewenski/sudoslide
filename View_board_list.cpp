#include "View_board_list.h"

#include <iostream>
#include <iomanip>

using std::cout; using std::endl;
using std::setw;

void View_board_list::draw()
{
  cout << setw(5) << "id" << setw(5) << "size" << endl;
  for (auto board_info : board_info_map) {
    cout << setw(5) << board_info.first;
    cout << setw(5) << board_info.second.size;
    cout << endl;
  }
}

void View_board_list::update_board(int id, int size)
{
  board_info_map[id] = Board_info{size};
}