#include "Controller.h"
#include "Utility.h"
#include "Model.h"
#include "Board_factory.h"
#include <iostream>
#include <string>

using std::cout; using std::endl; using std::cin;
using std::string;

const int default_board_size = 4;

Controller::Controller()
{
  commands["slide"] = &Controller::slide;
  commands["add_board"] = &Controller::add_board;
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
      error.what();
      while (cin.get() != '\n'); 
    }
    catch (std::exception &error) {
      error.what();
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

void Controller::slide()
{

}

void Controller::add_board()
{
  int board_id = Model::get_instance().get_next_board_id();
  auto board_ptr = create_board(default_board_size);
  Model::get_instance().add_board(board_id, board_ptr);
}
