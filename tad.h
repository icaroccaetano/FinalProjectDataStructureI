#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nTimes 6
#define N_MAX 128

typedef struct TipoItem {
    char *nome;
    int gf, gs; //gols feitos e gols sofridos
    int pts; //pontos
    int* id;
    
} TipoItem;

typedef struct No {
    TipoItem time;
    struct No *prox;
} No;

typedef struct Lista {
    No *inicio;
    No *fim;
    int tam, rodada;
    int jfeitos[nTimes*(nTimes-1)];
    int contj;
} Lista;    

void init(Lista *lista);

int insereTime(Lista *lista, char *nomeTime);

void imprimeTabela(Lista lista);

void libera(Lista *lista);

int conferenome (Lista *lista, char *teste);

void vitoria (Lista *lista, int time); //adiciona 3 pontos ao time

void empate (Lista *lista, int time); //adiciona ponto 1 ao time

void atgols (Lista *lista, int time, int gf, int gs); //atualiza valores de gols do time

int conferejogo (Lista *lista, int a, int b); // ve se os times ja nao se enfrentaram

int atpartida (Lista *lista, int id1, int gid1, int id2, int gid2); //recebe uma partida e atualiza as structs dos respectivos times

void atrodada (Lista *lista); // coleta os placares da rodada e envia para a funcao de atualizar partida

void stringing_to_int(int *id, char * string ); // string to int -> Usamos para criar uma identidade para o time

void tabela (Lista *lista); //vai atualizar a tabela de acordo com os resultados da rodada