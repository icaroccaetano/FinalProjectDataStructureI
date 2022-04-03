#include "tad.h"

void init(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    lista->rodada = 0;
    lista->historico.contjogos = 0;
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
    int lenVet;
    int valorId;
    if (conferenome (lista,nomeTime)==1) 
    {
        printf("ERRO: %s ja foi inserido.\n", nomeTime);
        return  1;
    }
    No *aux = (No*)malloc(sizeof(No));
    int tamNome, i=0; //tamNome vai receber o tamanho do nome do time recebido, para que seja mais facil alocar memoria ao vetor de caracteres que lista->time.nome vai receber.
    tamNome = tamanhoNome(nomeTime);
    //printf("Tamanho do nome do time: %d\n", tamNome);
    
    //Aqui estamos colocando dentro da lista de apontadores os nomes de cada time e seu respectivo id
    aux->time.nome = (char*)malloc(tamNome * sizeof(char)); //alocando memoria para colocar o nome do time
    while(nomeTime[i] != '\0') {
        aux->time.nome[i] = nomeTime[i];
        i++;
    }
    aux->time.nome[i] = '\0'; //adicionando o caractere de fim de string no nome do time
    aux->time.id = (int*) malloc ((tamNome+1)*sizeof(int));
    stringing_to_int(aux->time.id, nomeTime);

    //Aqui estamos colocando dentro do vetor de times os nomes de cada time e seu respectivo id
    i=0;
    lista->listaVet.timeVet[lista->tam].nome = (char *)malloc(tamNome * sizeof(char)); 
    while(nomeTime[i] != '\0') {
        lista->listaVet.timeVet[lista->tam].nome[i] = nomeTime[i];
        i++;
    }
    lista->listaVet.timeVet[lista->tam].nome[i] = '\0'; //adicionando o caractere de fim de string no nome do time
    lista->listaVet.timeVet[lista->tam].id = (int*) malloc ((tamNome+1)*sizeof(int));
    stringing_to_int(lista->listaVet.timeVet[lista->tam].id, nomeTime);
    valorId = somaId(lista->listaVet.timeVet[lista->tam].id, tamNome); //passamos tamNome como parametro para colocar ele como expoente de base 10, como se usassemos ordens de grandeza para gerar um numero atraves de um vetor. Em que a posição 0 possui o maior expoente(tamNome - 1) e a útima posiçao teria o expoente 0
    lista->idTimes[lista->tam].idT = (unsigned short int)valorId;
    
    //inicializando as estatisticas dos times dentro do vetor
    lista->listaVet.timeVet[lista->tam].gf = 0;
    lista->listaVet.timeVet[lista->tam].gs = 0;
    lista->listaVet.timeVet[lista->tam].pts = 0;

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

// void imprimeTabela(Lista lista) {
//     int i = 1;
//     printf("      TIME   -      PTS - GF - GS\n");
//     while(lista.inicio != NULL) { //percorre a tabela toda imrpimindo os dados do time
//         printf("%d - %-15s - %d - %d - %d\n", i, lista.inicio->time.nome, lista.inicio->time.pts, lista.inicio->time.gf, lista.inicio->time.gs);
//         i++;
//         lista.inicio = lista.inicio->prox;
//     }
// }


//imprimindo a tabela usando o vetor de times
void imprimeTabela(Lista lista) {
    int i;
    printf("      TIME            PTS        GF         GS\n");
    for(i=0;i<lista.tam;i++) { //percorre a tabela toda imrpimindo os dados do time
        printf("%d - %-15s   %-8d   %-8d   %-8d   (%d)\n", i+1, lista.listaVet.timeVet[i].nome, lista.listaVet.timeVet[i].pts, lista.listaVet.timeVet[i].gf, lista.listaVet.timeVet[i].gs, lista.idTimes[i].idT);
        
    }
}

void imprimeTabelaGF(Lista lista) { //imprimir tabela dos times em relação aos Gols Feitos (do maior ao menor)
    int i, j=1;
    printf("      TIME               GF\n");
    for(i=lista.tam-1;i>=0;i--) {
        printf("%d - %-20s %d\n", j, lista.listaVet.timeVet[i].nome, lista.listaVet.timeVet[i].gf);
        j++;
    }
}

void imprimeTabelaGS(Lista lista) { //imprimir tabela dos times em relação aos Gols Sofridos (do maior ao menor)
    int i, j=1;
    printf("      TIME               GS\n");
    for(i=lista.tam-1;i>=0;i--) {
        printf("%d - %-20s %d\n", j, lista.listaVet.timeVet[i].nome, lista.listaVet.timeVet[i].gs);
        j++;
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

void atpartida (Lista *lista, int nome1, int gnome1, int nome2, int gnome2) //recebe uma partida e atualiza as structs dos respectivos times
{
    /*PROCESSA O PLACAR*/
    /*vai atualizar os pontos, gols sofridos e gols feitos de cada time */ 
    /*alem disso vai colocar na matriz que esse jogo ja ocorreu*/
    int sentinela, i;

    //realizamos uma busca sequencial para encontrar a id do time da casa na lista, ao encontrar, seus dados são atualizados
    sentinela = nome1;
    for(i=lista->tam-1;i>=0;i--) {
        if(sentinela == lista->idTimes[i].idT) {
            lista->listaVet.timeVet[i].gf += gnome1;
            lista->listaVet.timeVet[i].gs += gnome2;
            if(gnome1 > gnome2) lista->listaVet.timeVet[i].pts += 3; //se o time fez mais gols do que sofreu, ele ganhou a partida, portanto recebe 3 pontos
            else if(gnome1 == gnome2) lista->listaVet.timeVet[i].pts++; //se  time fez o mesmo numero de gols no jogo do que sofreu, quer dizer que ele empatou, portanto ele ganha apenas um ponto
            break;
        }
    }

    //realizamos uma busca sequencial para encontrar a id do time visitante na lista, ao encontrar, seus dados são atualizados
    sentinela = nome2;
    for(i=lista->tam-1;i>=0;i--) {
        if(sentinela == lista->idTimes[i].idT) {
            lista->listaVet.timeVet[i].gf += gnome2;
            lista->listaVet.timeVet[i].gs += gnome1;
            if(gnome2 > gnome1) lista->listaVet.timeVet[i].pts += 3; //se o time fez mais gols do que sofreu, ele ganhou a partida, portanto recebe 3 pontos
            else if(gnome1 == gnome2) lista->listaVet.timeVet[i].pts++; //se  time fez o mesmo numero de gols no jogo do que sofreu, quer dizer que ele empatou, portanto ele ganha apenas um ponto
            break;
        }
    }
}


void atrodada (Lista *lista)
{
    int i, g1, g2, *id1, *id2, tamanho[2], soma[2], aux1, aux2;
    char nome1[20], nome2[20];
    //printf ("JOGOS DA RODADA\n");
    //printf ("No total sao %d jogos, insira-os separados por um enter\n", nTimes/2);
    for (i=0;i<nTimes/2;i++)
    {
        //printf ("JOGO %d:\n", (i+1));
        //printf ("Time de casa: ");
        scanf ("%[^\n]%*c", nome1); 
        while(conferenome(lista, nome1)==0) { //verifica se o time existe
            //printf("ERRO: Time não encontrado.\nColoque o nome do time visitante novamente: ");
            scanf ("%[^\n]%*c", nome1);
        }
        tamanho[0] = strlen(nome1);
        // printf("LEN 1: %d\n", tamanho[0]);
        // printf ("Gols feitos por ele: ");
        scanf("%d", &g1);
        

        //printf ("Time visitante: ");
        scanf ("%*c%[^\n]%*c", nome2);
        while(conferenome(lista, nome2)==0) { //verifica se o time existe
            //printf("ERRO: Time não encontrado.\nColoque o nome do time visitante novamente: ");
            scanf ("%[^\n]%*c", nome2);
        }
        tamanho[1] = strlen(nome2);
        // printf("LEN 2: %d\n", tamanho[1]);
        // printf ("Gols feitos por ele: ");
        scanf("%d%*c", &g2);

        id1 = (int*)malloc((tamanho[0]+1)*sizeof(int));
        stringing_to_int(id1, nome1);

        id2 = (int*)malloc((tamanho[1]+1)*sizeof(int));      
        stringing_to_int(id2, nome2); /*transformeu o nome dos times em int (peguei a id deles)*/

        aux1 = somaId(id1, tamanho[0]);
        soma[0] = (unsigned short int)aux1;
        // printf("Soma 1: %d\n", soma[0]);

        aux2 = somaId(id2, tamanho[1]);
        soma[1] = (unsigned short int)aux2;   
        // printf("Soma 2: %d\n", soma[1]);     
        /*
        if (conferejogo(lista,soma[0],soma[1]) == 1);
        {
            printf ("ERRO - JOGO JA OCORREU\n");
            i--;
            continue;
        }
        */
        adicionajogo (lista,soma[0],soma[1]);
        atpartida(lista, soma[0], g1, soma[1], g2); //se o jogo nao tiver ocorrido vamos para o atualiza partida
        //insertionSortTAB(lista, nTimes);
        
    }
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

int somaId(int *id, int lenVet) { //faremos com que os elementos do vetor se transformem em um número para que seja mais fácil de implementar o algoritmo de busca binaria
    int i, j;
    int soma = 0;
    int exp;

    for(i=0;i<lenVet;i++) {
        exp = (lenVet)-i;
        soma += (id[i]*pow((double)10, exp));
    }

    return soma;
}

void buscaSeqTime(Lista lista, char *nomeTime) { //Busca sequencial no vetor de times
    int cont = 0;
    int i, j, tamNome;
    char *sentinela;

    if(lista.tam == 0) {
        printf("ERRO: Lista vazia.\n");
        return;
    }

    tamNome = strlen(nomeTime);
    sentinela = (char *)malloc(tamNome * sizeof(char)); //alocando memória para que o sentinela possa receber o nome do time
    strcpy(sentinela, nomeTime); //colocando o nome do time no sentinela
    for(i=lista.tam-1;i>=0;i--) {
        if(strcmp(lista.listaVet.timeVet[i].nome, sentinela) == 0) { //comparando o nome do time na posiçao i com o nome do sentinela, se forem iguais, a condição será atendida
            printf("TIME: %s\nGOLS FEITOS: %d\nGOLS SOFRIDOS: %d\nPONTOS: %d\n", lista.listaVet.timeVet[i].nome, lista.listaVet.timeVet[i].gf, lista.listaVet.timeVet[i].gs, lista.listaVet.timeVet[i].pts);
            free(sentinela);
            return; //Caso o time seja encontrado, seu histórico será impresso e será feito um return

        }
    }
    printf("O time %s não foi encontrado.\n", nomeTime); //Caso o for acabe seu loop, significa que o time não foi encontrado na lista, já que não foi feito nenhum return
    free(sentinela);

}

int idtime (Lista lista, char *nomeTime) { //Busca sequencial no vetor de times
    int cont = 0;
    int i, j, tamNome;
    char *sentinela;

    if(lista.tam == 0) {
        return -1;
    }

    tamNome = strlen(nomeTime);
    sentinela = (char *)malloc(tamNome * sizeof(char)); //alocando memória para que o sentinela possa receber o nome do time
    strcpy(sentinela, nomeTime); //colocando o nome do time no sentinela
    for(i=lista.tam-1;i>=0;i--) {
        if(strcmp(lista.listaVet.timeVet[i].nome, sentinela) == 0) { //comparando o nome do time na posiçao i com o nome do sentinela, se forem iguais, a condição será atendida
            free(sentinela);
            return lista.idTimes[i].idT; //Caso o time seja encontrado, seu histórico será impresso e será feito um return

        }
    }
    free(sentinela);
    return -1;
}

void buscaBinTime(Lista lista, char *nomeTime) { //Busca binária no vetor de times
    int esq, dir, i;
    int vet[lista.tam]; //vetor para armazenar as ids dos time
    int id;
    int* idvet;
    for (i=0;i<lista.tam;i++)
    {
        vet[i] = lista.idTimes[i].idT;
    }

    insertionSortLis (&lista,lista.tam);
    id = idtime(lista,nomeTime);

    if(lista.tam == 0) {
        printf("ERRO: Lista vazia.\n");
        return;
    }
    else 
    {
        esq = 0;
        dir = lista.tam-1;
        do 
        {
            i = (esq + dir) / 2;
            if (id > vet[i])
            esq = i + 1;
            else
            dir = i - 1;
        } while (id != vet[i] && esq <= dir);
        if (id == vet[i])
        {
            printf("TIME: %s\nGOLS FEITOS: %d\nGOLS SOFRIDOS: %d\nPONTOS: %d\n", lista.listaVet.timeVet[i].nome, lista.listaVet.timeVet[i].gf, lista.listaVet.timeVet[i].gs, lista.listaVet.timeVet[i].pts);
            return;
        }
        else printf("O time %s não foi encontrado.\n", nomeTime);
        return;
    }
}


void quickSortGF(Lista *lista, int esq, int dir) {
    int pivo = lista->listaVet.timeVet[(esq+dir) / 2].gf;
    int i = esq;
    int j = dir;
    TipoItem aux; //usaremos no swap, será de tipoItem já que iremos fazer swap dos times, não apenas dos Gols


    while(i<=j) {
        while(lista->listaVet.timeVet[i].gf < pivo && i < dir) {
            i++;
        }
        while(lista->listaVet.timeVet[j].gf > pivo && j > esq) {
            j--;
        }

        if(i <= j) {
            aux = lista->listaVet.timeVet[i];
            lista->listaVet.timeVet[i] = lista->listaVet.timeVet[j];
            lista->listaVet.timeVet[j] = aux;
            i++;
            j--;
        }
    }

    if(j > esq) {
        quickSortGF(lista, esq, j);
    }
    if(i < dir) {
        quickSortGF(lista, i, dir);
    }
}

void insertionSortGS(Lista *lista, int tam) {
    int i, j, aux2;
    TipoItem aux;

    for(i=1;i<tam;i++) {
        aux2 = i; //essa variavel vai pegar o valor de i para conseguir manusear o indice dentro do proximo loop

        for(j=i-1;j>=0;j--) { //percorremos o vetor em direçao da esquerda para ver se esxitem valores maiores que o valor da posicao i
            if(lista->listaVet.timeVet[aux2].gs < lista->listaVet.timeVet[j].gs) {  //se o valor à esquerda for maior, ocorre uma troca
                aux = lista->listaVet.timeVet[aux2];
                lista->listaVet.timeVet[aux2] = lista->listaVet.timeVet[j];
                lista->listaVet.timeVet[j] = aux; 
            }
            else break; //se o valor a esquerda não for maior, entao quebra o loop
            aux2--; //aqui atualizamos o novo indice que o valor vai ocupar na lista, por ex: se estivesse na 3a e tivesse ido para a 2a
        }
        
    }
}

void insertionSortTAB(Lista *lista, int tam) {
    int i, j, aux2;
    TipoItem aux;

    for(i=1;i<tam;i++) {
        aux2 = i; //essa variavel vai pegar o valor de i para conseguir manusear o indice dentro do proximo loop

        for(j=i-1;j>=0;j--) { //percorremos o vetor em direçao da esquerda para ver se esxitem valores menores que o valor da posicao i
            if(lista->listaVet.timeVet[aux2].pts > lista->listaVet.timeVet[j].pts) {  //se o valor à direita for maior, ocorre uma troca
                aux = lista->listaVet.timeVet[aux2];
                lista->listaVet.timeVet[aux2] = lista->listaVet.timeVet[j];
                lista->listaVet.timeVet[j] = aux; 
            }
            else if(lista->listaVet.timeVet[aux2].pts == lista->listaVet.timeVet[j].pts) {  //se o valor à esquerda for igual, vamos analisar os criterios de desempate
                if (desempate(&lista->listaVet.timeVet[aux2],&lista->listaVet.timeVet[j]) == 0) //a Função vai conferir se o valor é maior e se for retornara 0 e faremos o swap
                {
                    aux = lista->listaVet.timeVet[aux2];
                    lista->listaVet.timeVet[aux2] = lista->listaVet.timeVet[j];
                    lista->listaVet.timeVet[j] = aux;
                } 
            }
            else break; //se o valor a esquerda não for maior, entao quebra o loop
            aux2--; //aqui atualizamos o novo indice que o valor vai ocupar na lista, por ex: se estivesse na 3a e tivesse ido para a 2a
        }
        
    }
}

void insertionSortLis (Lista *lista, int tam) {
    int i, j, aux2;
    TipoItem aux;

    for(i=1;i<tam;i++) {
        aux2 = i; //essa variavel vai pegar o valor de i para conseguir manusear o indice dentro do proximo loop

        for(j=i-1;j>=0;j--) { //percorremos o vetor em direçao da esquerda para ver se esxitem valores menores que o valor da posicao i
            if(lista->idTimes[aux2].idT > lista->idTimes[j].idT) {  //se o valor à direita for maior, ocorre uma troca
                aux = lista->listaVet.timeVet[aux2];
                lista->listaVet.timeVet[aux2] = lista->listaVet.timeVet[j];
                lista->listaVet.timeVet[j] = aux; 
            }
            else if(lista->idTimes[aux2].idT == lista->idTimes[j].idT) {  //se o valor à esquerda for igual, vamos analisar os criterios de desempate
                if (desempate(&lista->listaVet.timeVet[aux2],&lista->listaVet.timeVet[j]) == 0) //a Função vai conferir se o valor é maior e se for retornara 0 e faremos o swap
                {
                    aux = lista->listaVet.timeVet[aux2];
                    lista->listaVet.timeVet[aux2] = lista->listaVet.timeVet[j];
                    lista->listaVet.timeVet[j] = aux;
                } 
            }
            else break; //se o valor a esquerda não for maior, entao quebra o loop
            aux2--; //aqui atualizamos o novo indice que o valor vai ocupar na lista, por ex: se estivesse na 3a e tivesse ido para a 2a
        }
        
    }
}

int desempate(TipoItem *ana, TipoItem *comp) // Para retornar 0, o ana tem que ser maior que o comp de acordo com os criterios de desempate
{
/*
Os criterios sao:
- Maior saldo de gols
- Maior numero de gols feitos
- Menor numero de gols sofridos
*/
// Conferindo saldo de gols
if ((ana->gf-ana->gs) > (comp->gf-comp->gs)) return 0;
if ((ana->gf-ana->gs) < (comp->gf-comp->gs)) return 1;
// Conferindo gols feitos
if (ana->gf > comp->gf) return 0;
if (ana->gf < comp->gf) return 1;
// Conferindo gols sofridos
if (ana->gs < comp->gs) return 0;
if (ana->gs > comp->gs) return 1;

return 1; //se for tudo igual retorn 1 tambem
}

void adicionajogo (Lista *lista,int a, int b) // adiciona o jogo na matriz que armazena o historico das partidas
{
    lista->historico.jogos[lista->historico.contjogos][0] = a;
    lista->historico.jogos[lista->historico.contjogos][1] = b; 
    lista->historico.contjogos++;
    return;
}
int conferejogo (Lista *lista,int a, int b) // confere se o jogo ja esta na matriz que armazena o historico das partidas
{
    int i;
    for (i=0;i<lista->historico.contjogos;i++)
    {
        if (a ==lista->historico.jogos[i][0])
        {
            if (b ==lista->historico.jogos[i][1]) return 1;
        }
        if (a ==lista->historico.jogos[i][1])
        {
            if (b ==lista->historico.jogos[i][0]) return 1;
        }
    }
    return 0;
}
