#ifndef VIEW_BOARD_LIST_H
#define VIEW_BOARD_LIST_H 1

#include "View.h"
#include <map>
#include <vector>

class View_board_list : public View {
public:
  void draw() override;
  void update_row(int id, int row_num, int slide_amount, std::vector<int> row) override;
  void update_col(int id, int col_num, int slide_amount, std::vector<int> col) override;
  void update_board(int id, int size, std::vector<std::vector<int>> board) override;
  void update_remove(int id) override;
private:
  struct Board_info {
    int size;
    std::vector<std::vector<int>> board;
  };
  std::map<int, Board_info> board_info_map;

  void draw_board(std::vector<std::vector<int>> board);
};

#endif /*VIEW_BOARD_LIST_H*/