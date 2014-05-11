#ifndef MODEL_H
#define MODEL_H 1

#include <string>
#include <map>
#include <set>
#include <memory>
#include <vector>

class Board;
class View;

class Model {
  using Board_ptr_t = std::shared_ptr<Board>;
  using View_ptr_t = std::shared_ptr<View>;
public:
  static Model& get();

  int get_next_board_id();
  bool does_board_exist(int id);
  Board_ptr_t get_board(int id);
  void add_board(int id, Board_ptr_t board_ptr);
  void remove_board(int id);

  void notify_col(int id, int col_num, int slide_amount, std::vector<int> col);
  void notify_row(int id, int row_num, int slide_amount, std::vector<int> row);
  void notify_state(int id, int size, std::vector<std::vector<int>> board);

  void attach_view(View_ptr_t view_ptr);
  void detach_view(View_ptr_t view_ptr);

private:
  using Board_map_t = std::map<int, Board_ptr_t>;
  using View_map_t = std::set<View_ptr_t>;

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