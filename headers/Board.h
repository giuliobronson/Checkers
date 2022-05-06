#ifndef BOARD_H
#define BOARD_H

#include "Spot.h"

class Board
{
public:
  Board();

private:
  Spot ***boxes;
};

#endif