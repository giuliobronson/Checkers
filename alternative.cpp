#include <iostream>

using namespace std;

enum Status {

}

class Spot;
class Board;

class Piece
{
private:
    bool white;
    bool killed;

public:
    Piece(bool white, bool killed) : white(white), killed(killed) {
    }

    bool isWhite() {
        return white;
    }

    bool isKilled() {
        return killed;
    }

    void setKilled(bool killed) {
        this->killed = killed;
    }

};

class Common : public Piece
{
public:
    Common(bool white, bool killed) : Piece(white, killed) {
    }

};

class Queen : public Piece
{
public:
    Queen(bool white, bool killed) : Piece(white, killed) {
    }
};

class Spot
{
private:
    Piece *piece;
    int x, y;

public:
    Spot(int i, int j, Piece *piece) : x(j), y(i), piece(piece) {
    }

    Piece *getPiece() {
        return piece;
    }

    void setPiece(Piece *piece) {
        this->piece = piece;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};

class Board 
{
private:
    Spot ***spots;

public:
    Board() {
        spots = new Spot**[8];
        for(int i = 0; i < 8; i++) {
            spots[i] = new Spot*[8];
        }
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(i <= 2 && i%2 != j%2) 
                    spots[i][j] = new Spot(i, j, new Common(false, false));
                else if(i >= 5 && i%2 == j%2) 
                    spots[i][j] = new Spot(i, j, new Common(true, false));
                else
                    spots[i][j] = new Spot(i, j, NULL);
            }
        }
    }

    Spot *getSpot(int x, int y) {
        return spots[y][x];
    }

    Piece *getPiece(int x, int y) {
        return spots[y][x]->getPiece();
    }

    void print() {
        for(int i = 0; i < 8; i++) {
        cout << i + 1 << "| ";
            for(int j = 0; j < 8; j++) {
                if(spots[i][j]->getPiece() == NULL) cout << "   ";
                else if(spots[i][j]->getPiece()->isWhite()) cout << " B ";
                else cout << " V ";
            }
            cout << endl;
        }
        cout << "  ";
        for(int i = 0; i < 8; i++) cout << "---";
        cout << endl;
        cout << "   ";
        for(int i = 0; i < 8; i++) cout << " " << (char)('A' + i) << " ";
        cout << endl;
    }
};