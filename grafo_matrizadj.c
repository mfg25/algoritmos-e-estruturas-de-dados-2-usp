#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXNUMVERTICES 100
#define AN -1


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

double pegaPesoAresta(int v1, int v2, GRAFO* gr){
    return gr->mat[v1][v2];
}

bool existeAresta(int v1, int v2, GRAFO* gr){
    if(gr->mat[v1][v2] != -1) return true;
    else return false;
}

bool verificaParametros(int v1, int v2, GRAFO grafo){
    if((v1 > grafo.numVertices) || (v2 > grafo.numVertices)){
        fprintf(stderr, "Ultrapassou numero de vertices do grafo.");
        return false;
    }
    if((v1 < 0) || (v2 < 0)){
        fprintf(stderr, "vertices admitem valores > 0");
        return false;
    }
    return true;
}

bool inicializaGrafo(GRAFO* grafo, int nv){
    if(nv > MAXNUMVERTICES || nv <= 0){
        fprintf(stderr, "Erro na inicializacao do grafo.");
        return false;
    }
    int i;
    int j;
    grafo->numVertices = nv;
    grafo->numArestas = 0;
    for(i = 0; i < nv; i++){
        for(j = 0; j < nv; j++){
            grafo->mat[i][j] = AN;
        }
    }
    return true;
}

bool criaArestaNaoDirecionada(int v1, int v2, Peso peso, GRAFO* grafo){
    if(verificaParametros(v1, v2, *grafo)){
        grafo->mat[v1][v2] = peso;
        grafo->mat[v2][v1] = peso;
        grafo->numArestas++;
        return true;
    }else{
        return false;
    }
}


