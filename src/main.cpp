#include <iostream>

using namespace std;

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

        void print() {
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    //if(casas[i][j]->getPeca()->isJogador()) cout << "B ";
                    cout << "X";
                }
                cout << endl;
            }
        }
};








int main() {
    Tabuleiro a;
    a.print();

    return 0;
}