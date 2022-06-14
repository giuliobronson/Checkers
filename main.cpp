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
    Queen(bool white, bool killed) : Piece(white, killed) {}

    bool canMove(Board &b, Spot &start, Spot &end);
    Spot* canJump(Board &b, Spot &start, Spot &end);
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
                else if(spots[i][j]->getPiece()->isWhite()) {
                    Queen *q = dynamic_cast<Queen*>(spots[i][j]->getPiece());
                    if(q != NULL) cout << " BR";
                    else cout << " B ";
                } 
                else {
                    Queen *q = dynamic_cast<Queen*>(spots[i][j]->getPiece());
                    if(q != NULL) cout << " VR";
                    else cout << " V ";
                } 
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

bool Queen::canMove(Board &b, Spot &start, Spot &end) {
    if(b.getPiece(end.getX(), end.getY())) return false;
    Queen *q = dynamic_cast<Queen*>(b.getPiece(start.getX(), start.getY()));
    if(!q) return false;
    int dx = end.getX() - start.getX();
    int dy = end.getY() - start.getY();
    if(abs(dy) != abs(dx)) return false;
    int xDiagonal, yDiagonal;
    if(dx > 0 && dy > 0) {
        xDiagonal = 1;
        yDiagonal = 1;
    } else if(dx > 0 && dy < 0) {
        xDiagonal = 1;
        yDiagonal = -1;
    } else if(dx < 0 && dy < 0) {
        xDiagonal = -1;
        yDiagonal = -1;
    } else {
        xDiagonal = -1;
        yDiagonal = 1;
    }
    int startX = start.getX() + xDiagonal, startY = start.getY() + yDiagonal;
    while(startX != end.getX() && startY != end.getY()) {
        if(b.getPiece(startX, startY) != NULL) return false;
        startX += xDiagonal;
        startY += yDiagonal;
    }
    return true;
}

