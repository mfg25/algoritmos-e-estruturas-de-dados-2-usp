#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAXNUMVERTICES 100
#include "./fila.c"
#include "./grafo_listaadj.h"

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

double pegarAltura(double alturaMin){
    double i = 0;
    while(alturaMin >= i && i <= 4.5){
        i = i + 0.5;
    }
    return i - 0.5;
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

void bfs(GRAFO* gr, int inicio, int fim, double* dist, int* pai){
    bool visitado[gr->numVertices];
    FILA q;
    inicializarFila(&q);
    visitado[inicio] = true;

    inserirNaFila(&q, inicio);

    while(numeroDeElementosFila(&q) != 0){
        int reg;
        excluirDaFila(&q, &reg);
        for(int i = 0; i < gr->numVertices; i++){
            if(existeAresta(reg, i, gr) && !visitado[i]){
                dist[i] = pegaPesoAresta(reg, i, gr);
                pai[i] = reg;
                visitado[i] = true;
                inserirNaFila(&q, i);
            }
        }
    }
}

void primMST(GRAFO* gr, double* dist, int* pai){
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
            if(existeAresta(u, v, gr) && mstSet[v] == false && pegaPesoAresta(u, v, gr) > dist[v]){
                pai[v] = u;
                dist[v] = pegaPesoAresta(u, v, gr);
            }
        }
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Quantidade invalida de argumentos.");
    }
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Nao foi possivel abrir o arquivo");
    }

    int numVertices, numArestas, numConsultas;
    fscanf(fp, "%d %d %d", &numVertices, &numArestas, &numConsultas);

    GRAFO gr;
    inicializaGrafo(&gr, numVertices);

    int i;
    double pesoAresta;
    int vertice1 = 0, vertice2 = 0;
    for(i = 0; i < numArestas; i++){
        fscanf(fp, "%d %d %lf", &vertice1, &vertice2, &pesoAresta);
        criaArestaNaoDirecionada(vertice1, vertice2, pesoAresta, &gr);
    }

    int consultas[numConsultas*2];
    int k = 0;
    for(i = 0; i < numConsultas; i++){
        fscanf(fp, "%d %d", &vertice1, &vertice2);
        consultas[k] = vertice1;
        consultas[k+1] = vertice2;
        k += 2;
    }

    double dist[gr.numVertices];
    int pai[gr.numVertices];
    primMST(&gr, dist, pai);

    GRAFO grFinal;
    inicializaGrafo(&grFinal, numVertices);


    for(int i = 0; i < numVertices; i++){
        criaArestaNaoDirecionada(pai[i], i, dist[i], &grFinal);
    }
    FILE* fw;
    fw = fopen("saida.txt", "w");

    for(i = 0; i < numConsultas*2; i += 2){
        bfs(&grFinal, consultas[i], consultas[i+1], dist, pai);
        double tamanho = encontraAltura(&grFinal, pai, dist, consultas[i], consultas[i+1]);
        fprintf(fw, "%.1f\n", tamanho);
    }


    fclose(fw);
    fclose(fp);
    return -1;
}
