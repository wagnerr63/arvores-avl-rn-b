#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>
  

enum coloracao { Vermelho, Preto }; 
typedef enum coloracao Cor; 

  

typedef struct RNno { 
    struct RNno* pai; 
    struct RNno* esquerda; 
    struct RNno* direita; 
    Cor cor; 
    int valor; 
} RNNo; 

typedef struct RNarvore { 
    struct RNno* raiz; 
    struct RNno* nulo;  
} RNArvore; 

  

int RNcontador = 0; 
RNNo* criarRNNo(RNArvore*, RNNo*, int); 
void RNbalancear(RNArvore*, RNNo*); 
void rotacionarEsquerda(RNArvore*, RNNo*); 
void rotacionarDireita(RNArvore*, RNNo*); 

RNArvore* RNcriar(); 
int RNvazia(RNArvore*); 
RNNo* RNadicionar(RNArvore*, int); 
RNNo* RNlocalizar(RNArvore* RNarvore, int valor); 

RNArvore* RNcriar() { 
    RNArvore *RNarvore = malloc(sizeof(RNArvore)); 
    RNarvore->nulo = NULL; 
    RNarvore->raiz = NULL;

    RNarvore->nulo = criarRNNo(RNarvore, NULL, 0); 
    RNarvore->nulo->cor = Preto; 

    return RNarvore; 
} 

int RNvazia(RNArvore* RNarvore) { 
    return RNarvore->raiz == NULL; 
} 

RNNo* criarRNNo(RNArvore* RNarvore, RNNo* pai, int valor) { 
    RNNo* RNno = malloc(sizeof(RNNo)); 

    RNno->pai = pai;     
    RNno->valor = valor; 
    RNno->direita = RNarvore->nulo; 
    RNno->esquerda = RNarvore->nulo; 
    return RNno; 
} 

RNNo* adicionarRNNo(RNArvore* RNarvore, RNNo* RNno, int valor) { 
    RNcontador++; 
    if (valor > RNno->valor) { 
        if (RNno->direita == RNarvore->nulo) { 
            RNno->direita = criarRNNo(RNarvore, RNno, valor);      
            RNno->direita->cor = Vermelho;        
            return RNno->direita; 

        } else { 
            return adicionarRNNo(RNarvore, RNno->direita, valor); 
        } 

    } else { 
        if (RNno->esquerda == RNarvore->nulo) { 
            RNno->esquerda = criarRNNo(RNarvore, RNno, valor); 
            RNno->esquerda->cor = Vermelho; 
            return RNno->esquerda; 

        } else { 
            return adicionarRNNo(RNarvore, RNno->esquerda, valor); 
        } 
    } 
} 
  
RNNo* RNadicionar(RNArvore* RNarvore, int valor) { 
    RNcontador++; 
    if (RNvazia(RNarvore)) { 
        RNarvore->raiz = criarRNNo(RNarvore, RNarvore->nulo, valor); 
        RNarvore->raiz->cor = Preto; 
         
        return RNarvore->raiz; 
    } else { 
        RNNo* RNno = adicionarRNNo(RNarvore, RNarvore->raiz, valor); 
        RNbalancear(RNarvore, RNno); 

        return RNno; 
    } 
} 

RNNo* RNlocalizar(RNArvore* RNarvore, int valor) { 
    if (!RNvazia(RNarvore)) { 
        RNNo* RNno = RNarvore->raiz; 
        while (RNno != RNarvore->nulo) { 
            if (RNno->valor == valor) { 
                return RNno; 
            } else { 
                RNno = valor < RNno->valor ? RNno->esquerda : RNno->direita; 
            } 
        } 
    } 
    return NULL; 
} 
  
void RNpercorrerProfundidadeIRNnOrder(RNArvore* RNarvore, RNNo* RNno, void (*callback)(int)) { 
    if (RNno != RNarvore->nulo) { 
        RNpercorrerProfundidadeIRNnOrder(RNarvore, RNno->esquerda,callback); 
        callback(RNno->valor); 
        RNpercorrerProfundidadeIRNnOrder(RNarvore, RNno->direita,callback); 
    } 
} 

void RNpercorrerProfundidadePreOrder(RNArvore* RNarvore, RNNo* RNno, void (*callback)(int)) { 
    if (RNno != RNarvore->nulo) { 
        callback(RNno->valor); 
        RNpercorrerProfundidadePreOrder(RNarvore, RNno->esquerda,callback); 
        RNpercorrerProfundidadePreOrder(RNarvore, RNno->direita,callback); 
    } 
} 

