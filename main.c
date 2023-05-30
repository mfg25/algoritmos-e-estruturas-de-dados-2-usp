#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./listaadj.h"


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
