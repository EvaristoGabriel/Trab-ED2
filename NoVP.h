#ifndef NOVP_H_INCLUDED
#define NOVP_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 1
#define BLACK 0

using namespace std;
using namespace std::chrono;

class NoVP
{
  public:
    NoVP()               { };
    ~NoVP()              { };
    void setEsq(NoVP *p) { esq = p; };
    void setInfo(int val) { info = val; };
    void setDir(NoVP *p) { dir = p; };
    void setCor(int cor) { cor = RED; };
    NoVP* getEsq()       { return esq; };
    int getInfo()         { return info; };
    NoVP* getDir()       { return dir; };
    int getCor()        {return cor; };

  private:
    NoVP *esq;  // ponteiro para o filho a esquerda
    int info,cor; // informa��o do No (int)
    NoVP *dir;  // ponteiro para o filho a direita
};

#endif