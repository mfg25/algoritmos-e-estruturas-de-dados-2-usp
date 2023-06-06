#ifndef GRAFO_MATRIZADJ_H_INCLUDED
#define GRAFO_MATRIZADJ_H_INCLUDED

#include <stdbool.h>

typedef double Peso;

typedef struct{
    Peso mat[MAXNUMVERTICES+1][MAXNUMVERTICES+1];
    int numVertices;
    int numArestas;
}GRAFO;

bool existeAresta(int v1, int v2, GRAFO* gr);

bool verificaParametros(int v1, int v2, GRAFO grafo);

double pegaPesoAresta(int v1, int v2, GRAFO* gr);

bool inicializaGrafo(GRAFO* grafo, int nv);

bool criaArestaNaoDirecionada(int v1, int v2, Peso peso, GRAFO* grafo);


#endif // GRAFO_MATRIZADJ_H_INCLUDED
