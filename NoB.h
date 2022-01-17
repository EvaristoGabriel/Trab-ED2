#ifndef NOB_H_INCLUDED
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <iostream>
using namespace std;

class NoB{
    private:
        bool ehfolha;        // indica se o no é uma folha
        int totalChaves;   // total de chaves presentes no no
        int ordem;           // ordem do no
        int *chaves;         // lista com as chaves do no
        NoB **filhos;        // lista com os filhos do no
        NoB *ascendente;     // no ascendente
        NoB *irmaoEsquerda; // no irmão à esquerda
        NoB *irmaoDireita;  // no irmão à direita
    public:
        bool ehFolha() {return ehfolha;};
        int getNumChaves() {return totalChaves;};
        NoB* getAscendente() {return ascendente;};
        NoB* getIrmaoEsquerda() {return irmaoEsquerda;};
        NoB* getIrmaoDireita() {return irmaoDireita;};
        void setAscendente(NoB* no) {ascendente = no;};
        void setIrmaoDireita(NoB* no) {irmaoDireita = no;};
        void setIrmaoEsquerda(NoB* no) {irmaoEsquerda = no;};
        NoB* getFilhoPosicao(int posicao) {if(!ehfolha && posicao >= 0 && posicao <totalChaves+1) return filhos[posicao]; return NULL;};
        int getChavePosicao(int posicao) {if(posicao >= 0 && posicao <totalChaves) return chaves[posicao]; return -1;};
        int getPosicaoChave(int chave) {for(int i =0; i<totalChaves;i++)if(chave == chaves[i]) return i; return -1;};
        int getPosicaoFilho(NoB* no) {if(!ehfolha)for(int i =0; i<totalChaves;i++)if(filhos[i] == no) return i; return -1;};

};

#endif