#ifndef BOARD_H
#define BOARD_H 1

#include <vector>
#include <memory>

#include <iosfwd>

struct Square;

class Board {
public:
  Board(int id_, int size_);

  int get_id() const { return id; }

  bool is_solved();

  void slide_col(int col_num, int slide_amount, bool track_slide = true);
  void slide_row(int row_num, int slide_amount, bool track_slide = true);

  void solve();
  // void solve_instant();
  void restore_original();

  void undo();

  
  void broadcast_state();

private:
  using Square_ptr_t = std::shared_ptr<Square>;
  using Square_vector_t = std::vector<Square_ptr_t>;
  using Board_graph_t = std::vector<Square_vector_t>;

  int id;
  int size;
  Board_graph_t board;
  Board_graph_t original_board;

  struct Slide {
    bool row_col; // true = col, false = row
    int row_col_num, slide_amount;
    Slide opposite()
      { return Slide{row_col, row_col_num, slide_amount * -1}; }
  };
  friend std::ostream& operator<< (std::ostream& os, const Slide& slide);
  std::vector<Slide> solution;
  std::vector<Slide> player_slides;

  void scramble_board(int scramble_quality);
  int convert_neg_to_pos(int neg_val);
  std::vector<int> Square_vector_to_int_vector(const Square_vector_t& square_vector);
  std::vector<std::vector<int>> Board_to_int_board();
  Square_vector_t slide_row_no_notify(int row_num, int slide_amount);
  Square_vector_t slide_col_no_notify(int col_num, int slide_amount);
};

std::ostream& operator<< (std::ostream& os, const Board::Slide& slide);

#endif /*BOARD_H*/