#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "b/b.h"
#include "rubronegra/rubronegra.h"

int findValueInArray(int array[], int size, int value) {
    for(int i=0; i<size; i++) {
        if (array[i]==value) {
            return 1; // found
        }
    }

    return 0; // not found
}

void popula(int vetor[], int tamanho){
    int numero;
    int i = 0;
    while(i!=tamanho) {
        numero = rand() % 5000;
        if (findValueInArray(vetor, tamanho, numero)==0) {
            vetor[i]=numero;
            i++;
        } 
    }
}

int main() {
    extern int bContador;
    /*
     FILE *arquivo;
    arquivo = fopen("bMedioCaso.csv", "w");
    fprintf(arquivo, "%s", "tamanho,esforco;\n");

    int tamanho = 2;
    
    for (int i =0;i<10;i++) {
        ArvoreB* arvore = criaArvoreB(1);
        bFillWithRandomNumbers(arvore, tamanho);

        printf("\nNúmero de operações no MÉDIO CASO: %d\n", bContador);
        fprintf(arquivo, "%i,%i;\n", tamanho,bContador);
        bContador = 0;
        
        tamanho = tamanho*2;
    
        free(arvore);
    }


    bContador = 0;
    tamanho = 2;
    arquivo = fopen("bPiorCaso.csv", "w");
    fprintf(arquivo, "%s", "tamanho,esforco;\n");
    for (int j =0;j<10;j++) {
        ArvoreB* arvorePior = criaArvoreB(1);
        bFillWithRandomNumbersASC(arvorePior, tamanho);

        printf("\nNúmero de operações no PIOR CASO: %d\n", bContador);
        
        fprintf(arquivo, "%i,%i;\n", tamanho,bContador);


        bContador = 0;
        tamanho = tamanho*2;

        free(arvorePior);  
    }
    */

    extern int RNcontador;

    int v[1000]; 
    srand ( time(NULL) );  

    FILE *arquivomedio; 
    FILE *arquivopior; 

    arquivomedio = fopen("casomedio.csv", "w"); 
    if (arquivomedio==NULL){ 
        printf("Erro ao abrir arquivo Caso Medio\n"); 
    }

    arquivopior = fopen("piorcaso.csv", "w"); 
    if (arquivopior==NULL){ 
        printf("Erro ao abrir arquivo PiorCaso\n"); 
    } 

  
    fprintf(arquivomedio, "%s", "n;RN;AVL;B-1;B-5;B-10\n");
    fprintf(arquivopior, "%s", "n;RN;AVL;B-1;B-5;B-10\n");

     
    //Criação Loop 1000 registros
    for (int j = 1; j < 1000; j++){ 
        long int media_rn=0, media_avl=0, media_b1=0, media_b5=0, media_b10=0; 
        printf("Execucao: %d\n", j);
        //Arvore a com Caso Medio 
        for (int numero = 0; numero < 10; numero++) { 
            int v[j]; 
            popula(v,j);
            
            RNArvore* a = RNcriar(); 
            //AVLArvore* b = AVLcriar(); 

            for (int i = 0; i < j; i++){ 
                RNcontador=0;
                //printf("%d: %d\n",i, v[i]);
                RNadicionar(a, v[i]);
                media_rn+=RNcontador; 
  
                //AVLcontador=0; 
                //adicinarAVL=(b, v[i]); 
                //media_avl+=AVLcontador; 

            } 
            free(a);
            //free(v);
        } 

        fprintf(arquivomedio, "%d;%ld", j, media_rn/10); 
        //fprintf(arquivomedio, "%d;%ld", j, media_avl/10);
        fprintf(arquivomedio, "\n"); 


        //Arvore com Pior Caso
        /*
        for (size_t i = 0; i < count; i++){ 
            
        } 

        fprintf(arquivopior, "\n"); 

        //contador=0; 

        //Arvore b com pior caso 
        RNArvore* b = criar();  
        for (int i = 0; i < j; i++){ 
            adicionar(b, i); 
        } 

        fprintf(arquivo, "%i", contador); 
        fprintf(arquivo, "%s", ";\n"); 
        contador=0;  
        free(b);
        */


    } 
    fclose (arquivomedio);
    fclose (arquivopior);

  
}