#ifndef VIEW_H
#define VIEW_H 1

#include <vector>

class View {
public:
  virtual ~View() {}
  virtual void draw() = 0;
  virtual void update_row(int id, int row_num, int slide_amount, std::vector<int> row);
  virtual void update_col(int id, int col_num, int slide_amount, std::vector<int> col);
  virtual void update_board(int id, int size);

private:
};

#endif /*VIEW_H*/