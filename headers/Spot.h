#ifndef SPOT_H
#define SPOT_H

#include "Piece.h"

class Spot
{
public:
  Spot(int mX, int mY, Piece *piece);

  int getX();

  void setX(int x);

  int getY();

  void setY(int y);

  Piece *getPiece();

  void setPiece(Piece *piece);

private:
  int mX;
  int mY;
  Piece *mPiece;
};

#endif