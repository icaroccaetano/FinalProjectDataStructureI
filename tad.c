#include "tad.h"

void init(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    lista->rodada = 0;
    lista->contj = 0;
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

int insereTime(Lista *lista, char *nomeTime) {
    if (conferenome (lista,nomeTime)==1) 
    {
        printf("Erro - Nome de time ja utilizado\n");
        return  1;
    }
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
    aux->time.id = (int*) malloc (tamNome*sizeof(int));
    stringing_to_int(aux->time.id, nomeTime);
    
    printf("Nome do time: %s\n", aux->time.nome); //printa o nome do time na tela

    if(lista->tam == 0) { // se a lista estiver vazia
        lista->inicio = aux;
        lista->fim = aux;
        aux->prox = NULL;
    }
    else {
        lista->fim->prox = aux; // se nao estiver vazia
        lista->fim = aux;
        aux->prox = NULL;
    }
    lista->tam++;

    //inicializando as estatísticas do time
    aux->time.gf = 0;
    aux->time.gs = 0;
    aux->time.pts = 0;
    return 0;
}

void imprimeTabela(Lista lista) {
    int i = 1;
    printf("      TIME   -      PTS - GF - GS\n");
    while(lista.inicio != NULL) { //percorre a tabela toda imrpimindo os dados do time
        printf("%d - %-15s - %d - %d - %d\n", i, lista.inicio->time.nome, lista.inicio->time.pts, lista.inicio->time.gf, lista.inicio->time.gs);
        i++;
        lista.inicio = lista.inicio->prox;
    }
}

void libera(Lista *lista) {
    No *aux = (No*)malloc(sizeof(No));
    aux = lista->inicio;
    while(aux != NULL) { //percorre toda a lista dando free nos malloc que utilizamos
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

int conferenome (Lista *lista, char *teste) //confere se ja tem um time com esse nome -> USAR TAMBEM NA HORA DE ATUALIZAR RODADA PARA VER SE O NOME DO TIME QUE FOI COLOCADO E VALIDO 
{
    No *AUX;
    AUX = lista->inicio;
    while (AUX != NULL)
    {
        if (strcmp(AUX->time.nome,teste)==0) return 1;
        AUX = AUX->prox;
    }
    return 0;
}

void vitoria (Lista *lista, int time)
{
    /*recebe a id do time e da mais 3 pts pra ele*/
    /*chamada pela atpartida*/
}

void empate (Lista *lista, int time) //adiciona ponto 1 ao time
{
    /*recebe a id do time e da mais 1 pt pra ele*/
    /*chamada pela atpartida tbm*/
}

void atgols (Lista *lista, int time, int gf, int gs) //atualiza valores de gols do time
{
    /*vai receber a id do time e quantos gols sofreu e fez, aqui vai atualizar na struct */
    /*vai ser chamada pela atpartida*/
}

int conferejogo (Lista *lista, int a, int b)
{
    /* Vai consultar na  nossa matriz que salva quais partidas ja ocorreram se determinado encontro ja aconteceu e retornar sim ou nao*/
}

int atpartida (Lista *lista, int nome1, int gnome1, int nome2, int gnome2) //recebe uma partida e atualiza as structs dos respectivos times
{
    /*PROCESSA O PLACAR*/
    /*vai atualizar os pontos, gols sofridos e gols feitos de cada time */ 
    /*alem disso vai colocar na matriz que esse jogo ja ocorreu*/
}


void atrodada (Lista *lista)
{
    int i, g1, g2, id1, id2;
    char *nome1, *nome2;
    printf ("JOGOS DA RODADA\n");
    printf ("No total sao %d jogos, insira-os separados por um enter\n", nTimes/2);
    for (i=0;i<nTimes;i++)
    {
        printf ("JOGO %d", (i+1));
        printf ("Time de casa: ");
        scanf ("%[^\n]%*c", nome1); /*depois colocar aqui a função para verificar se esse time existe -> usar a mesma que usei na hora de inserir os nome sdo time no inicio*/
        printf ("Gols feitos por ele: ");
        scanf("%d", &g1);
        printf ("Time de fora: ");
        scanf ("%[^\n]%*c", nome2);
        printf ("Gols feitos por ele: ");
        scanf("%d", &g2);
        stringing_to_int(&id1,nome1);
        stringing_to_int(&id2,nome2); /*transformeu o nome dos times em int (peguei a id deles*/

        //* If (*FUNCAO QUE INFORMA SE O JOGO JA OCORREU* DER SIM)
        {
            printf ("ERRO - JOGO JA OCORREU");
            i--;
            continue;
        }
        atpartida (lista,id1,g1,id2,g2); //se o jogo nao tiver ocorrido vamos para o atualiza partida
        
    }
}
 
void tabela (Lista *lista) //vai atualizar a tabela de acordo com os resultados da rodada
{
    /*vai conferir quem tem mais ponto e colocar nas devidas posicoções*/
    /*Em caso de mesma pontuação: criterios de desempate:
    1 - Saldo de Gols
    2 - Mais gols feitos
    3 - Menos gols sofridos */
    
}

void stringing_to_int(int *id, char * string ) { //Cria a id do time a a partir do seu nome 
    int i;

    for (i=0;string[i] != '\0'; i++)
    {
        id[i] = (int) string[i];
    }
    id[i] = -1;
    return;
}