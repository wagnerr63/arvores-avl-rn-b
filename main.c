#include <stdlib.h>
#include <stdio.h>
#include "b/b.h"


int main() {
    extern int contador;
    FILE *arquivo;
    arquivo = fopen("bMedioCaso.csv", "w");
    fprintf(arquivo, "%s", "tamanho,esforco;\n");

    int tamanho = 2;
    
    for (int i =0;i<10;i++) {
        ArvoreB* arvore = criaArvoreB(1);
        bFillWithRandomNumbers(arvore, tamanho);

        printf("\nNúmero de operações no MÉDIO CASO: %d\n", contador);
        fprintf(arquivo, "%i,%i;\n", tamanho,contador);
        contador = 0;
        
        tamanho = tamanho*2;
    
        free(arvore);
    }


    contador = 0;
    tamanho = 2;
    arquivo = fopen("bPiorCaso.csv", "w");
    fprintf(arquivo, "%s", "tamanho,esforco;\n");
    for (int j =0;j<10;j++) {
        ArvoreB* arvorePior = criaArvoreB(1);
        bFillWithRandomNumbersASC(arvorePior, tamanho);

        printf("\nNúmero de operações no PIOR CASO: %d\n", contador);
        
        fprintf(arquivo, "%i,%i;\n", tamanho,contador);


        contador = 0;
        tamanho = tamanho*2;

        free(arvorePior);  
    }
  
}