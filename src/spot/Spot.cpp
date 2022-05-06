#include "Spot.h"

Spot::Spot(int mX, int mY, Piece *piece) : mX(mX), mY(mY), mPiece(mPiece) {
}

int Spot::getX() {
  return mX;
}

void Spot::setX(int x) {
  mX = x;
}

int Spot::getY() {
  return mY;
}

void Spot::setY(int y) {
  mY = y;
}

void Spot::setY(int y) {
  mY = y;
}

Piece *Spot::getPiece() {
  return mPiece;
}