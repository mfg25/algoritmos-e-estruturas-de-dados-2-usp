#ifndef LISTAADJ_H_INCLUDED
#define LISTAADJ_H_INCLUDED

#include <stdbool.h>

typedef double Peso;

typedef struct aux{
    int reg;
    struct aux* prox;
}ELEMENTO, *PONT;

typedef struct{
    PONT inicio;
    PONT fim;
}FILA;

typedef struct ADJACENCIA{
    int vertice;
    Peso peso;
    struct ADJACENCIA *prox;
}ADJACENCIA;

typedef struct vertice{
    ADJACENCIA *cab;
}VERTICE;

typedef struct grafo{
    int numVertices;
    int numArestas;
    VERTICE* adj;
}GRAFO;

void inicializarFila(FILA* f);

int numeroDeElementosFila(FILA* f);

bool inserirNaFila(FILA* f, int reg);

bool excluirDaFila(FILA* f, int* reg);


bool inicializaGrafo(GRAFO* gr, int nv);

ADJACENCIA* criaAdj(int v, Peso peso);

bool criaArestaNaoDirecionada(int v1, int v2, Peso peso, GRAFO* gr);

int maxDist(GRAFO* gr, double dist[], bool mstSet[]);

void primMST(GRAFO* gr, double* dist, int* pai);

double pegarAltura(double alturaMin);

void bfs(GRAFO* gr, int inicio, int fim, double* dist, int* pai);

double encontraAltura(GRAFO* gr, int pai[], double dist[], int inicio, int fim);


#endif // LISTAADJ_H_INCLUDED
