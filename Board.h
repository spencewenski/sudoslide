#ifndef BOARD_H
#define BOARD_H 1

#include <vector>
#include <memory>

struct Square;

class Board {
public:
  Board(int id_, int size_);

  void slide_col(int col_num, int slide_amount);
  void slide_row(int row_num, int slide_amount);
  void scramble_board();
  
  void broadcast_info();
  // debugging
  void print_board();
private:
  using Square_ptr_t = std::shared_ptr<Square>;
  using Square_vector_t = std::vector<Square_ptr_t>;
  using Board_graph_t = std::vector<Square_vector_t>;

  int id;
  int size;
  Board_graph_t board;

  int convert_neg_to_pos(int neg_val);
  std::vector<int> Square_vector_to_int_vector(Square_vector_t square_vector);
};

#endif /*BOARD_H*/