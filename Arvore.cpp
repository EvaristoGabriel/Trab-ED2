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

void NoB::remove(int k){
    int index = buscaChave(k);

    if(index < totalChaves && chaves[index] == k){
        if(ehfolha)
            removeFolha(index);
        else
            removedeNonFolha(index);
    }
    else
    {
        if(ehfolha)
            return;
        bool flag = ((index == totalChaves) ? true : false);

        if(filhos[index]->totalChaves < grau)
            preencher(index);
        
        if(flag && index > totalChaves)
            filhos[index-1]->remove(k);
        else
            filhos[index]->remove(k);
    }
}

void NoB::removeFolha(int index){
    for(int i = index+1;i<totalChaves; ++i)
        chaves[i-1] = chaves[i];
    
    totalChaves--;
}

void NoB::removedeNonFolha(int index){
    int k = chaves[index];

    if(filhos[index]->totalChaves >= grau){
        int pred = getpredecessor(index);
        chaves[index] = pred;
        filhos[index]->remove(pred);
    }

    else if(filhos[index+1]->totalChaves >= grau){
        int suc = getsucessor(index);
        chaves[index] = suc;
        filhos[index+1]->remove(suc);
    }
    else{
        juntar(index);
        filhos[index]->remove(k);
    }
}

int NoB::getpredecessor(int index){
    NoB* p = filhos[index];
    while (!p->ehfolha)
        p = p->filhos[p->totalChaves];
    return p->chaves[p->totalChaves-1];
}

int NoB::getsucessor(int index){
    NoB* p = filhos[index+1];
    while (!p->ehfolha)
        p = p->filhos[0];
    return p->chaves[0];
}

void NoB::preencher(int index){
    if(index != 0 && filhos[index - 1]->totalChaves >= grau)
        pegarEsquerda(index);
    else if(index != totalChaves && filhos[index + 1]->totalChaves >= grau)
        pegarDireita(index);

    else{
        if(index != totalChaves)
            juntar(index);
        else
            juntar(index - 1);
    }
}

void NoB::pegarEsquerda(int index){
    NoB* filho = filhos[index];
    NoB* sibling = filhos[index - 1];


    for (int i = filho->totalChaves - 1; i >= 0; --i)
        filho->chaves[i + 1] = filho->chaves[i];


    if (!filho->ehfolha)
    {
        for (int i = filho->totalChaves; i >= 0; --i)
            filho->filhos[i + 1] = filho->filhos[i];
    }

    filho->chaves[0] = chaves[index - 1];


    if (!filho->ehfolha)
        filho->filhos[0] = sibling->filhos[sibling->totalChaves];

    chaves[index - 1] = sibling->chaves[sibling->totalChaves - 1];

    filho->totalChaves += 1;
    sibling->totalChaves -= 1;

}

void NoB::pegarDireita(int index)
{

    NoB* filho = filhos[index];
    NoB* irmao = filhos[index + 1];


    filho->chaves[(filho->totalChaves)] = chaves[index];


    if (!(filho->ehfolha))
        filho->filhos[(filho->totalChaves) + 1] = irmao->filhos[0];


    chaves[index] = irmao->chaves[0];


    for (int i = 1; i < irmao->totalChaves; ++i)
        irmao->chaves[i - 1] = irmao->chaves[i];


    if (!irmao->ehfolha)
    {
        for (int i = 1; i <= irmao->totalChaves; ++i)
            irmao->filhos[i - 1] = irmao->filhos[i];
    }


    filho->totalChaves += 1;
    irmao->totalChaves -= 1;

}

void NoB::juntar(int index)
{
    NoB* filho = filhos[index];
    NoB* irmao = filhos[index + 1];

    filho->chaves[grau - 1] = chaves[index];

    for (int i = 0; i < irmao->totalChaves; ++i)
        filho->chaves[i + grau] = irmao->chaves[i];

    if (!filho->ehfolha)
    {
        for (int i = 0; i <= irmao->totalChaves; ++i)
            filho->filhos[i + grau] = irmao->filhos[i];
    }

    for (int i = index + 1; i < totalChaves; ++i)
        chaves[i - 1] = chaves[i];

    for (int i = index + 2; i <= totalChaves; ++i)
        filhos[i - 1] = filhos[i];

    filho->totalChaves += irmao->totalChaves + 1;
    totalChaves--;

    delete(irmao);
    return;
}

void NoB::inserirNonFull(int k)
{

    int i = totalChaves - 1;

    if (ehfolha == true)
    {
        while (i >= 0 && chaves[i] > k)
        {
            chaves[i + 1] = chaves[i];
            i--;
        }
        chaves[i + 1] = k;
        totalChaves = totalChaves + 1;
    }
    else 
    {
        while (i >= 0 && chaves[i] > k)
            i--;

        if (filhos[i + 1]->totalChaves == 2 * grau - 1)
        {
            splitChild(i + 1, filhos[i + 1]);

            if (chaves[i + 1] < k)
                i++;
        }
        filhos[i + 1]->inserirNonFull(k);
    }
}

void NoB::splitChild(int i, NoB* y)
{
    NoB* z = new NoB(y->grau, y->ehfolha);
    z->totalChaves = grau - 1;

    for (int j = 0; j < grau - 1; j++)
        z->chaves[j] = y->chaves[j + grau];

    if (y->ehfolha == false)
    {
        for (int j = 0; j < grau; j++)
            z->filhos[j] = y->filhos[j + grau];
    }

    y->totalChaves = grau - 1;

    for (int j = totalChaves; j >= i + 1; j--)
        filhos[j + 1] = filhos[j];

    filhos[i + 1] = z;

    for (int j = totalChaves - 1; j >= i; j--)
        chaves[j + 1] = chaves[j];

    chaves[i] = y->chaves[grau - 1];

    totalChaves = totalChaves + 1;
}

void NoB::atravessarNo()
{
    int i;
    for (i = 0; i < totalChaves; i++)
    {
        if (ehfolha == false)
            filhos[i]->atravessarNo();
        cout << " " << chaves[i];
    }

    if (ehfolha == false)
        filhos[i]->atravessarNo();
}

NoB* NoB::busca(int k)
{
    int i = 0;
    while (i < totalChaves && k > chaves[i])
        i++;

    if (chaves[i] == k)
        return this;

    if (ehfolha == true)
        return NULL;

    return filhos[i]->busca(k);
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
    if(raiz == nullptr){
        raiz = new NoB(grau,true);
        raiz->chaves[0] = val;
        raiz->totalChaves = 1;
    }
    else{
        if(raiz->totalChaves == 2*grau -1){
            NoB* s = new NoB(grau,false);

            s->filhos[0] = raiz;
            s->splitChild(0, raiz);

            int i = 0;
            if (s->chaves[0] < val)
                i++;
            s->filhos[i]->inserirNonFull(val);

            raiz = s;
        }
        else  
            raiz->inserirNonFull(val);
    }
}
