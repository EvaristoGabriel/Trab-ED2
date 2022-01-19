/* O tipo abstrato de dados deve implementar as operações de inserção e busca 
(não há necessidade de implementar a remoção). 
Cada nó deve armazenar o id da avaliação e a sua localização no arquivo binário. 
A ordenação da árvore será determinada pelo id. 
As outras informações do registro, quando necessárias, 
serão recuperadas através do acesso ao disco.  */
#include "ArvoreVP.h"
#include "ArvoreB.h"


ArvoreVP::ArvoreVP(){
    raiz = NULL;
}

int ArvoreVP::Cor(NoVP* no){
    if(no == NULL)
        return BLACK;
    else
        return no->getCor();
}

void ArvoreVP:: TrocaCor(NoVP* no){
    no->setCor(!no->getCor());
    if(no->getEsq() != NULL)
        no->getEsq()->setCor(!no->getEsq()->getCor());
    if(no->getDir() != NULL)
        no->getDir()->setCor(!no->getDir()->getCor());
}

NoVP* ArvoreVP::rotacionaEsquerda(NoVP* no){
    NoVP* a = no->getDir();
    no->setDir(a->getEsq());
    a->setEsq(no);
    a->setCor(no->getCor());
    no->setCor(RED);
    return a;
}

NoVP* ArvoreVP::rotacionaEsquerda(NoVP* no){
    NoVP* a = no->getEsq();
    no->setEsq(a->getDir());
    a->setDir(no);
    a->setCor(no->getCor());
    no->setCor(RED);
    return a;
}

/* int ArvoreVP::Insere(ArvoreVP* raiz, int valor){
    int resp;
    *raiz = InsereNo(*raiz, valor, &resp);
    if((*raiz) != NULL)
        (*raiz)->setcor(BLACK);

    return resp;
}

NoVP* ArvoreVP::InsereNo(NoVP* no, int valor, int *resp){
    if(no == NULL)
    {
        NoVP *novo;
        novo = (NoVP*)malloc(sizeof(NoVP));
        if(novo == NULL){
            *resp = 0;
            return NULL;
        }
        novo->setInfo(valor);
        novo->setCor(RED);
        novo->setDir(NULL);
        novo->setDir(NULL);
        *resp = 1;
        return novo;
    }
    if(valor == no->getInfo())
        *resp=0;
    else{
        if(valor < no->getInfo())
            no->setEsq(InsereNo(no->getEsq(),valor,resp));
        else
            no->setDir(InsereNo(no->getDir(),valor,resp));
    }
    
    if(Cor(no->getDir()) == RED && Cor(no->getEsq()) == BLACK)
        rotacionaEsquerda(no);
    
    if(Cor(no->getEsq()) == RED && Cor(no->getEsq()->getEsq()) == RED)
        rotacionaDireita(no);
    
    if(Cor(no->getEsq()) == RED && Cor(no->getDir()) == RED)
        TrocaCor(no);
    
    return no;
} */

bool ArvoreVP::Busca(int valor){
    return auxBusca(raiz, valor);
}

bool ArvoreVP::auxBusca(NoVP *p, int valor){
    if(p == NULL)
        return false;
    else if(p->getInfo() == valor)
        return true;
    else if(valor < p->getInfo())
        return auxBusca(p->getEsq(),valor);
    else
        return auxBusca(p->getDir(),valor);
}

NoB::NoB(int t, bool folha){
    grau = t;
    ehfolha = folha;

    chaves = new int [2*grau - 1];
    filhos = new NoB* [2*t];

    totalChaves = 0;
}

int NoB::buscaChave(int k){
    int index = 0;
    while(index < totalChaves && chaves[index] < k)
        ++index;
    return index;
}

ArvoreB::ArvoreB(int k){
    raiz = NULL;
    grau = k;
}

void ArvoreB::atravessarNos(){
    if(raiz != NULL)
        raiz->atravessarNo();
}

NoB* ArvoreB::busca(int k){
    return (raiz == NULL) ? NULL : raiz->busca(k);
}

void ArvoreB::inserir(int val)
{    
       
} 