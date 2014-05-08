#ifndef BOARD_FACTORY_H
#define BOARD_FACTORY_H 1

#include <memory>

class Board;

std::shared_ptr<Board> create_board(int size);

#endif /*BOARD_FACTORY_H*/