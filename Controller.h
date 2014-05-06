#ifndef CONTROLLER_H
#define CONTROLLER_H 1

#include <map>
#include <string>

class Controller {
public:
  Controller();
  void run();
private:
  using Command_fp_t = void (Controller::*)();
  using Command_map_t = std::map<std::string, Command_fp_t>;

  Command_map_t commands;

  void slide();
  void create_board();
  void open_view();
};

#endif /*CONTROLLER_H*/