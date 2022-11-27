#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

int main() {
    Arvore* a = criar();

    for (int i = 1; i <= 8; i++) {
        adicionar(a,i);  
    }

    printf("In-order: ");
    percorrerProfundidadeInOrder(a->raiz,visitar);
    printf("\n");
}