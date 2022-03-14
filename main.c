#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

int main() {
    Lista lista;
    char nome[30];
    int i;

    init(&lista);

    for(i=0;i<6;i++) {
        scanf("%[^\n]%*c", nome);
        insereTime(&lista, nome);
    }

    printf("\n");
    imprimeTabela(lista);

    printf("\n");
    libera(&lista);

    return 0;
}