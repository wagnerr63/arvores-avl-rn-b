#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "b/b.h"
#include "rubronegra/rubronegra.h"
#include "avl/avl.h"

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
    extern long int RNcontador;
    extern int bContador;
    extern long int AVLcontador;

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
            ArvoreB* arvoreB = criaArvoreB(1);
            ArvoreB* arvoreBOrdem5 = criaArvoreB(5);
            ArvoreB* arvoreBOrdem10 = criaArvoreB(10);
            AVLArvore* arvoreAVL = AVLcriar(); 

            for (int i = 0; i < j; i++){ 
                RNcontador=0;
                bContador=0;

                RNadicionar(a, v[i]);
                media_rn+=RNcontador; 

                bAdicionaChave(arvoreB, v[i]);
                media_b1+=bContador;
                bContador=0;
                bAdicionaChave(arvoreBOrdem5, v[i]);
                media_b5+=bContador;
                bContador=0;
                bAdicionaChave(arvoreBOrdem10, v[i]);
                media_b10+=bContador;
  
                AVLcontador=0; 
                AVLadicionar(arvoreAVL, v[i]); 
                media_avl+=AVLcontador; 

            } 
            free(a);
            free(arvoreB);
            free(arvoreBOrdem5);
            free(arvoreBOrdem10);
            free(arvoreAVL);
            //free(v);
        } 

        fprintf(arquivomedio, "%d;%ld;", j, media_rn/10); 
        fprintf(arquivomedio, "%ld;", media_avl/10);
        fprintf(arquivomedio, "%ld;", media_b1/10); 
        fprintf(arquivomedio, "%ld;", media_b5/10); 
        fprintf(arquivomedio, "%ld", media_b10/10); 
        fprintf(arquivomedio, "\n"); 


        //Arvore com Pior Caso
        RNArvore* rnPior = RNcriar(); 
        ArvoreB* arvoreBPior = criaArvoreB(1);
        ArvoreB* arvoreBOrdem5Pior = criaArvoreB(5);
        ArvoreB* arvoreBOrdem10Pior = criaArvoreB(10);
        AVLArvore* arvoreAVLPior = AVLcriar();
        long int bContador1 = 0, bContador5 = 0, bContador10 = 0, contadorRN = 0, avlContador = 0;
        for (int i = 1; i <= j; i++){ 

            RNcontador=0;
            bContador=0;
            AVLcontador=0;
            //printf("%d: %d\n",i, v[i]);
            RNadicionar(rnPior, i);
            contadorRN+=RNcontador;
            bAdicionaChave(arvoreBPior, i);
            bContador1+=bContador;
            bContador=0;
            bAdicionaChave(arvoreBOrdem5Pior, i);
            bContador5+=bContador;
            bContador=0;
            bAdicionaChave(arvoreBOrdem10Pior, i);
            bContador10+=bContador;
            AVLadicionar(arvoreAVLPior, i);
            avlContador+=AVLcontador;
            

        }
        free(rnPior);
        free(arvoreBPior);
        free(arvoreBOrdem5Pior);
        free(arvoreBOrdem10Pior); 
        free(arvoreAVLPior); 

        fprintf(arquivopior, "%d;%ld;", j, contadorRN);
        fprintf(arquivopior, "%ld;", avlContador);
        fprintf(arquivopior, "%ld;", bContador1); 
        fprintf(arquivopior, "%ld;", bContador5); 
        fprintf(arquivopior, "%ld", bContador10); 
        fprintf(arquivopior, "\n"); 

    } 
    fclose (arquivomedio);
    fclose (arquivopior);
    printf("FIM");
  
}