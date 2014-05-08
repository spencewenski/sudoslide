#include "Controller.h"
#include "Utility.h"
#include <iostream>
#include <string>

using std::cout; using std::endl; using std::cin;
using std::string;

Controller::Controller()
{
  commands["slide"] = &Controller::slide;
  commands["add_board"] = &Controller::create_board;
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

void Controller::create_board()
{

}
