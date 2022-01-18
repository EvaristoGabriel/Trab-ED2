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
#include "Ordenacao.cpp"
using namespace std;
using namespace std::chrono;

struct Registro
{
    char id[90];
    char review[1000];
    int upvotes;
    char version[10];
    char data[20];
};

void Processamento()
{
   /*  ifstream csv("tiktok_app_reviews.csv");
    ofstream bin("tiktok_app_reviews.bin",ios::binary); */
     ifstream csv("reduzido.csv");
    ofstream bin("reduzido.bin",ios::binary);
    ofstream upvotes("Upvotes.txt",ios::out);
    ofstream version("Versao.txt",ios::out);

    Registro teste;
    int bufSize = 100000000;
    char *buffer = new char[bufSize];
    string header;
    getline(csv, header);
    csv.read(buffer, bufSize);
    int campo = 0;
    bool inreviewtext = false;
    int textIdx = 0;
    ofstream textBin("reviews.bin", ios::binary);
    while (csv.gcount() > 0)
    {
        int ini = 0;
        for (int pos = 0; pos < csv.gcount(); pos++)
        {
            if (buffer[pos] == ',' || buffer[pos] == '\n')
            {
                if (!inreviewtext)
                {
                    int val,textSize = pos - ini;
                    char app[20];
                    switch (campo)
                    {
                    case 0:
                        bin.write(&buffer[ini], 89);
                        break;
                    case 1:
                        bin.write(reinterpret_cast<const char *>(&textIdx), sizeof(int));
                        textBin.write(reinterpret_cast<const char *>(&textSize), sizeof(int));
                        textBin.write(&buffer[ini], textSize);
                        textIdx += textSize + sizeof(int);
                        break;
                    case 2:
                        val = atoi(&buffer[ini]);
                        bin.write(reinterpret_cast<const char *>(&val), sizeof(int));
                        upvotes << val;
                        upvotes<< "\n";
                        break;
                    case 3:
                        char versao[20];
                        strncpy(versao,&buffer[ini], pos -ini +1);
                        bin.write(versao, 10);
                        version.write(versao,10);
                        version << "\n";
                        break;
                        
                    case 4:
                        bin.write(&buffer[ini], 19);
                        break;
                    }
                    
                    ini = pos + 1;
                    campo = (campo + 1) % 5;
                }
            }
            else
            {
                if (buffer[pos] == '"' && !inreviewtext)
                {
                    inreviewtext = true;
                }
                else if(buffer[pos] == '"'){
                    if (buffer[pos + 1] != '"')
                    {
                        if (buffer[pos + 1] == ',' )
                        {
                            inreviewtext = false;
                        }
                    }
                    else {
                        pos++;
                    }

                }
            }
        }

        csv.read(buffer, bufSize);
    }
    delete[] buffer;
        
    bin.close();
    csv.close();
    upvotes.close();
}

int numLinhas(ifstream &inFile)
{
    int lin = 0; // número de linhas do arquivo de entrada

    string str;

    while (!inFile.eof())
    {
        getline(inFile, str);
        lin++;
    }

    return lin - 1;
}

void acessaRegistroI(int option,int save){

    //ifstream bin("tiktok_app_reviews.bin", ios::binary);
    ifstream bin("reduzido.bin", ios::binary);
    ifstream textBin("reviews.bin", ios::binary);

    bin.seekg(0, ios::beg);
    int size = 2*sizeof(int) +120;
    bin.seekg(option * size, ios::beg);
    Registro reg;
    int dText, textSize;
    bin.read((char *)(&reg.id), 89);
    bin.read((char *)(&dText), sizeof(int));
    bin.read((char *)(&reg.upvotes), sizeof(int));
    bin.read((char *)(&reg.version), 9);
    bin.read((char *)(&reg.data), 19);
    textBin.seekg(dText, ios::beg);
    textBin.read((char *)(&textSize), sizeof(int));
    textBin.read((char *)(&reg.review), textSize);

    if(save == 1){
        cout << "Id: " << reg.id << endl;
        cout << "Review Text: " << reg.review << endl;
        cout << "Upvotes: " << reg.upvotes << endl;
        cout << "Version: " << reg.version << endl;
        cout << "Data : " << reg.data <<endl;
    }
    else{
        ofstream import ("Importacao.txt",ios::out);
        import << reg.id << ",";
        import << reg.review << ",";
        import << reg.upvotes << ",";
        import << reg.version << ",";
        import << reg.data <<endl;
    }
    

    bin.close();
    textBin.close();
}



