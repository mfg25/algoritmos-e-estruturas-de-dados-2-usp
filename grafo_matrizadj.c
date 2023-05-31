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

void inicializarFila(FILA* f){
    f->inicio = NULL;
    f->fim = NULL;
}

int numeroDeElementosFila(FILA* f){
    PONT i = f->inicio;
    int tam = 0;
    while(i){
        tam++;
        i = i->prox;
    }
    return tam;
}

bool inserirNaFila(FILA* f, int reg){
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    novo->prox = NULL;
    if(f->inicio == NULL) f->inicio = novo;
    else f->fim->prox = novo;
    f->fim = novo;
    return true;
}

bool excluirDaFila(FILA* f, int* reg){
    if(f->inicio == NULL) return false;
    *reg = f->inicio->reg;
    PONT apagar = f->inicio;
    f->inicio = f->inicio->prox;
    free(apagar);
    return true;
}

void imprimeGrafo(GRAFO* grafo){
    int i, j;
    for(i = 0; i < grafo->numVertices; i++){
        for(j = 0; j < grafo->numVertices; j++){
            if(j == grafo->numVertices-1)printf("%.1f\n", grafo->mat[i][j]);
            else printf("%.1f ", grafo->mat[i][j]);
        }
    }
}

int procuraValor(GRAFO grafo, int* coordenada1, int* coordenada2){
    int i, j;
    for(i = 0; i < grafo.numVertices; i++){
        for(j = 0; j < grafo.numVertices; j++){
            if(grafo.mat[i][j] != AN){
                *coordenada1 = i;
                *coordenada2 = j;
                return grafo.mat[i][j];
            }
        }
    }
    return 0;
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

bool retiraAresta(int v1, int v2, GRAFO* grafo){
    if(verificaParametros(v1, v2, *grafo)){
        grafo->mat[v1][v2] = AN;
        return true;
    }else{
        return false;
    }
}

bool liberaGrafo(GRAFO* grafo){
    if(grafo){
        free(grafo);
        return true;
    }else{
        return false;
    }
}

int retiraMinimo(GRAFO* grafo){
    int coordenada1;
    int coordenada2;
    int minimo = procuraValor(*grafo, &coordenada1, &coordenada2);

    int i, j;
     for(i = 0; i < grafo->numVertices; i++){
        for(j = 0; j < grafo->numVertices; j++){
            if(grafo->mat[i][j] < minimo && grafo->mat[i][j] != AN){
                minimo = grafo->mat[i][j];
                coordenada1 = i;
                coordenada2 = j;
            }
        }
    }
    grafo->mat[coordenada1][coordenada2] = AN;
    return minimo;
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

double* primMST(GRAFO* gr, double* dist, int* pai){
    bool mstSet[gr->numVertices];
    for(int i = 0; i < gr->numVertices; i++){
        dist[i] = INT_MIN;
        mstSet[i] = false;
    }
    dist[0] = 0;
    pai[0] = 0;
    for(int i = 0; i < gr->numVertices-1; i++){
        int u = maxDist(gr, dist, mstSet);
        mstSet[u] = true;
        for(int v = 0; v < gr->numVertices; v++){
            if(gr->mat[u][v] && mstSet[v] == false && gr->mat[u][v] > dist[v]){
                pai[v] = u;
                dist[v] = gr->mat[u][v];
            }
        }
    }
}

double pegarAltura(double alturaMin){
    double i = 0;
    while(alturaMin >= i && i <= 4.5){
        i = i + 0.5;
    }
    return i - 0.5;
}

bool bfs(GRAFO* gr, int inicio, int fim, double* dist, int* pai){
    bool visitado[gr->numVertices];
    FILA q;
    inicializarFila(&q);
    visitado[inicio] = true;

    inserirNaFila(&q, inicio);

    while(numeroDeElementosFila(&q) != 0){
        int reg;
        excluirDaFila(&q, &reg);
        for(int i = 0; i < gr->numVertices; i++){
            if(gr->mat[reg][i] != -1 && !visitado[i]){
                dist[i] = gr->mat[reg][i];
                pai[i] = reg;
                visitado[i] = true;
                inserirNaFila(&q, i);
            }
        }
    }
    return false;
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
