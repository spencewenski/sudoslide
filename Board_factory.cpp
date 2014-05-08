#include "Board_factory.h"
#include "Board.h"

using std::make_shared;
using std::shared_ptr;

shared_ptr<Board> create_board()
{
  return make_shared<Board>();
}