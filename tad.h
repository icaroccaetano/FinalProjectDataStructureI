#include <stdio.h>
#include <stdlib.h>

typedef struct TipoItem {
    char *nome;
    int gf, gs; //gols feitos e gols sofridos
    int pts; //pontos
} TipoItem;

typedef struct No {
    TipoItem time;
    struct No *prox;
} No;

typedef struct Lista {
    No *inicio;
    No *fim;
    int tam, rodada;
} Lista;    

void init(Lista *lista);

void insereTime(Lista *lista, char *nomeTime);

void imprimeTabela(Lista lista);

void libera(Lista *lista);