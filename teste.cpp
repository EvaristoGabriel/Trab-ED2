#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
//#include <cstdlib>
#include <chrono>
#include <cstdlib>
#include <ctime>
//#include <conio.h>
#include <stdio.h>
#include <stdlib.h>



using namespace std;
using namespace std::chrono;

struct Registro
{
    char id[100]; 
    char review[1000];
    char upvotes[10];
    char version[20];
    char data[20];
};

int ehNum(char c)
{
    //retorna '1' se for caractere

    if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
        return 1;
    else
        return 0;
}

void leArquivoCsv()
{

    ifstream inFile;
    inFile.open("tiktok_app_reviews.csv");

    if (!inFile.is_open())
        cout << "Não foi possível abrir o arquivo" << endl;

    ofstream arq1; // ponteiro do arquivo de review_id
    ofstream arq2; // ponteiro do arquivo de review_text
    ofstream arq3; // ponteiro do arquivo de upvotes
    ofstream arq4; // ponteiro do arquivo de app_version
    ofstream arq5; // ponteiro do arquivo de posted_date
    ofstream tiktok;

    arq1.open("review_id.bin", ios::out);
    arq2.open("review_text.bin", ios::out);
    arq3.open("upvotes.bin", ios::out);
    arq4.open("app_version.bin", ios::out);
    arq5.open("posted_date.bin", ios::out);
    tiktok.open("tiktok_app_reviews.bin", ios::out);

    string str;           // string que fará a leitura linha por linha do aquivo tiktok_app_reviews
    getline(inFile, str); // retirando o cabecalho do arquivo csv
    
    getline(inFile, str);

    while (!inFile.eof()){

        int cont;
        int tam = 0;

    // Armazenando o review_id do csv em um arquivo próprio:
        for (cont = 0; str[cont] != ','; cont++);

        for (int i = 0; i < cont; i++){
            arq1 << str[i];
            tiktok << str[i];
        }
            
        arq1 << endl;

        cont++;
        tam = cont;

    // Armazenando o review_text do csv em um arquivo próprio:
        while (true)
        {
            if(str[cont] == '\n'){
                cout << "Houve quebra de linha";
                str[cont] == ' ';
            }
            if (str[cont] == ',' && (ehNum(str[cont + 1]) == 1) && (ehNum(str[cont + 2]) == 1 || str[cont + 2] == ',') && (ehNum(str[cont + 3]) == 1 || str[cont + 3] == ','))
                break;
            cont++;
        }

        for (int i = tam; i < cont; i++){
            arq2 << str[i];
            tiktok << str[i];    
        }
        arq2 << endl;

        cont++;
        tam = cont;

    // Armazenando upvotes do csv em um arquivo próprio:
        for (; str[cont] != ','; cont++);

        for (int i = tam; i < cont; i++){
            arq3 << str[i];
            tiktok<<str[i];
        }
        arq3 << endl;

        cont++;
        tam = cont;

    // Armazenando app_version do csv em um arquivo próprio:
        for (; str[cont] != ','; cont++);     

        for (int i = tam; i < cont; i++){
            arq4 << str[i];
            tiktok << str[i];
        }
        arq4 << endl;

        cont++;
        tam = cont;

    // Armazenando app_version do csv em um arquivo próprio:
        for (; str[cont] != '\0'; cont++);
        
        for (int i = tam; i < cont; i++){
            arq5 << str[i];
            tiktok << str[i];
        }
        arq5 << endl;
        
        tiktok << endl;
        getline(inFile, str);
    }
}

int numLinhas(ifstream &inFile){

    int lin = 0; // número de linhas do arquivo de entrada

    string str;

    while (! inFile.eof())
    {
        getline (inFile, str);
        lin++;
    }

    return lin;
}

void acessaRegistro(int i)
{
    ifstream inFile;
    inFile.open("tiktok_app_reviews.bin", ios::app);

    if(!inFile.is_open()){
        cout << "Não foi possível abrir o arquivo!";
    }
    else{
        string linha;
        int numlinhas = numLinhas(inFile);
        /* int j;
        cout << "Procurar linha do arquivo";
        for(j = 0; j < i; j++){
            getline(inFile, linha); 
        }

        if(j == i){
            for(int k = 0; k<linha.length();k++){
                cout<< linha[k];
            }
        } */
        for(int j = 0; j<numlinhas;j++){
            if(j == i){
                getline(inFile,linha);
            }
        }
        cout << linha;

        inFile.close();
    }
    

}

