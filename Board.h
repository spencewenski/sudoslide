#ifndef BOARD_H
#define BOARD_H 1

#include <vector>
#include <memory>

struct Square;

class Board {
public:
  void col_slide(int col_num, int slide_amount);
  void row_slide(int row_num, int slide_amount);
  void scramble_board();
  
private:
  using Square_ptr_t = std::shared_ptr<Square>;
  using Row_t = std::vector<Square_ptr_t>;
  using Board_graph_t = std::vector<Row_t>;

  Board_graph_t board;
  
};

#endif /*BOARD_H*/