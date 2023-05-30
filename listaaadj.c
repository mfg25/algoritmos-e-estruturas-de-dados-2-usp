#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "./fila.h"
#define MAXNUMVERTICES 100
#define AN -1

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

void imprimeLista(GRAFO* g){
    printf("Numero de arestas: %d\nNumero de vertices: %d\n", g->numArestas, g->numVertices);
    int i;
    for(i = 0; i < g->numVertices; i++){
        printf("v%d: ", i);
        ADJACENCIA* iterador = g->adj[i].cab;
        while(iterador){
            printf("v%d(%.1f) ", iterador->vertice, iterador->peso);
            iterador = iterador->prox;
        }
        printf("\n");
    }
}

int maxDist(GRAFO* gr, double dist[], bool mstSet[]){

    int maxValue = INT_MIN;
    int max_index;

    for(int v = 0; v < gr->numVertices; v++){
        if(mstSet[v] == false && dist[v] > maxValue){
            maxValue = dist[v];
            max_index = v;
        }
    }
    return max_index;
}

void primMST(GRAFO* gr, double* dist, int* pai) {
    bool mstSet[gr->numVertices];
    for (int i = 0; i < gr->numVertices; i++) {
        dist[i] = INT_MIN;
        mstSet[i] = false;
    }
    dist[0] = 0;
    pai[0] = 0;
    for (int i = 0; i < gr->numVertices - 1; i++) {
        int u = maxDist(gr, dist, mstSet);
        mstSet[u] = true;
        ADJACENCIA* adj = gr->adj[u].cab;
        while (adj != NULL) {
            int v = adj->vertice;
            Peso peso = adj->peso;
            if (mstSet[v] == false && peso > dist[v]) {
                pai[v] = u;
                dist[v] = peso;
            }
            adj = adj->prox;
        }
    }
}

double pegarAltura(double alturaMin){
    double i = 0;
    while(alturaMin > i && i <= 4.5){
        i = i + 0.5;
    }
    return i - 0.5;
}

void bfs(GRAFO* gr, int inicio, int fim, double* dist, int* pai) {
    bool visitado[gr->numVertices];
    visitado[inicio] = true;

    FILA fila;
    inicializarFila(&fila);
    inserirNaFila(&fila, inicio);

    while (numeroDeElementosFila(&fila) != 0) {
        int verticeAtual;
        excluirDaFila(&fila, &verticeAtual);
        ADJACENCIA* atual = gr->adj[verticeAtual].cab;
        while (atual != NULL) {
            int reg = atual->vertice;
            if (!visitado[reg]) {
                visitado[reg] = true;
                dist[reg] = atual->peso;
                pai[reg] = verticeAtual;
                inserirNaFila(&fila, reg);
            }
            atual = atual->prox;
        }
    }
}

int menorDist(GRAFO* g, bool* aberto, double* d){
    int i;
    for(i = 0; i < g->numVertices; i++){
        if(aberto[i]) break;
    }
    if(i == g->numVertices) return -1;
    int menor = i;
    for (i = menor+1; i < g->numVertices; i++){
        if(aberto[i] && (d[menor] > d[i])){
            menor = i;
        }
    }
    return menor;
}

double encontraAltura(GRAFO* gr, int pai[], double dist[], int inicio, int fim) {
    int atual = fim;
    double alturaMin = pegarAltura(dist[atual]);
    while (atual != inicio) {
        if(dist[atual] < alturaMin){
            alturaMin = pegarAltura(dist[atual]);

        }

        atual = pai[atual];
    }
    return alturaMin;
}
