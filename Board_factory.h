#ifndef BOARD_FACTORY_H
#define BOARD_FACTORY_H 1

#include <memory>

class Board;

std::shared_ptr<Board> create_board();

#endif /*BOARD_FACTORY_H*/