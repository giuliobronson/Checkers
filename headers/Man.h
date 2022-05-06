#ifndef MAN_H
#define MAN_H

#include "Piece.h"

class Man : public Piece
{
public:
  Man(bool white);

  bool isCrowned();

  void setCrowned(bool crowned);

  virtual bool canMove(Board board, Spot start, Spot end) const;

private:
  bool mCrowned;
};

#endif