#ifndef GRAFO_MATRIZADJ_H_INCLUDED
#define GRAFO_MATRIZADJ_H_INCLUDED

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

typedef struct{
    Peso mat[MAXNUMVERTICES+1][MAXNUMVERTICES+1];
    int numVertices;
    int numArestas;
}GRAFO;

void inicializarFila(FILA* f);

int numeroDeElementosFila(FILA* f);

bool inserirNaFila(FILA* f, int reg);

bool excluirDaFila(FILA* f, int* reg);

bool verificaParametros(int v1, int v2, GRAFO grafo);

bool inicializaGrafo(GRAFO* grafo, int nv);

bool criaArestaNaoDirecionada(int v1, int v2, Peso peso, GRAFO* grafo);

int maxDist(GRAFO* gr, double dist[], bool mstSet[]);

double* primMST(GRAFO* gr, double* dist, int* pai);

double pegarAltura(double alturaMin);

bool bfs(GRAFO* gr, int inicio, int fim, double* dist, int* pai);

double encontraAltura(GRAFO* gr, int pai[], double dist[], int inicio, int fim);




#endif // GRAFO_MATRIZADJ_H_INCLUDED
