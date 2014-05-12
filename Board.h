#ifndef BOARD_H
#define BOARD_H 1

#include <vector>
#include <memory>

struct Square;

class Board {
public:
  Board(int id_, int size_);

  // implement and utilize
  bool is_solved() { return false; }

  void slide_col(int col_num, int slide_amount);
  void slide_row(int row_num, int slide_amount);
  void restore_original();
  
  void broadcast_state();

private:
  using Square_ptr_t = std::shared_ptr<Square>;
  using Square_vector_t = std::vector<Square_ptr_t>;
  using Board_graph_t = std::vector<Square_vector_t>;

  int id;
  int size;
  Board_graph_t board;
  Board_graph_t original_board;

  void scramble_board();
  int convert_neg_to_pos(int neg_val);
  std::vector<int> Square_vector_to_int_vector(const Square_vector_t& square_vector);
  std::vector<std::vector<int>> Board_to_int_board();
  Square_vector_t slide_row_no_notify(int row_num, int slide_amount);
  Square_vector_t slide_col_no_notify(int col_num, int slide_amount);
};

#endif /*BOARD_H*/