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

void ArvoreB::cria(int m){
    ordem = m;
    raiz = NULL;
    totalChaves = 0;
}

/* void ArvoreB::inserir(int chave, NoB* no, int nivelDoNo, NoB* filhoAEsquerda, NoB* filhoADireita)
     {    
          
          if(raiz == NULL){  

              raiz = (NoB*) malloc(sizeof(NoB)); 
              
              if(!raiz->cria(ordem, nivelDoNo == -1)){
                  cout << "\nMemoria insuficiente!" << endl;
                  cin.get();
                  return;
              }
              
              raiz->adicionaChave(chave);
              
              if(filhoAEsquerda != NULL && filhoADireita != NULL){                  
                  raiz->adicionaFilho(filhoAEsquerda, 0);
                  raiz->adicionaFilho(filhoADireita, 1);
                  
                  filhoAEsquerda->setAscendente(raiz);
                  filhoADireita->setAscendente(raiz);
              }
              
          }else{
                
                // Pega a posição que a chave foi inserida no no
                int posicao = no->adicionaChave(chave);
                
                if(filhoADireita != NULL){  
                   // A partir da posição que a chave foi inserida, insere o ponteiro a sua direita  
                   filhoADireita->setAscendente(no);
                   no->adicionaFilho(filhoADireita, posicao + 1);
                }
                
               
               
               // Condição para deslocamento e divisão do no
               if(no->getNumeroDeChaves() == ordem){
                   
                   // Divide o no                                      
                   NoB **novosFilhos = no->divideFilhos(); // guarda os filhos do novo no(se existirem)
                   int *novasChaves = no->divideChaves(); // guarda as chaves do novo no
                   int newNumberOfKeys = ordem - no->getNumeroDeChaves();
                   
                   // Cria um novo no
                   NoB* novoNo;
                   
                   novoNo = (NoB*) malloc(sizeof(NoB)); 
                   
				   if(!novoNo->cria(ordem, no->ehfolha())){
					  cout << "\nMemoria insuficiente!" << endl;
					  cin.get();
					  return;
				   }
				   
				   // ajusta os ponteiros			   
				   novoNo->setIrmaoADireita(no->getIrmaoADireita());
				   novoNo->setIrmaoAEsquerda(no);
				   
				   if(no->getIrmaoADireita() != NULL)
					  no->getIrmaoADireita()->setIrmaoAEsquerda(novoNo);
					  
				   no->setIrmaoADireita(novoNo);	
				   
				   
				   
                   // Adiciona as chaves no novo no
                   for(int i = 0; i < newNumberOfKeys; i++)
                       novoNo->adicionaChave(novasChaves[i]);
                   
				   free(novasChaves);
				   
                   // Se não for uma folha, adiciona os ponteiros que foram separados do no velho
                   if(novosFilhos != NULL){
                                  
                       NoB* f = NULL;
                                 
                       // Adiciona os ponteiros  
                       for(int i=0; i < newNumberOfKeys + 1; i++){  
                           f = novosFilhos[i];        
                           f->setAscendente(novoNo);
                           novoNo->adicionaFilho(f, i);
						   novosFilhos[i] = NULL;
                       }
                         
                       f = NULL;
                       
                       // limpa da memória
                       free(novosFilhos);
                   }
                      
                   
                   
               
               
                   // Pega a chave que vai subir e a retira do no
                   int chavePromovida = no->retiraUltimaChave();                       
                   
                   // Define os ponteiros para o novo elemento que vai subir
                   filhoAEsquerda = no == raiz ? no : NULL; 
                   filhoADireita = novoNo;              
                   
                   if(no == raiz){
                       raiz = NULL; // o elemento a ser reinserido será a nova raiz 
                       no = NULL;
                   }else
                       no = no->getAscendente();
                       
                   // Reinsere o elemento no nivel acima do que ele estava 
                   inserir(chavePromovida, no, nivelDoNo - 1, filhoAEsquerda, filhoADireita);         
               } 
               
          }           
        
     }  */