#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MAXNUMVERTICES 100
#define AN -1
#include "./fila.h"

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