void RNpercorrerProfundidadePosOrder(RNArvore* RNarvore, RNNo* RNno, void (callback)(int)) { 
    if (RNno != RNarvore->nulo) { 
        RNpercorrerProfundidadePosOrder(RNarvore, RNno->esquerda,callback); 
        RNpercorrerProfundidadePosOrder(RNarvore, RNno->direita,callback); 
        callback(RNno->valor); 
    } 
} 

void visitar(int valor){ 
    printf("%d ", valor); 
} 

void RNbalancear(RNArvore* RNarvore, RNNo* RNno) { 
    while (RNno->pai->cor == Vermelho) { 
        RNcontador++; 
        if (RNno->pai == RNno->pai->pai->esquerda) { 
            RNNo *tio = RNno->pai->pai->direita; 

            if (tio->cor == Vermelho) { 
                RNcontador++; 
                tio->cor = Preto; //Caso 1 
                RNno->pai->cor = Preto;  
                RNno->pai->pai->cor = Vermelho; //Caso 1 
                RNno = RNno->pai->pai; //Caso 1 

            } else { 
                if (RNno == RNno->pai->direita) { 
                    RNcontador++; 
                    RNno = RNno->pai; //Caso 2 
                    rotacionarEsquerda(RNarvore, RNno); //Caso 2 
                } else { 
                    RNcontador++; 
                    RNno->pai->cor = Preto;  
                    RNno->pai->pai->cor = Vermelho; //Caso 3 
                    rotacionarDireita(RNarvore, RNno->pai->pai); //Caso 3 
                } 
            } 
        } else { 
            RNNo *tio = RNno->pai->pai->esquerda; 
            if (tio->cor == Vermelho) { 
                RNcontador++; 
                tio->cor = Preto; //Caso 1 
                RNno->pai->cor = Preto;  
                RNno->pai->pai->cor = Vermelho; //Caso 1 
                RNno = RNno->pai->pai; //Caso 1 
            } else { 
                if (RNno == RNno->pai->esquerda) { 
                    RNcontador++; 
                    RNno = RNno->pai; //Caso 2 
                    rotacionarDireita(RNarvore, RNno); //Caso 2 
                } else { 
                    RNcontador++; 
                    RNno->pai->cor = Preto;  
                    RNno->pai->pai->cor = Vermelho; //Caso 3 
                    rotacionarEsquerda(RNarvore, RNno->pai->pai); //Caso 3 
                } 
            } 
        } 
    } 
    RNarvore->raiz->cor = Preto; //Conserta possível quebra regra 2 
} 

void rotacionarEsquerda(RNArvore* RNarvore, RNNo* RNno) { 
    RNcontador++; 
    RNNo* direita = RNno->direita; 
    RNno->direita = direita->esquerda;  
    if (direita->esquerda != RNarvore->nulo) { 
        direita->esquerda->pai = RNno; 
    }
    direita->pai = RNno->pai; 
    if (RNno->pai == RNarvore->nulo) { 
        RNarvore->raiz = direita; 
    } else if (RNno == RNno->pai->esquerda) { 
        RNno->pai->esquerda = direita; 
    } else { 
        RNno->pai->direita = direita; 
    } 
    direita->esquerda = RNno; 
    RNno->pai = direita; 
} 

void rotacionarDireita(RNArvore* RNarvore, RNNo* RNno) { 
    RNcontador++; 
    RNNo* esquerda = RNno->esquerda; 
    RNno->esquerda = esquerda->direita; 
    if (esquerda->direita != RNarvore->nulo) { 
        esquerda->direita->pai = RNno; 
    } 
    esquerda->pai = RNno->pai; 

    if (RNno->pai == RNarvore->nulo) { 
        RNarvore->raiz = esquerda; 
    } else if (RNno == RNno->pai->esquerda) { 
        RNno->pai->esquerda = esquerda; 
    } else { 
        RNno->pai->direita = esquerda; 
    } 
    esquerda->direita = RNno; 
    RNno->pai = esquerda; 
} 

void popula(int vetor[], int tamanho){
    int numero;
    for (int i = 0; i <= tamanho; i++){ 
        numero = rand() % 5000; 
        for (int j = 0; j < i+1; j++){ 
            if (numero == vetor[j]){ 
                numero=-1;
                printf("Preso\n");
            }
        }
        if (numero==-1){
            i--;
        }else{
            vetor[i]=numero;
        }
    }
}

int main() { 

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
                printf("%d: %d\n",i, v[i]);
                RNadicionar(a, v[i]);
                media_rn+=RNcontador; 
  
                //AVLcontador=0; 
                //adicinarAVL=(b, v[i]); 
                //media_avl+=AVLcontador; 

            } 
            free(a);
            free(v);
        } 

        fprintf(arquivomedio, "%d;%d", j, media_rn/10); 
        //fprintf(arquivomedio, "%d;%d", j, media_avl/10);
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