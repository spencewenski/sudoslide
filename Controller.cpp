#include "Controller.h"
#include "Utility.h"
#include "Model.h"
#include "Board.h"
#include "Board_factory.h"
#include "View.h"
#include "View_board_list.h"
#include <iostream>
#include <string>

using std::cout; using std::endl; using std::cin;
using std::string;
using std::make_shared;

const int default_board_size_c = 4;

static int read_int();

Controller::Controller()
{
  commands["slide_col"] = &Controller::slide_col;
  commands["slide_row"] = &Controller::slide_row;
  commands["add_board"] = &Controller::add_board;
  commands["show"] = &Controller::show;
}

void Controller::run()
{
  string command;
  while (true) {
    try {
      cout << "\nEnter command: ";
      cin >> command;
      if (command == "quit") {
        cout << "Done" << endl;
        return;
      }
      auto command_itr = commands.find(command);
      if (command_itr == commands.end())
        throw Error{"Invalid command!"};
      (this->*(command_itr->second))();

    } // try
    catch (Error &error) {
      cout << error.what() << endl;
      while (cin.get() != '\n'); 
    }
    catch (std::exception &error) {
      cout << error.what() << endl;
      cout << "Done" << endl;
      return;
    }
    catch (...) {
      cout << "Unknown exception caught!" << endl;
      cout << "Done" << endl;
      return;
    }
  }
}

void Controller::slide_col()
{
  int board_id = read_int();
  int col_num = read_int();
  int slide_amount = read_int();
  auto board_ptr = Model::get().get_board(board_id);
  board_ptr->slide_col(col_num, slide_amount);
}

void Controller::slide_row()
{
  int board_id = read_int();
  int row_num = read_int();
  int slide_amount = read_int();
  auto board_ptr = Model::get().get_board(board_id);
  board_ptr->slide_row(row_num, slide_amount);
}

void Controller::add_board()
{
  int board_id = Model::get().get_next_board_id();
  auto board_ptr = create_board(board_id, default_board_size_c);
  board_ptr->scramble_board();
  Model::get().add_board(board_id, board_ptr);
  open_list_view();
}

void Controller::open_list_view()
{
  if (views.find("list_view") != views.end())
    return;
  auto view_ptr = make_shared<View_board_list>();
  views["list_view"] = view_ptr;
  Model::get().attach_view(view_ptr);
}

void Controller::show()
{
  for (auto view : views)
    view.second->draw();
}

int read_int()
{
  int val;
  if (!(cin >> val)) {
    cin.clear();
    throw Error{"Expected an integer value!"};
  }
  return val;
}