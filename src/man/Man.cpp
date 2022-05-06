#include "Man.h"

Man::Man(bool white) : Piece(white), mCrowned(false) {
}

bool Man::isCrowned() {
  return mCrowned;
}

void Man::setCrowned(bool crowned) {
  mCrowned = crowned;
}

bool Man::canMove(Board board, Spot start, Spot end) const {
  
}