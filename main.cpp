#include <iostream>
#include <vector>

using namespace std;

// enum Status {

// }

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

    virtual bool canMove(Board &b, Spot &start, Spot &end) = 0;
    //virtual Spot& canMove(Board &b, Spot &start) = 0;
    virtual Spot* canJump(Board &b, Spot &start, Spot &end) = 0;
    //virtual Piece* canJump(Board &b, Spot &start) = 0;

};

class Common : public Piece
{
public:
    Common(bool white, bool killed) : Piece(white, killed) {
    }

    bool canMove(Board &b, Spot &start, Spot &end);
    //Spot& canMove(Board &b, Spot &start);
    Spot* canJump(Board &b, Spot &start, Spot &end);
    //Piece* canJump(Board &b, Spot &start);


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
                if(i <= 2 && i%2 == j%2) 
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

bool Common::canMove(Board &b, Spot &start, Spot &end) {
    // MOVER CORNER CASE PARA A HORA DE PERGUNTAR AO USUARIO
    // int xs = start.getX(), ys = start.getY();
    // int xe = end.getX(), ye = end.getY();
    // if(xs < 0 || ys > 7 || xe < 0 || ye > 7) return false; // Corner cases
    if(b.getPiece(end.getX(), end.getY())) return false;
    Common *c = dynamic_cast<Common*>(b.getPiece(start.getX(), start.getY()));
    if(!c) return false;
    if(c->isWhite()) {
        int dx = end.getX() - start.getX();
        int dy = end.getY() - start.getY();
        if(dy != -1) return false;
        if(dy != -abs(dx)) return false;
    }
    else {
        int dx = end.getX() - start.getX();
        int dy = end.getY() - start.getY();
        if(dy != 1) return false;
        if(dy != abs(dx)) return false;
    }
    return true;
}

// Spot& Common::canMove(Board &b, Spot &start) {
//     Common *c = dynamic_cast<Common*>(b.getPiece(start.getX(), start.getY()));
//     if(!c) return false;

//     if(c->isWhite()) {
        
//         int dx = end.getX() - start.getX();
//         int dy = end.getY() - start.getY();
//         if(dy != -1) return false;
//         if(dy != -abs(dx)) return false;
//     }
//     else {
//         int dx = end.getX() - start.getX();
//         int dy = end.getY() - start.getY();
//         if(dy != 1) return false;
//         if(dy != abs(dx)) return false;
//     }
//     return true;
// }

Spot* Common::canJump(Board &b, Spot &start, Spot &end) {
    if(b.getPiece(end.getX(), end.getY())) return NULL;
    Common *c = dynamic_cast<Common*>(b.getPiece(start.getX(), start.getY()));
    if(!c) return NULL;
    if(c->isWhite()) {
        int dx = end.getX() - start.getX();
        int dy = end.getY() - start.getY();
        if(dy != -2) return NULL;
        int pieceX = dx > 0 ? start.getX() + 1 : start.getX() - 1;
        if(b.getPiece(pieceX, start.getY() - 1) == NULL) return NULL;
        return b.getSpot(pieceX, start.getY() - 1);
    } else {
        int dx = end.getX() - start.getX();
        int dy = end.getY() - start.getY();
        if(dy != 2) return NULL;
        int pieceX = dx > 0 ? start.getX() + 1 : start.getX() - 1;
        if(b.getPiece(pieceX, start.getY() + 1) == NULL) return NULL;
        return b.getSpot(pieceX, start.getY() + 1);
    }
}


class Game 
{
private:
    //Status statusGame;
    bool isWhiteTurn;
    int deadWhiteCount, deadRedCount;
public:
    Board *board;
    Game(): isWhiteTurn(true), deadRedCount(0), deadWhiteCount(0) {
        board = new Board();
    }

    bool movePiece(Spot &start, Spot &end);
    bool isGameOver();
};

bool Game::isGameOver() {
    if(deadRedCount == 12) {
        cout << "VITORIA DAS PECAS BRANCAS" << endl;
        return true;
    }
    if(deadWhiteCount == 12) {
        cout << "VITORIA DAS PECAS VERMELHAS" << endl;
        return true;
    }
    return false;
};

bool Game::movePiece(Spot &start, Spot &end) {
    Common *c = dynamic_cast<Common*> (board->getPiece(start.getX(), start.getY()));
    //Queen *c = dynamic_cast<Queen*> board.getPiece(start.getX(), start.getY());
    if((isWhiteTurn && !c->isWhite()) || (!isWhiteTurn && c->isWhite())) {
        cout << "Voce nao pode mover a peca de outro jogador" << endl;
        return false;
    }

    if(c->canMove(*board, start, end)) {
        board->getSpot(end.getX(), end.getY())->setPiece(start.getPiece());
        board->getSpot(start.getX(), start.getY())->setPiece(NULL);
        isWhiteTurn = !isWhiteTurn;
        return true;
    }

    Spot* p = c->canJump(*board, start, end);
    if(p != NULL) {
        board->getSpot(end.getX(), end.getY())->setPiece(start.getPiece());
        board->getSpot(start.getX(), start.getY())->setPiece(NULL);
        p->getPiece()->setKilled(true);
        if(p->getPiece()->isWhite()) deadWhiteCount++;
        else deadRedCount++;
        p->setPiece(NULL);
        isWhiteTurn = !isWhiteTurn;
        return true;
    }
    cout << "Movimento invalido" << endl;
    return false;
}




int main() {
    Game g;

    g.board->print();
    cout << g.board->getPiece(1,5)->canMove(*g.board, *g.board->getSpot(1,5),*g.board->getSpot(2,4)) << endl << endl;

    g.movePiece(*g.board->getSpot(1,5), *g.board->getSpot(2,4));
    g.board->print();
    g.movePiece(*g.board->getSpot(0,2), *g.board->getSpot(1,3));
    g.board->print();
    g.movePiece(*g.board->getSpot(2,4), *g.board->getSpot(0,2));
    g.board->print();
    g.movePiece(*g.board->getSpot(4,2), *g.board->getSpot(5,3));
    g.board->print();
    g.movePiece(*g.board->getSpot(0,2), *g.board->getSpot(1,1));

    return 0;
}