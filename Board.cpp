#include "Board.h"
#include "Model.h"
#include "Utility.h"
#include <random>

using std::vector;
using std::make_shared;

#include <iostream>
using std::cout; using std::endl;

// debugging
// #include <iostream>
// using std::cout; using std::endl;

struct Square {
  Square(int num_) : num{num_} {}
  int num;
};

std::ostream& operator<< (std::ostream& os, const Board::Slide& slide)
{
  os << "slide " << (slide.row_col ? "col" : "row") << ' '
     << slide.row_col_num << ' ' << slide.slide_amount << " units" << endl;
  return os;
}

Board::Board(int id_, int size_)
: id{id_}, size{size_}, board(size)
{
  // assert(size > 1);
  if (size < 2)
    throw Error{"Size of board is too small!"};
  int count{};
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      board[i].push_back(make_shared<Square>(count++));
    }
  }
  int scramble_quality = size * size;
  scramble_board(scramble_quality);
  original_board = board;
}

// !!! need to test
bool Board::is_solved()
{
  int count{};
  for (const auto& row : board) {
    for (auto square_ptr : row) {
      if (square_ptr->num != count++)
        return false;
    }
  }
  return true;
}


void Board::slide_col(int col_num, int slide_amount, bool track_slide)
{
  if (track_slide)
    player_slides.push_back(Slide{true, col_num, slide_amount});
  auto new_col = slide_col_no_notify(col_num, slide_amount);
  Model::get().notify_col(id, col_num, slide_amount, 
    Square_vector_to_int_vector(new_col));
}

void Board::slide_row(int row_num, int slide_amount, bool track_slide)
{
  if (track_slide)
    player_slides.push_back(Slide{false, row_num, slide_amount});
  auto new_row = slide_row_no_notify(row_num, slide_amount);
  Model::get().notify_row(id, row_num, slide_amount, 
    Square_vector_to_int_vector(new_row));
}

vector<int> Board::Square_vector_to_int_vector(const Square_vector_t& square_vector)
{
  vector<int> new_vector;
  for (auto square_ptr : square_vector)
    new_vector.push_back(square_ptr->num);
  return new_vector;
}

vector<vector<int>> Board::Board_to_int_board()
{
  vector<vector<int>> int_board;
  for (const auto& row : board) {
    int_board.push_back(Square_vector_to_int_vector(row));
  }
  return int_board;
}


void Board::restore_original()
{
  board = original_board;
  player_slides.clear();
  Model::get().notify_state(id, size, Board_to_int_board());
}


void Board::scramble_board(int scramble_quality)
{
  /* use random device after debugging */
  // static std::random_device rd;
  // static std::mt19937 gen(rd());
  static std::mt19937 gen;
  /* number distributions */
  // make these static?
  // distribution that decides whether to slide a row (0) or a column (1)
  static std::uniform_int_distribution<> row_or_col_bool_dis(0, 1);
  // distribution that selectrs row/column number
  std::uniform_int_distribution<> row_col_num_dis(0, size - 1);
  // distribution to decide the amount to slide the row or column
  std::uniform_int_distribution<> slide_amount_dis(-1 * (size - 1), size - 1);

  /* scramble the board */

  Slide slide;
  for (int i = 0; i < scramble_quality; ++i) {
    slide.row_col_num = row_col_num_dis(gen);
    slide.slide_amount = slide_amount_dis(gen);
    slide.row_col = row_or_col_bool_dis(gen);
    solution.push_back(slide);

    // true for column, false for row
    if (slide.row_col)
      slide_col_no_notify(slide.row_col_num, slide.slide_amount);
    else
      slide_row_no_notify(slide.row_col_num, slide.slide_amount);
  }
  Model::get().notify_state(id, size, Board_to_int_board());
}

void Board::solve()
{
  restore_original();
  for (int i = solution.size(); i-- > 0;) {
    const auto& slide = solution[i].opposite();
    cout << slide;
    if (slide.row_col)
      slide_col(slide.row_col_num, slide.slide_amount, false);
    else
      slide_row(slide.row_col_num, slide.slide_amount, false);
  }
}

void Board::undo()
{
  if (player_slides.empty())
    throw Error{"No moves to undo!"};
  auto slide = player_slides.back().opposite();
  player_slides.pop_back();
  if (slide.row_col)
    slide_col(slide.row_col_num, slide.slide_amount, false);
  else
    slide_row(slide.row_col_num, slide.slide_amount, false);
}


void Board::broadcast_state()
{
  Model::get().notify_state(id, size, Board_to_int_board());
}

Board::Square_vector_t Board::slide_row_no_notify(int row_num, int slide_amount)
{
  if (row_num >= size || row_num < 0)
    throw Error{"Row does not exist!"};
  if (slide_amount < 0)
    slide_amount = convert_neg_to_pos(slide_amount);
  Square_vector_t new_row(size);
  for (int i = 0; i < size; ++i) {
    new_row[(slide_amount + i) % size] = board[row_num][i];
  }
  board[row_num] = new_row;
  return new_row;
}

Board::Square_vector_t Board::slide_col_no_notify(int col_num, int slide_amount)
{
  if (col_num >= size || col_num < 0)
    throw Error{"Column does not exist!"};
  if (slide_amount < 0)
    slide_amount = convert_neg_to_pos(slide_amount);
  Square_vector_t new_col(size);
  for (int i = 0; i < size; ++i) {
    new_col[i] = board[(slide_amount + i) % size][col_num];
  }
  for (int i = 0; i < size; ++i) {
    board[i][col_num] = new_col[i];
  }
  return new_col;
}

/*
converts a negative slide value into its equivalent positive slide value
*/
int Board::convert_neg_to_pos(int neg_val)
{
  return size + neg_val;
}

