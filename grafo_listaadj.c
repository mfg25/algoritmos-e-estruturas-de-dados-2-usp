#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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

bool inicializaGrafo(GRAFO* gr, int nv) {
    gr->numVertices = nv;
    gr->numArestas = 0;
    gr->adj = (VERTICE*)malloc(nv * sizeof(VERTICE));
    if (gr->adj == NULL) {
        return false; // Falha na alocação de memória
    }
    int i;
    for (i = 0; i < nv; i++) {
        gr->adj[i].cab = NULL;
    }
    return true; // Operação concluída com sucesso
}


ADJACENCIA* criaAdj(int v, Peso peso){
    ADJACENCIA *temp = (ADJACENCIA *) malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return (temp);
}

bool existeAresta(int v1, int v2, GRAFO* gr){
    ADJACENCIA* adj = gr->adj[v1].cab;
    while (adj != NULL) {
            if(adj->vertice == v2)return true;
            adj = adj->prox;
        }
    return false;
}

double pegaPesoAresta(int v1, int v2, GRAFO* gr){
    ADJACENCIA* adj = gr->adj[v1].cab;
    while (adj != NULL) {
            if(adj->vertice == v2)return adj->peso;
            adj = adj->prox;
        }
    return false;
}

bool criaArestaNaoDirecionada(int v1, int v2, Peso peso, GRAFO* gr){
    if(peso == 0) return false;
    ADJACENCIA* novo1 = criaAdj(v1, peso);
    novo1->prox = gr->adj[v2].cab;
    gr->adj[v2].cab = novo1;

    ADJACENCIA* novo2 = criaAdj(v2, peso);
    novo2->prox = gr->adj[v1].cab;
    gr->adj[v1].cab = novo2;

    gr->numArestas++;
    return true;
}

