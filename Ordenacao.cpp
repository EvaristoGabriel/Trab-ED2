#include "ArvoreVP.h"

template <typename T>
void ImprimirVetor(T *vet, int n, ofstream &saida){
    saida << "Vetor ordenado: ";
    for(int i = 0; i<n; i++)
        saida << vet[i] << " ";
}

template <typename T>
void troca(T &a, T &b)
{
    T aux = a;
    a = b;
    b = aux;
}

int pivoAleatorio(int *v, int ini, int fim)
{
    int pos = ini + rand() % (fim - ini + 1);
    troca(v[pos], v[fim]);
    return v[fim];
}

template <typename T>
T medianaDeTres(T *v, int ini, int fim)
{
    int meio = (ini + fim) / 2;
    if (v[ini] > v[fim])
        troca(v[ini], v[fim]);
    if (v[meio] > v[fim])
        troca(v[meio], v[fim]);
    if (v[ini] > v[meio])
        troca(v[ini], v[meio]);
    troca(v[meio], v[fim]);
    return v[fim];
}

template <typename T>
int particiona(T *v, int ini, int fim)
{
    // T pivo = v[fim];
    // int pivo = pivoAleatorio(v, ini, fim);
    T pivo = medianaDeTres(v, ini, fim);

    int i = ini, j = fim - 1;
    while (true)
    {
        while (i < fim && v[i] < pivo)
            i++;
        while (j >= ini && v[j] > pivo)
            j--;
        if (i < j)
        {
            troca(v[i], v[j]);
            i++;
            j--;
        }
        else
            break;
    }
    troca(v[i], v[fim]);
    return i;
}

template <typename T>
void QuickSortRec(T *v, int ini, int fim)
{
    if (ini < fim)
    {   
        int p = particiona(v, ini, fim);
        QuickSortRec(v, ini, p - 1);
        QuickSortRec(v, p + 1, fim);
        return;
    }
}

template <typename T>
double QuickSort(T *v, int n, ofstream &saida)
{
    saida << "Quick Sort: "<<endl;
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    

    QuickSortRec(v, 0, n - 1);
    
    saida << "Tempo: ";
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    double tempo = duration_cast<duration<double>>(fim - inicio).count();
    saida << tempo << " segundos" << endl;

    //ImprimirVetor(v,n,saida);
    saida << endl << endl;
    return tempo;
}

template <typename T>
void Heapify(T *v, int i, int n)
{
    while (i < n)
    {
        int filho = 2 * i + 1;
        if (filho < n)
        {
            if (filho + 1 < n && v[filho + 1] > v[filho])
                filho++;
            if (v[filho] > v[i])
                troca(v[i], v[filho]);
        }
        i = filho;
    }
}

template <typename T>
void constroiHeap(T *v, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(v, i, n);
}

template <typename T>
void HeapSortRec(T *v, int n)
{
    constroiHeap(v, n);
    while (n > 0)
    {
        troca(v[0], v[n - 1]);
        Heapify(v, 0, n - 1);
        n--;
    }
}

template <typename T>
double HeapSort(T *v, int n, ofstream &saida)
{   
    saida << "Heap Sort: "<<endl;
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    HeapSortRec(v, n);
    saida << "Tempo: ";
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    double tempo = duration_cast<duration<double>>(fim - inicio).count();
    saida << tempo << " segundos" << endl;
    //ImprimirVetor(v,n,saida);
    saida << endl << endl;
    return tempo;
}

int getProxGap(int gap)
{
    gap = (gap * 10) / 13;
    if (gap < 1)
        return 1;
    return gap;
}

template <typename T>
double CombSort(T *vet, int n, ofstream &saida)
{
    saida << "Comb Sort: "<<endl;
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    int gap = n;
    bool troca = true;
    while (gap != 1 || troca == true)
    {
        gap = getProxGap(gap);
        troca = false;
        for (int i = 0; i < n - gap; i++)
        {
            if (vet[i] > vet[i + gap])
            {
                swap(vet[i], vet[i + gap]);
                troca = true;
            }
        }
    }
    saida << "Tempo: ";
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    double tempo = duration_cast<duration<double>>(fim - inicio).count();
    saida << tempo << " segundos" << endl;
    //ImprimirVetor(vet,n,saida);
    saida << endl << endl;
    return tempo;
}







