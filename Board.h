#ifndef BOARD_H
#define BOARD_H 1

#include <memory>
#include <vector>

struct Square;

class Board {
public:
  Board(int size_);
  ~Board() = default;



  void slide_row(int row_num, int slide_amount = 1);
  void slide_col(int col_num, int slide_amount = 1);
private:
  int size; // size of the puzzle (number of rows and cols)
  using Row_t = std::vector<std::unique_ptr<Square>>;
  using Board_list_t = std::vector<Row_t>;

  Board_list_t board;

};

#endif