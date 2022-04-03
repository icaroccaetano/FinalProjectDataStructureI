#include "tad.h"

int main() {
    Lista lista;
    char nome[30];
    int i, j; 

    init(&lista);
    printf("\n");

    printf ("O PROGRAMA ESTA SETADO PARA UM CAMPEONATO DE %d JOGOS\n", nTimes);
    printf("--------------------------------------------------------\n");

    printf("\n------------------INSERINDO OS TIMES--------------------\n");
    for(i=0;i<nTimes;i++) {
        scanf("%[^\n]%*c", nome);
        if (insereTime(&lista, nome) == 1)
        {
            do {
                scanf ("%[^\n]%*c", nome);
            }
            while (insereTime(&lista, nome) == 1);
        }
    }
    printf("--------------------------------------------------------\n");

    for(j=0;j<nTimes-1;j++) {
        atrodada(&lista);
    }
    insertionSortTAB(&lista, nTimes);
    printf("\n");
    imprimeTabela(lista);

    printf("\n");
    printf("--------------OPERAÇÕES DE BUSCA--------------\n");
    buscaSeqTime(lista, "Juventus");
    printf("\n");
    buscaSeqTime(lista, "Bayern Munchen");
    printf("\n");    
    buscaBinTime(lista, "Bayern Munchen");
    printf("\n");
    buscaBinTime(lista, "Vila");
    printf("\n");
    buscaSeqTime(lista, "Goias");
    printf("----------------------------------------------\n");
    printf("\n\n");

    printf("------------OPERAÇÕES DE ORDENAÇÃO------------\n");
    printf("ORDENAÇÃO POR GOLS FEITOS: \n");
    quickSortGF(&lista, 0, lista.tam-1); //usando quickSort (Primeiro método de ordenação)
    imprimeTabelaGF(lista);
    printf("\n\n");
    printf("ORDENAÇÃO POR GOLS SOFRIDOS: \n");
    insertionSortGS(&lista, lista.tam); //usando insertionSort(Segundo método de ordenação)
    imprimeTabelaGS(lista);
    printf("-----------------------------------------------\n");

    printf("\n");
    libera(&lista);

    return 0;
}
