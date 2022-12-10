#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>
#include "rubronegra.h"

int RNcontador = 0; 

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