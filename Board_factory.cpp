#include "Board_factory.h"
#include "Board.h"

using std::make_shared;
using std::shared_ptr;

shared_ptr<Board> create_board(int size)
{
  static int id_counter{};
  return make_shared<Board>(id_counter++, size);
}