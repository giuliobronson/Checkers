#ifndef PIECE_H
#define PIECE_H

#include "Board.h"
#include "Spot.h"

class Piece
{
public:
  Piece(bool mWhite);

  bool isWhite();

  bool isKilled();

  void setKilled(bool killed);

  virtual bool canMove(Board board, Spot start, Spot end) const = 0;
  
private:
  bool mWhite;
  bool mKilled;
};

#endif