void testeImportacao()
{
    int num = 0;

    leArquivoCsv();

    ifstream inFile;
    inFile.open("tiktok_app_reviews.csv");

    int lin = numLinhas(inFile);

    do
    {
        cout << "Menu do teste de importacao:" << endl;
        cout << "Digite 1 - Para exibir a saida no console" << endl;
        cout << "Digite 2 - Para exibir a saida em um arquivo .txt" << endl;
        cout << "digite 3 - Para finalizar o programa" << endl;

        cin >> num;

        if (num == 1){
            // saida no console, n = 10

            int n; // contador do numero de registros
            string str; // string que vai armazenar a linha do arquivo

            int num;

            for(n = 0; n < 10; n++)
            {
                //num = rand()%lin;
                acessaRegistro(rand()%lin);
                // ainda não consegui fazer a impressao correta, algum erro ainda não identificado
                // a funcao acessaRegistro imprime a linha, no entanto, nao esta imprimindo.
            }


        }
        else if (num == 2){
            // saida no arquivo, n = 100

            int n; // contador do numero de registros

            for(n = 0; n < 100; n++)
                acessaRegistro(rand()%lin);
                //mesmo erro acima
            

            cout << "Arquivo gerado com sucesso!" << endl;
            break;


        }
        else{
            cout << "Valor invalido, por favor, digite novamente." << endl;
            cout << "############################################" << endl << endl;
        }

    }while(num != 3);


}

template <typename T>
void troca(T &a, T &b)
{
    T aux = a;
    a = b;
    b = aux;
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
void QuickSort(T *v, int n)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    QuickSortRec(v, 0, n - 1);
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
}

void Heapify(int *v, int i, int n)
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

void constroiHeap(int *v, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(v, i, n);
}

void HeapSortRec(int *v, int n)
{
    constroiHeap(v, n);
    while (n > 0)
    {
        troca(v[0], v[n - 1]);
        Heapify(v, 0, n - 1);
        n--;
    }
}

void HeapSort(int *v, int n)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    HeapSortRec(v, n);
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
}

int getProxGap(int gap)
{
    gap = (gap * 10) / 13;
    if (gap < 1)
        return 1;
    return gap;
}

void CombSort(int *vet, int n)
{
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
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
}

void menuPrincipal()
{
    /* O programa deve oferecer ao usuário um menu para permitir a escolha de qual etapa será executada:
        Ordenação
        Hash
        Módulo de Teste
         */

    int op;

    cout << "Digite uma opcao para continuar: " << endl;
    cout << "1 - Ordenação" << endl;
    cout << "2 - Hash" << endl;
    cout << "3 - Módulo teste" << endl;
    cout << "Digite: ";

    cin >> op;

    switch (op){
    case 1:
    {
       
        menuPrincipal();
        break;
    };
    case 2:
    {
        
        menuPrincipal();
        break;
    };

    case 3:
    {
        /* O módulo de teste deve permitir a realização de algumas operações para garantir que as funções básicas do programa entregam resultados corretos sob quantidades menores de registros. 
        Esse módulo deve conter funções para escrever as saídas em um arquivo teste.txt das seguintes operações:
        O resultado de cada um dos algoritmos de ordenação.
        O resultado das versões do app mais frequentes
        Para estes testes, considere a ordenação de N=100 reviews aleatórios. */
        menuPrincipal();
        break;
    }

    default:
        break;
    }
}

int main()
{
    srand((unsigned)time(NULL));
    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    ifstream inFile("tiktok_app_reviews.csv");
    ofstream outFile("reduzido.csv");

    int bufSize = 10000000;
    char *buffer = new char[bufSize];

    inFile.read(buffer,bufSize);
    outFile.write(buffer,bufSize);

    delete [] buffer;


    //ifstream csv("tiktok_app_reviews.csv");
    /* ifstream csv("reduzido.csv");
    //ofstream bin("tiktok_app_reviews.bin");
    ofstream bin("reduzido.bin",ios::out);

    

    bin.close();
    csv.close();

    //ifstream inBin("tiktok_app_reviews.bin");
    ifstream inBin("reduzido.bin");
    inBin.close(); */

    //menuPrincipal();  
    //acessaRegistro(2825393);
    //leArquivoCsv();
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;

    return 0;
}
