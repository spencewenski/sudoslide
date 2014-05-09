#ifndef VIEW_BOARD_LIST_H
#define VIEW_BOARD_LIST_H 1

#include "View.h"
#include <map>

class View_board_list : public View {
public:
  void draw() override;
  void update_board(int id, int size) override;
private:
  struct Board_info {
    int size;
  };
  std::map<int, Board_info> board_info_map;
};

#endif /*VIEW_BOARD_LIST_H*/