Spot* Queen::canJump(Board &b, Spot &start, Spot &end) {
    if(b.getPiece(end.getX(), end.getY())) return NULL;
    Queen *q = dynamic_cast<Queen*>(b.getPiece(start.getX(), start.getY()));
    if(!q) return NULL;
    int dx = end.getX() - start.getX();
    int dy = end.getY() - start.getY();
    if(abs(dy) != abs(dx)) return NULL;
    int xDiagonal, yDiagonal;
    if(dx > 0 && dy > 0) {
        xDiagonal = 1;
        yDiagonal = 1;
    } else if(dx > 0 && dy < 0) {
        xDiagonal = 1;
        yDiagonal = -1;
    } else if(dx < 0 && dy < 0) {
        xDiagonal = -1;
        yDiagonal = -1;
    } else {
        xDiagonal = -1;
        yDiagonal = 1;
    }
    int startX = start.getX() + xDiagonal, startY = start.getY() + yDiagonal;
    if(b.getPiece(end.getX()-xDiagonal, end.getY()-yDiagonal) == NULL) return NULL;
    while(startX != end.getX() - xDiagonal && startY != end.getY() - yDiagonal) {
        if(b.getPiece(startX, startY) != NULL) return NULL;
        startX += xDiagonal;
        startY += yDiagonal;
    }
    return b.getSpot(end.getX()-xDiagonal, end.getY()-yDiagonal);
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
    void checkCrowning(Spot &end) {
        if(end.getPiece()->isWhite() && end.getY() == 0) {
            board->getSpot(end.getX(), end.getY())->setPiece(new Queen(true, false));
            return;
        }
        if(!end.getPiece()->isWhite() && end.getY() == 7) {
            board->getSpot(end.getX(), end.getY())->setPiece(new Queen(false, false));
            return;
        }
    }

    bool turn() {
        return isWhiteTurn;
    }
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
    Queen *q = dynamic_cast<Queen*> (board->getPiece(start.getX(), start.getY()));
    if(!c) {
        if((isWhiteTurn && !q->isWhite()) || (!isWhiteTurn && q->isWhite())) {
            cout << "Voce nao pode mover a peca de outro jogador" << endl;
            return false;
        }
        if(q->canMove(*board, start, end)) {
            board->getSpot(end.getX(), end.getY())->setPiece(start.getPiece());
            board->getSpot(start.getX(), start.getY())->setPiece(NULL);
            checkCrowning(*board->getSpot(end.getX(), end.getY()));
            isWhiteTurn = !isWhiteTurn;
            return true;
        }

        Spot* p = q->canJump(*board, start, end);
        if(p != NULL) {
            board->getSpot(end.getX(), end.getY())->setPiece(start.getPiece());
            board->getSpot(start.getX(), start.getY())->setPiece(NULL);
            checkCrowning(*board->getSpot(end.getX(), end.getY()));
            p->getPiece()->setKilled(true);
            if(p->getPiece()->isWhite()) deadWhiteCount++;
            else deadRedCount++;
            p->setPiece(NULL);
            isWhiteTurn = !isWhiteTurn;
            return true;
        }

    } else {
        if((isWhiteTurn && !c->isWhite()) || (!isWhiteTurn && c->isWhite())) {
            cout << "Voce nao pode mover a peca de outro jogador" << endl;
            return false;
        }
        if(c->canMove(*board, start, end)) {
            board->getSpot(end.getX(), end.getY())->setPiece(start.getPiece());
            board->getSpot(start.getX(), start.getY())->setPiece(NULL);
            checkCrowning(*board->getSpot(end.getX(), end.getY()));
            isWhiteTurn = !isWhiteTurn;
            return true;
        }

        Spot* p = c->canJump(*board, start, end);
        if(p != NULL) {
            board->getSpot(end.getX(), end.getY())->setPiece(start.getPiece());
            board->getSpot(start.getX(), start.getY())->setPiece(NULL);
            checkCrowning(*board->getSpot(end.getX(), end.getY()));
            p->getPiece()->setKilled(true);
            if(p->getPiece()->isWhite()) deadWhiteCount++;
            else deadRedCount++;
            p->setPiece(NULL);
            isWhiteTurn = !isWhiteTurn;
            return true;
        }
    }

    cout << "Movimento invalido" << endl;
    return false;
}




int main() {
    Game g;

    // g.board->print();
    // cout << g.board->getPiece(1,5)->canMove(*g.board, *g.board->getSpot(1,5),*g.board->getSpot(2,4)) << endl << endl;

    do {
        g.board->print();
        cout << endl;
        int line;
        char col;
        cout << "Insira as coordenadas da peca que quer mover: ";
        cin >> col >> line;
        int column = col - 'A';
        line--;
        if(line > 7 || column < 0) {
            cout << "Coordenada invalida" << endl;
            continue;
        }

        if(g.board->getPiece(column,line) == NULL) {
            cout << "Casa vazia" << endl;
            continue;
        }

        int eLine;
        char eCol;
        cout << "Insira as coordenadas destino da peca: ";
        cin >> eCol >> eLine;
        int eColumn = eCol - 'A';
        eLine--;
        if(eLine > 7 || eColumn < 0) {
            cout << "Coordenada invalida" << endl;
            continue;
        }

        g.movePiece(*g.board->getSpot(column, line), *g.board->getSpot(eColumn, eLine));
    }
    while(!g.isGameOver());

    // g.movePiece(*g.board->getSpot(1,5), *g.board->getSpot(2,4));
    // g.board->print();
    // g.movePiece(*g.board->getSpot(0,2), *g.board->getSpot(1,3));
    // g.board->print();
    // g.movePiece(*g.board->getSpot(2,4), *g.board->getSpot(0,2));
    // g.board->print();
    // g.movePiece(*g.board->getSpot(4,2), *g.board->getSpot(5,3));
    // g.board->print();
    // g.movePiece(*g.board->getSpot(0,2), *g.board->getSpot(1,1));

    return 0;
}