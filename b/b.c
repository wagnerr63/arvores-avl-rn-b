#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "b.h"

ArvoreB* criaArvoreB(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = bCriaNo(a);

    return a;
}

int bContador = 0;

No* bCriaNo(ArvoreB* arvore) {
    int max = arvore->ordem * 2;
    No* no = malloc(sizeof(No));

    no->pai = NULL;
        
    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(No) * (max + 2));
    no->total = 0;

    for (int i = 0; i < max + 2; i++)
        no->filhos[i] = NULL;

    return no;
}

void bPercorreArvore(No* no) {
    if (no != NULL) {
        for (int i = 0; i < no->total; i++){
            bPercorreArvore(no->filhos[i]); //visita o filho a esquerda
            
            printf("%d ",no->chaves[i]);
        }

        bPercorreArvore(no->filhos[no->total]); //visita ultimo filho (direita)
    }
}

int bPesquisaBinaria(No* no, int chave) {
    int inicio = 0, fim = no->total - 1, meio;
    
    while (inicio <= fim) {	
        bContador++;
        
        meio = (inicio + fim) / 2;
        
        if (no->chaves[meio] == chave) {	
		    return meio; //encontrou	
        } else if (no->chaves[meio] > chave) {
                fim	= meio - 1;	
        } else {
            inicio = meio + 1;
        }
    }
    return inicio; //não encontrou	
}

int bLocalizaChave(ArvoreB* arvore, int chave) {	
    No *no = arvore->raiz;
    
    while (no != NULL) {
        int i = bPesquisaBinaria(no, chave);

        if (i < no->total && no->chaves[i] == chave) {
            return 1; //encontrou
        } else {
            no = no->filhos[i];
        }
    }

    return 0; //não encontrou	
}

No* bLocalizaNo(ArvoreB* arvore, int chave) {	
    No *no = arvore->raiz;
    
    while (no != NULL) {
        bContador++;

        int i = bPesquisaBinaria(no, chave);

        if (no->filhos[i] == NULL)
            return no; //encontrou nó
        else
            no = no->filhos[i];
    }

    return NULL; //não encontrou nenhum nó
}

void bbAdicionaChaveNo(No* no, No* novo, int chave) {
    int i = bPesquisaBinaria(no, chave);
    
    bContador++;

    for (int j = no->total - 1; j >= i; j--) {
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
    }
    
    no->chaves[i] = chave;
    no->filhos[i + 1] = novo;

    no->total++;
}

int bTransbordo(ArvoreB* arvore, No* no) {
    bContador++;
    
    return no->total > arvore->ordem * 2;
}

No* bDivideNo(ArvoreB* arvore, No* no) {
    int meio = no->total / 2;
    No* novo = bCriaNo(arvore);
    novo->pai = no->pai;

    bContador++;
    
    for (int i = meio + 1; i < no->total; i++) {
        novo->filhos[novo->total] = no->filhos[i];
        novo->chaves[novo->total] = no->chaves[i];
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
        
        novo->total++;
    }

    novo->filhos[novo->total] = no->filhos[no->total];
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;    
    no->total = meio;
    return novo;
}

void bAdicionaChaveRecursivo(ArvoreB* arvore, No* no, No* novo, int chave) {
    bContador++;
    
    bbAdicionaChaveNo(no, novo, chave);
    
    if (bTransbordo(arvore, no)) {
        int promovido = no->chaves[arvore->ordem]; 
        No* novo = bDivideNo(arvore, no);

        if (no->pai == NULL) {
            bContador++;
            
            No* pai = bCriaNo(arvore);            
            pai->filhos[0] = no;
            bbAdicionaChaveNo(pai, novo, promovido);
            
            no->pai = pai;
            novo->pai = pai;
            arvore->raiz = pai;
        } else
            bAdicionaChaveRecursivo(arvore, no->pai, novo, promovido);
    }
}

void bAdicionaChave(ArvoreB* arvore, int chave) {
    No* no = bLocalizaNo(arvore, chave);

    bAdicionaChaveRecursivo(arvore, no, NULL, chave);
}

int random_number(int range){
    int num;
    num = rand() % range;
    return num;
}

int findValueInArray(int array[], int size, int value) {
    for(int i=0; i<size; i++) {
        if (array[i]==value) {
            return 1; // found
        }
    }

    return 0; // not found
}

int bFillWithRandomNumbers(ArvoreB* arvore, int quantity) {
    int i = 0;
    int numbers[1024];
    for (int i=0; i<1024; i++) {
        numbers[i]=-1;
    }
    srand(time(NULL));

    while(i!=quantity) {
        int randNumber = random_number(quantity);
        
        if(findValueInArray(numbers, 1024, randNumber)==0) {
            numbers[i] = randNumber;
            bAdicionaChave(arvore, randNumber);
            i++;
        }
    }

    return 0;
}

int bFillWithRandomNumbersASC(ArvoreB* arvore, int quantity) {
    for(int i=0; i<quantity; i++) {
        bAdicionaChave(arvore, i);
    }
    return 0;
}

/*
int main() {

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
  

}
*/