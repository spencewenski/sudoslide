#ifndef MODEL_H
#define MODEL_H 1

#include <string>
#include <map>
#include <memory>
#include <vector>

class Board;
class View;

class Model {
  using Board_ptr_t = std::shared_ptr<Board>;
  using View_ptr_t = std::shared_ptr<View>;
public:
  static Model& get_instance();

  int get_next_board_id();
  bool does_board_exist(int id);
  Board_ptr_t get_board(int id);
  void add_board(int id, Board_ptr_t board_ptr);
  void remove_board(int id);

  void notify_row(std::vector<int> row);
  void notify_col(std::vector<int> col);

  void attach_view(std::string name, View_ptr_t view_ptr);
  void detach_view(std::string name);

private:
  using Board_map_t = std::map<int, Board_ptr_t>;
  using View_map_t = std::map<std::string, View_ptr_t>;

  Board_map_t boards;
  View_map_t views;
  int board_count{};

  Model() {}
  ~Model() {}
  Model(const Model&) = delete;
  Model& operator=(const Model&) = delete;
  Model(Model&&) = delete;
  Model& operator=(Model&&) = delete;
};

#endif /*MODEL_H*/