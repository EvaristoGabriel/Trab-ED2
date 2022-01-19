#ifndef NOB_H_INCLUDED
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <iostream>
using namespace std;

class NoB{  
    public:
        bool ehfolha;       //indica se o no é uma folha
        int totalChaves;    //numero atual de chaves
        int grau;           //grau maximo
        int *chaves;        //lista de chaves         
        NoB **filhos;       //matrix de ponteiro para os filhos 
        NoB(int t, bool leaf);
        void atravessarNo();
        NoB* busca(int k);
        int buscaChave(int k);
        void inserirNonFull(int k);
        void splitChild(int i, NoB* y);
        void remove(int k);
        void removeFolha(int index);
        void removedeNonFolha(int index);
        int getpredecessor(int index);
        int getsucessor(int index);
        void preencher(int index);
        void pegarEsquerda(int index);
        void pegarDireita(int index);
        void juntar(int index);

};

#endif