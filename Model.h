#ifndef MODEL_H
#define MODEL_H 1

#include <string>
#include <map>
#include <memory>

class Board;

class Model {
  using Board_ptr_t = std::shared_ptr<Board>;
public:
  static Model& get_instance();

  int get_next_board_id();
  bool does_board_exist(int id);
  Board_ptr_t get_board(int id);
  void add_board(int id, Board_ptr_t board_ptr);
private:
  using Board_map_t = std::map<int, Board_ptr_t>;

  Board_map_t boards;
  int board_count{};

  Model() {}
  ~Model() {}
  Model(const Model&) = delete;
  Model& operator=(const Model&) = delete;
  Model(Model&&) = delete;
  Model& operator=(Model&&) = delete;
};

#endif /*MODEL_H*/