void testeImportacao()
{
    int num = 0;
    int n;

    ifstream inFile;
    //inFile.open("tiktok_app_reviews.csv");
    inFile.open("reduzido.csv");
    int lin = numLinhas(inFile);
    
    inFile.close();

    do
    {
        cout << "Menu do teste de importacao:" << endl;
        cout << "Digite 1 - Para exibir a saida no console" << endl;
        cout << "Digite 2 - Para exibir a saida em um arquivo importacao.txt" << endl;
        cout << "digite 3 - Para finalizar o programa" << endl;

        cin >> num;

        if (num == 1)
        {
            // saida no console, n = 10

            n = 10;// contador do numero de registros

            for (int i = 0; i < n; i++)
            {
                acessaRegistroI(rand() % lin,1);
            }
        }
        else if (num == 2)
        {
            // saida no arquivo, n = 100

            n = 100; // contador do numero de registros

            for (int i = 0; i < n; i++)
                acessaRegistroI(rand() % lin,2);

            cout << "Arquivo gerado com sucesso!" << endl;
            break;
        }
        else
        {
            cout << "Valor invalido, por favor, digite novamente." << endl;
            cout << "############################################" << endl
                 << endl;
        }

    } while (num != 3);
}



void PegaLinha(int *v, int i, int numlinhas)
{
    ifstream inFile("Upvotes.txt");
    int numaleatorio = rand() % numlinhas;
    string linha;
    int j = 0;
     while (true)
    {
        getline(inFile, linha);
        if (j + 1 == numaleatorio)
        {
            v[i] = stoi(linha);
            break;
        }
        j++;
    } 
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
    cout << "1 - Acessar i-esimo registro" << endl;
    cout << "2 - Importacao" << endl;
    cout << "3 - Ordenacao" << endl;
    cout << "Qualquer outro para sair do programa!"<<endl;
    cout << "Digite: ";

    cin >> op;

    switch (op)
    {
    case 1:
    {
        cout << "Qual registro você quer acessar?"<<endl;
        int opc;
        cin >> opc;
        acessaRegistroI(opc,1);
        menuPrincipal();
        break;
    };
    case 2:
    {
        testeImportacao();
        menuPrincipal();
        break;
    };

    case 3:
    {
        int M = 0;
        ifstream arq("Upvotes.txt");
        ofstream saida("Saida.txt",ios::out);
        int numlinhas = numLinhas(arq);
        while (M < 1)
        {
            saida << "Para M = "<< M+1 << ": "<<endl;

            // Utilizando N = 5.000
            int N = 500000;
            int *vetQ = new int[N];
            int *vetH = new int[N];
            int *vetC = new int[N];

            for (int i = 0; i < N; i++)
            {
                PegaLinha(vetQ,i,numlinhas);
                cout << i << " ";
                vetH[i] = vetQ[i];
                vetC[i] = vetQ[i];
            }

            double tempoQ, tempoH, tempoC;
            tempoQ = QuickSort(vetQ, N,saida);

            tempoH = HeapSort(vetH, N,saida);

            tempoC = CombSort(vetC, N,saida);

            double mediatempos = (tempoQ + tempoH + tempoC)/3;

            saida << "A media de tempos para M = " << M+1 << " é de " << mediatempos << "segundos"<<endl<<endl;


            M++;
        }
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
    
    /* ifstream inFile("tiktok_app_reviews.csv");
    ofstream outFile("reduzido.csv");
    int bufSize = 100000000;
    char *buffer = new char[bufSize];
    inFile.read(buffer,bufSize);
    outFile.write(buffer,bufSize);
    delete [] buffer; */

    Processamento();
    menuPrincipal();

   
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;

    return 0;
}