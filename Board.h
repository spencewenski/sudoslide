#ifndef BOARD_H
#define BOARD_H 1

#include <vector>
#include <memory>

struct Square;

class Board {
public:
  Board(int size_);

  void slide_col(int col_num, int slide_amount);
  void slide_row(int row_num, int slide_amount);
  void scramble_board();
  
  // debugging
  void print_board();
private:
  using Square_ptr_t = std::shared_ptr<Square>;
  using Row_t = std::vector<Square_ptr_t>;
  using Board_graph_t = std::vector<Row_t>;

  int size;
  Board_graph_t board;

  int convert_neg_to_pos(int neg_val);
};

#endif /*BOARD_H*/