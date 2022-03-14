#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

void init(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    if(lista->inicio == NULL && lista->fim == NULL) printf("Lista criada.\n");
    else printf("Erro ao criar lista.");
}

int tamanhoNome(char *nome) {  //função que conta o número de caracteres no nome do time
    int i=0;
    while(nome[i] != '\0') {
        i++;
    }
    return i;
}

void insereTime(Lista *lista, char *nomeTime) {
    No *aux = (No*)malloc(sizeof(No));
    int tamNome, i=0; //tamNome vai receber o tamanho do nome do time recebido, para que seja mais facil alocar memoria ao vetor de caracteres que lista->time.nome vai receber.

    tamNome = tamanhoNome(nomeTime);
    printf("Tamanho do nome do time: %d\n", tamNome);
    
    aux->time.nome = (char*)malloc(tamNome * sizeof(char)); //alocando memoria para colocar o nome do time
    while(nomeTime[i] != '\0') {
        aux->time.nome[i] = nomeTime[i];
        i++;
    }
    aux->time.nome[i] = '\0'; //adicionando o caractere de fim de string no nome do time

    printf("Nome do time: %s\n", aux->time.nome);

    if(lista->tam == 0) {
        lista->inicio = aux;
        lista->fim = aux;
        aux->prox = NULL;
    }
    else {
        lista->fim->prox = aux;
        lista->fim = aux;
        aux->prox = NULL;
    }
    lista->tam++;

    //inicializando as estatísticas do time
    aux->time.gf = 0;
    aux->time.gs = 0;
    aux->time.pts = 0;
}

void imprimeTabela(Lista lista) {
    int i = 1;
    while(lista.inicio != NULL) {
        printf("%d - %s\n", i, lista.inicio->time.nome);
        i++;
        lista.inicio = lista.inicio->prox;
    }
}

void libera(Lista *lista) {
    No *aux = (No*)malloc(sizeof(No));
    aux = lista->inicio;
    while(aux != NULL) {
        free(aux);
        lista->inicio = lista->inicio->prox;
        aux = lista->inicio;
    }
    if(lista->inicio == NULL) {
        printf("Memória desalocada com sucesso.\n");
    }
    else {
        printf("Erro ao desalocar a memória.\n");
    }
}