#include "Board.h"
#include "Man.h"

Board::Board() {
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if(i >= 0 && i <= 2 && j % 2 != i % 2)
        boxes[i][j] = new Spot(i, j, new Man(false));
      else if(i >= 5 && i <= 7 && j % 2 != i % 2)
        boxes[i][j] = new Spot(i, j, new Man(true));
      else
        boxes[i][j] = new Spot(i, j, nullptr);
    }
  }
}