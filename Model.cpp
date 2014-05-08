#include "Model.h"
#include "Utility.h"

Model& Model::get_instance()
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

void Model::attach_view(std::string name, View_ptr_t view_ptr)
{
  views[name] = view_ptr;
}

void Model::detach_view(std::string name)
{
  views.erase(name);
}


