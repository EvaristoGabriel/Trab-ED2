#ifndef ARVOREVP_H_INCLUDED
#include "NoVP.h"

#define RED 1
#define BLACK 0

class ArvoreVP{
    private:
        NoVP *esq, *dir, *pai,*raiz;
        bool auxBusca(NoVP* no, int valor);

    public:
        ArvoreVP();
        int Cor(NoVP* no);
        void TrocaCor(NoVP* no);
        NoVP* rotacionaEsquerda(NoVP* no);
        NoVP* rotacionaDireita(NoVP* no);
        NoVP* InsereNo(NoVP* no, int valor, int *resp);
        int Insere(ArvoreVP* raiz, int valor);
        bool Busca(int valor);
};

#endif