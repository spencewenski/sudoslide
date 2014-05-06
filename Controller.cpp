#include "Controller.h"

Controller::Controller()
{
  commands["slide"] = &Controller::slide;
  commands["add_board"] = &Controller::create_board;
}

void Controller::run()
{

}

void Controller::slide()
{

}
void Controller::create_board()
{

}
