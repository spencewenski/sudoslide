#ifndef VIEW_H
#define VIEW_H 1

#include <vector>

class View {
public:
  virtual ~View() {}
  virtual void draw() = 0;
  virtual void update_row(int row_num, int slide_amount, std::vector<int> row);
  virtual void update_col(int col_num, int slide_amount, std::vector<int> col);

private:
};

#endif /*VIEW_H*/