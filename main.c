#include "tad.h"

int main() {
    Lista lista;
    char nome[30];
    int i; 

    init(&lista);

    printf ("O PROGRAMA ESTA SETADO PARA UM CAMPEONATO DE %d JOGOS\n", nTimes);

    for(i=0;i<6;i++) {
        scanf("%[^\n]%*c", nome);
        if (insereTime(&lista, nome) == 1)
        {
            while (insereTime(&lista, nome) == 1)
            scanf ("%[^\n]%*c", nome);
        }
    }


    printf("\n");
    imprimeTabela(lista);

    printf("\n");
    libera(&lista);

    return 0;
}