#include "Piece.h"

Piece::Piece(bool mWhite) : mWhite(mWhite) {
}

bool Piece::isWhite() {
  return mWhite;
}

bool Piece::isKilled() {
  return mKilled;
}

void Piece::setKilled(bool killed) {
  mKilled = killed;
}