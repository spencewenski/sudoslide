#include "Model.h"
#include "Utility.h"
#include "Board.h"
#include "View.h"
#include <algorithm>

using std::for_each;
using std::bind;
using namespace std::placeholders;
using std::vector;

Model& Model::get()
{
  static Model model;
  return model;
}

bool Model::does_board_exist(int id)
{
  return boards.find(id) != boards.end();
}

Model::Board_ptr_t Model::get_board(int id)
{
  if (!does_board_exist(id))
    throw Error{"Board does not exist!"};
  return boards[id];
}

void Model::add_board(int id, Board_ptr_t board_ptr)
{
  assert(!does_board_exist(id));
  boards[id] = board_ptr;
  board_ptr->broadcast_state();
}

void Model::remove_board(int id)
{
  if (!does_board_exist(id))
    throw Error{"Board does not exist!"};
  boards.erase(id);
  notify_remove(id);
}

void Model::notify_remove(int id)
{
  for_each(views.begin(), views.end(),
    bind(&View::update_remove, _1, id));
}

void Model::notify_col(int id, int col_num, int slide_amount, vector<int> col)
{
  for_each(views.begin(), views.end(),
    bind(&View::update_col, _1, id, col_num, slide_amount, col));
}

void Model::notify_row(int id, int row_num, int slide_amount, vector<int> row)
{
  for_each(views.begin(), views.end(),
    bind(&View::update_row, _1, id, row_num, slide_amount, row));
}

void Model::notify_state(int id, int size, vector<vector<int>> board)
{
  for_each(views.begin(), views.end(),
    bind(&View::update_board, _1, id, size, board));
}

void Model::attach_view(View_ptr_t view_ptr)
{
  views.insert(view_ptr);
  // add bind
  for_each(boards.begin(), boards.end(), 
    bind(&Board::broadcast_state,
      bind(&Board_map_t::value_type::second, _1)));
}

void Model::detach_view(View_ptr_t view_ptr)
{
  views.erase(view_ptr);
}


