#ifndef CONTROLLER_H
#define CONTROLLER_H 1

#include <map>
#include <string>
#include <memory>

class View;

class Controller {
public:
  Controller();
  void run();
private:
  using Command_fp_t = void (Controller::*)();
  using Command_map_t = std::map<std::string, Command_fp_t>;
  using View_ptr_t = std::shared_ptr<View>;
  using View_list_t = std::map<std::string, View_ptr_t>;

  Command_map_t commands;
  View_list_t views;

  void help();

  void slide_col();
  void slide_row();
  void undo();
  void add_board();
  void remove_board();
  void restore_original();
  void solve_board();

  void show();

  /*utilities*/

  // view is automatically opened
  void open_list_view();
  void close_list_view();
};

#endif /*CONTROLLER_H*/