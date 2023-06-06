#ifndef LISTAADJ_H_INCLUDED
#define LISTAADJ_H_INCLUDED

#include <stdbool.h>

typedef double Peso;

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

bool existeAresta(int v1, int v2, GRAFO* gr);

bool inicializaGrafo(GRAFO* gr, int nv);

ADJACENCIA* criaAdj(int v, Peso peso);

double pegaPesoAresta(int v1, int v2, GRAFO* gr);

bool criaArestaNaoDirecionada(int v1, int v2, Peso peso, GRAFO* gr);



#endif // LISTAADJ_H_INCLUDED
