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

static int read_int();

Controller::Controller()
{
  commands["help"] = &Controller::help;
  commands["slide_col"] = &Controller::slide_col;
  commands["slide_row"] = &Controller::slide_row;
  commands["undo"] = &Controller::undo;
  commands["add_board"] = &Controller::add_board;
  commands["remove_board"] = &Controller::remove_board;
  commands["restore_original"] = &Controller::restore_original;
  commands["solve_board"] = &Controller::solve_board;
  commands["show"] = &Controller::show;
  commands["open_list_view"] = &Controller::open_list_view;
  commands["close_list_view"] = &Controller::close_list_view;
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

void Controller::help()
{
  // description
  cout << "\nDESCRIPTION" << endl;
  cout << "\tSudoslide is a sliding-based puzzle game. It features puzzle\n"
       << "\tmechanics similar to a Rubik's cube: trying to solve one part of\n"
       << "\tthe puzzle might mess up other parts. A board starts out\n"
       << "\tscrambled, and the goal of the game is to rearrange the numbers\n"
       << "\ton the board so they are in order. For example, for a board of\n"
       << "\tsize 4, it would start out looking something like this:\n\n"
         << "\t\t 4  3 10  1\n"
         << "\t\t11  2  8  5\n"
         << "\t\t 6 12  7 13\n"
         << "\t\t14  9 15  0\n\n"
       << "\tand the solved board would look like this:\n\n"
         << "\t\t 0  1  2  3\n"
         << "\t\t 4  5  6  7\n"
         << "\t\t 8  9 10 11\n"
         << "\t\t12 13 14 15" << endl;
  // commands
  cout << "\nCOMMANDS" << endl;
  // help
  cout << "\thelp" << endl;
  cout << "\t\tdisplay this screen" << endl;
  // slide_col
  cout << "\n\tslide_col <board_id> <col_num> <slide_amount>" << endl;
  cout << "\t\tslide a column up or down; positive slide_amount for up,\n"
       << "\t\tnegative for down\n"
       << "\t\terror: board does not exist, column does not exist, unable to\n"
       << "\t\tread integer values" << endl;
  // slide_row
  cout << "\n\tslide_row <board_id> <row_num> <slide_amount>" << endl;
  cout << "\t\tslide a row right or left; positive slide_amount for right,\n"
       << "\t\tnegative for left;\n"
       << "\t\terror: board does not exist, row does not exist, unable to read\n"
       << "\t\tinteger values" << endl;
  // undo
  cout << "\n\tundo <board_id>" << endl;
  cout << "\t\tundo previous slides until there are no more slides to undo;\n"
       << "\t\terror: no more moves to undo" << endl;
  // add_board
  cout << "\n\tadd_board <board_size>" << endl;
  cout << "\t\tcreate a new board of the specified size and add to the\n"
       << "\t\tappropriate views" << endl;
  // remove_board
  cout << "\n\tremove_board <board_id>" << endl;
  cout << "\t\tremove a board from the game;\n"
       << "\t\terror: board does not exist, unable to read integer value" << endl;
  // restore_original
  cout << "\n\trestore_original <board_id>" << endl;
  cout << "\t\trestore a board to its original state;\n"
       << "\t\terror: board does not exist, unable to read integer value" << endl;
  // solve_board
  cout << "\n\tsolve_board <board_id>" << endl;
  cout << "\t\tsolve the board step by step from original state;\n"
       << "\t\terror: board does not exist, unable to read integer value" << endl;
  // shoe
  cout << "\n\tshow" << endl;
  cout << "\t\tdisplay all the open views" << endl;
  // open_list_view
  cout << "\n\topen_list_view" << endl;
  cout << "\t\topen the list view;\n"
       << "\t\terror: list view already open" << endl;
  // close_list_view
  cout << "\n\tclose_list_view" << endl;
  cout << "\t\tclose the list view;\n"
       << "\t\terror: list view is not open" << endl;
}

void Controller::slide_col()
{
  int board_id = read_int();
  int col_num = read_int();
  int slide_amount = read_int();
  auto board_ptr = Model::get().get_board(board_id);
  board_ptr->slide_col(col_num, slide_amount);
  if (board_ptr->is_solved()) {
    cout << "Solved!" << endl;
  }
}

void Controller::slide_row()
{
  int board_id = read_int();
  int row_num = read_int();
  int slide_amount = read_int();
  auto board_ptr = Model::get().get_board(board_id);
  board_ptr->slide_row(row_num, slide_amount);
  if (board_ptr->is_solved()) {
    cout << "Solved!" << endl;
  }
}

void Controller::undo()
{
  int board_id = read_int();
  auto board_ptr = Model::get().get_board(board_id);
  board_ptr->undo();
}

void Controller::add_board()
{
  int board_size = read_int();
  auto board_ptr = create_board(board_size);
  Model::get().add_board(board_ptr->get_id(), board_ptr);
}

void Controller::remove_board()
{
  int board_id = read_int();
  Model::get().remove_board(board_id);
}


void Controller::open_list_view()
{
  if (views.find("list_view") != views.end())
    throw Error{"List view is already open!"};
  auto view_ptr = make_shared<View_board_list>();
  views["list_view"] = view_ptr;
  Model::get().attach_view(view_ptr);
}

void Controller::close_list_view()
{
  auto view_itr = views.find("list_view");
  if (view_itr == views.end())
    throw Error{"List view is not open!"};
  Model::get().detach_view(view_itr->second);
  views.erase(view_itr);
}

void Controller::restore_original()
{
  int board_id = read_int();
  auto board_ptr = Model::get().get_board(board_id);
  board_ptr->restore_original();
}

void Controller::solve_board()
{
  int board_id = read_int();
  auto board_ptr = Model::get().get_board(board_id);
  board_ptr->solve();
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