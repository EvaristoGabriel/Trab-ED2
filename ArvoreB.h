#ifndef ARVOREB_H_INCLUDED
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <iostream>
#include "NoB.h"
using namespace std;

class ArvoreB{
    private:
        NoB* raiz;
        int ordem;
        int totalChaves;
        
    public:
        ArvoreB();
        void inserir(int chave, NoB* no, int nivelDoNo, NoB* filhoEsquerda, NoB* filhoDireita);
        void cria(int m);
        NoB* buscar(int chave);
        NoB* auxbuscar(int chave, int *nivelNo);
};

#endif