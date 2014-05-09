#include "Model.h"
#include "Utility.h"

#include <algorithm>

using std::for_each;

Model& Model::get()
{
  static Model model;
  return model;
}

int Model::get_next_board_id()
{
  return board_count++;
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
  // if (does_board_exist())
  //   throw Error{"Board already exists!"};
  assert((!does_board_exist(id), "Board already exists!"));
  boards[id] = board_ptr;
}

void Model::remove_board(int id)
{
  assert((!does_board_exist(id), "Board does not exist!"));
  boards.erase(id);
}

void Model::notify_col(int /*id*/, int /*col_num*/, int /*slide_amount*/, std::vector<int> /*col*/)
{

}

void Model::notify_row(int /*id*/, int /*row_num*/, int /*slide_amount*/, std::vector<int> /*row*/)
{

}



void Model::attach_view(View_ptr_t view_ptr)
{
  views.insert(view_ptr);
  // add bind
  for_each(boards.begin(), boards.end(), &Board::broadcast_board);
}

void Model::detach_view(View_ptr_t view_ptr)
{
  views.erase(view_ptr);
}


