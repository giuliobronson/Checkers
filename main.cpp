#include <iostream>

using namespace std;

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
};

class Common : public Piece
{
public:
    Common(bool white, bool killed) : Piece(white, killed) {
    }

    bool canMove(Board &b, Spot &start, Spot &end);
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
        if(dy > 0 || dy < -2) return false;
        if(dy != -abs(dx)) return false;
        if(dy == -2) {
            int pieceX = dx > 0 ? start.getX() + 1 : start.getX() - 1;
            Common *p = dynamic_cast<Common*>(b.getPiece(pieceX, start.getY() - 1));
            if(!p || p->isWhite()) return false;
        }
    }
    else {
        int dx = end.getX() - start.getX();
        int dy = end.getY() - start.getY();
        if(dy < 0 || dy > 2) return false;
        if(dy != abs(dx)) return false;
        if(dy == 2) {
            int pieceX = dx > 0 ? start.getX() + 1 : start.getX() - 1;
            Common *p = dynamic_cast<Common*>(b.getPiece(pieceX, start.getY() + 1));
            if(!p || !p->isWhite()) return false;
        }
    }
    return true;
}

class Move
{

};

// class Game 
// {
// private:
//     Board board;
//     Status statusGame;
//     bool turn;
// public:
//     Game() {
//     }

//     void makeMove(Casa inicio, Casa fim) {
//         if(tabuleiro.getPeca(inicio.getX(), inicio.getY())->getPeca()->isJogador() && turno != true) { //se a peça a mover é do jogador
//             cout << "Nao se pode mover a peca do adversario" << endl;
//             return;
//         }
//         if(!tabuleiro.getPeca(inicio.getX(), inicio.getY())->getPeca()->isJogador() && turno != false) { //se a peça a mover é do jogador
//             cout << "Nao se pode mover a peca do adversario" << endl;
//             return;
//         }

//         if(!tabuleiro.getPeca(inicio.getX(), inicio.getY())->getPeca()->podeMover()) {
//             cout << "A peca nao pode se mover" << endl;
//             return;
//         }

//         //mover a peça e dar um jeito de checar se tinha alguma no caminho
//     }
// };

// bool podeMover(Tabuleiro t, Casa inicio, Casa fim) {
//     if(t.getPeca(inicio.getX(),inicio.getY())->getPeca()->isJogador()) { //se a peça a ser movida for do jogador (só se pode mover pra cima)
//         if(fim.getY() < inicio.getY() || fim.getY() - inicio.getY() > 1) return false;
//         if(abs(fim.getX() - inicio.getX()) != 1) return false;

//         if(t.getPeca(fim.getX(), fim.getY())->getPeca() != NULL) return false; //se tiver algo na casa não move
//         return true;
//     }
//     else {
//         if(fim.getY() > inicio.getY() || fim.getY() - inicio.getY() < -1) return false;
//         if(abs(fim.getX() - inicio.getX()) != 1) return false;

//         if(t.getPeca(fim.getX(), fim.getY())->getPeca() != NULL) return false; //se tiver algo na casa não move
//         return true;
//     }
// }

int main() {
    Board b;
    b.print();
    cout << b.getPiece(1,5)->canMove(b, *b.getSpot(1,5),*b.getSpot(2,4)) << endl;
    return 0;
}