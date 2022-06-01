#include <iostream>
#include <cmath>

using namespace std;

enum Status {
    vitoriaBranca,
    vitoriaVermelha,
    emCurso
}

class Tabuleiro;
class Casa;

class Peca {
    private:
        bool isBranca;
        bool isMort;
    public:
        Peca(bool isBranca, bool isMorta) : isBranca(isBranca), isMort(isMorta) {}
        bool isJogador() {
            return isBranca;
        }

        bool isMorta() {
            return isMort;
        }

        void mataPeca() {
            this->isMort = true;
        }
        //RESOLVER A NECESSIDADE DE USAR AS CLASSES POSTERIORES AQUI
        //colocar no .h talvez resolva

        bool podeMover(Tabuleiro t, Casa inicio, Casa fim) {
            if(t.getPeca(inicio.getX(),inicio.getY())->getPeca()->isJogador()) { //se a peça a ser movida for do jogador (só se pode mover pra cima)
                if(fim.getY() < inicio.getY() || fim.getY() - inicio.getY() > 1) return false;
                if(abs(fim.getX() - inicio.getX()) != 1) return false;

                if(t.getPeca(fim.getX(), fim.getY())->getPeca() != NULL) return false; //se tiver algo na casa não move
                return true;
            }
            else {
                if(fim.getY() > inicio.getY() || fim.getY() - inicio.getY() < -1) return false;
                if(abs(fim.getX() - inicio.getX()) != 1) return false;

                if(t.getPeca(fim.getX(), fim.getY())->getPeca() != NULL) return false; //se tiver algo na casa não move
                return true;
            }
        }
};

class Comum : public Peca {
    public:
        Comum(bool isBranca, bool isMorta) : Peca(isBranca, isMorta) {}
};

class Rainha : public Peca {
    public:
        Rainha(bool isBranca, bool isMorta) : Peca(isBranca, isMorta) {}
};


class Casa {
    private:
        Peca *peca;
        int x,y;
    public: 
        Casa(int x, int y, Peca *p) : x(x), y(y), peca(p) {}
        Peca* getPeca() {
            return peca;
        }

        int getX() {
            return x;
        }

        int getY() {
            return y;
        }

        void setPeca(Peca *peca) {
            this->peca = peca;
        }
};

class Tabuleiro {
    private:
        Casa ***casas;
    public:
        Tabuleiro() {
            casas = new Casa**[8];
            for(int i = 0; i < 8; i++) {
                casas[i] = new Casa*[8];
            }

            for (int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    if(i <= 2 && i%2 != j%2) {
                        casas[i][j] = new Casa(i,j, new Comum(true,false));
                    }

                    else if(i >= 5 && i%2 == j%2) {
                        casas[i][j] = new Casa(i,j, new Comum(false,false));
                    }

                    else{
                        casas[i][j] = new Casa(i,j, NULL);
                    }
                }
            }
        }

        Peca* getPeca(int i, int j) {
            return casas[i][j]->getPeca();
        }

        void print() {
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    if(casas[i][j]->getPeca() == NULL) cout << " ";
                    else if(casas[i][j]->getPeca()->isJogador()) cout << "B ";
                    else cout << "V ";
                }
                cout << endl;
            }
        }
};

// class Movimento {

// };

class Jogo {
    private:
        Tabuleiro tabuleiro;
        Status statusJogo;
        bool turno;

    public:
        Jogo() : {}

        void makeMove(Casa inicio, Casa fim) {
            if(tabuleiro.getPeca(inicio.getX(), inicio.getY())->getPeca()->isJogador() && turno != true) { //se a peça a mover é do jogador
                cout << "Nao se pode mover a peca do adversario" << endl;
                return;
            }
            if(!tabuleiro.getPeca(inicio.getX(), inicio.getY())->getPeca()->isJogador() && turno != false) { //se a peça a mover é do jogador
                cout << "Nao se pode mover a peca do adversario" << endl;
                return;
            }

            if(!tabuleiro.getPeca(inicio.getX(), inicio.getY())->getPeca()->podeMover()) {
                cout << "A peca nao pode se mover" << endl;
                return;
            }

            //mover a peça e dar um jeito de checar se tinha alguma no caminho
        }
};








int main() {
    Tabuleiro a;
    a.print();
    cout << a.getPeca(0,1)->podeMover();

    return 0;
}