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
        int grau; //grau minimo
        
    public:
        ArvoreB(int k);
        void atravessarNos();
        NoB* busca(int k);
        void inserir(int val);
};

#endif