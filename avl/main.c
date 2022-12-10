#include <stdlib.h>
#include <stdio.h>

typedef struct AVLno {
    struct AVLno* pai;
    struct AVLno* esquerda;
    struct AVLno* direita;
    int valor;
} AVLNo;

typedef struct AVLarvore {
    struct AVLno* raiz;
} AVLArvore;

int AVLcontador = 0;
void AVLbalanceamento(AVLArvore*, AVLNo*);
int AVLaltura(AVLNo*);
int fb(AVLNo*);
AVLNo* rsd(AVLArvore*, AVLNo*);
AVLNo* rse(AVLArvore*, AVLNo*);
AVLNo* rdd(AVLArvore*, AVLNo*);
AVLNo* rde(AVLArvore*, AVLNo*);

AVLArvore* AVLcriar() {
    AVLArvore *AVLarvore = malloc(sizeof(AVLArvore));
    AVLarvore->raiz = NULL;

    return AVLarvore;
}

int AVLvazia(AVLArvore* AVLarvore) {
    return AVLarvore->raiz == NULL;
}

AVLNo* AVLadicionarNo(AVLNo* AVLno, int valor) {
    AVLcontador++;
    if (valor > AVLno->valor) {
        if (AVLno->direita == NULL) {
            printf("Adicionando %d\n",valor);
            AVLNo* AVLnovo = malloc(sizeof(AVLNo));
            AVLnovo->valor = valor;
            AVLnovo->pai = AVLno;
            AVLno->direita = AVLnovo;

            return AVLnovo;
        } else {
            return AVLadicionarNo(AVLno->direita, valor);
        }
    } else {
        if (AVLno->esquerda == NULL) {
            printf("Adicionando %d\n",valor);
            AVLNo* AVLnovo = malloc(sizeof(AVLNo));
            AVLnovo->valor = valor;
            AVLnovo->pai = AVLno;
            AVLno->esquerda = AVLnovo;
            return AVLnovo;
        } else {
            return AVLadicionarNo(AVLno->esquerda, valor);
        }
    }
}

AVLNo* AVLadicionar(AVLArvore* AVLarvore, int valor) {
    AVLcontador++;
    if (AVLarvore->raiz == NULL) {
        printf("Adicionando %d\n",valor);
        AVLNo* AVLnovo = malloc(sizeof(AVLNo));
        AVLnovo->valor = valor;
        AVLarvore->raiz = AVLnovo;
        return AVLnovo;
    } else {
        AVLNo* AVLno = AVLadicionarNo(AVLarvore->raiz, valor);
        AVLbalanceamento(AVLarvore, AVLno);
        return AVLno;
    }
}

void AVLremover(AVLArvore* AVLarvore, AVLNo* AVLno) {
    if (AVLno->esquerda != NULL) {
        AVLremover(AVLarvore, AVLno->esquerda);
    }

    if (AVLno->direita != NULL) {
        AVLremover(AVLarvore, AVLno->direita);
    }

    if (AVLno->pai == NULL) {
        AVLarvore->raiz = NULL;
    } else {
        if (AVLno->pai->esquerda == AVLno) {
            AVLno->pai->esquerda = NULL;
        } else {
            AVLno->pai->direita = NULL;
        }
    }
    free(AVLno);
}

AVLNo* AVLlocalizar(AVLNo* AVLno, int valor) {
    if (AVLno->valor == valor) {
        return AVLno;
    } else {
        if (valor < AVLno->valor) {
            if (AVLno->esquerda != NULL) {
                return AVLlocalizar(AVLno->esquerda, valor);
            }
        } else {
            if (AVLno->direita != NULL) {
                return AVLlocalizar(AVLno->direita, valor);
            }
        }
    }
    return NULL;
}

void AVLpercorrerProfundidadeInOrder(AVLNo* AVLno, void (*callback)(int)) {
    if (AVLno != NULL) {
        AVLpercorrerProfundidadeInOrder(AVLno->esquerda,callback);
        callback(AVLno->valor);
        AVLpercorrerProfundidadeInOrder(AVLno->direita,callback);
    }
}

void AVLpercorrerProfundidadePreOrder(AVLNo* AVLno, void (*callback)(int)) {
    if (AVLno != NULL) {
        callback(AVLno->valor);
        AVLpercorrerProfundidadePreOrder(AVLno->esquerda,callback);
        AVLpercorrerProfundidadePreOrder(AVLno->direita,callback);
    }
}

void AVLpercorrerProfundidadePosOrder(AVLNo* AVLno, void (callback)(int)) {
    if (AVLno != NULL) {
        AVLpercorrerProfundidadePosOrder(AVLno->esquerda,callback);
        AVLpercorrerProfundidadePosOrder(AVLno->direita,callback);
        callback(AVLno->valor);
    }
}

void AVLvisitar(int valor){
    printf("%d ", valor);
}

void AVLbalanceamento(AVLArvore* AVLarvore, AVLNo* AVLno) {
    while (AVLno != NULL) {
        int fator = fb(AVLno);

        if (fator > 1) { //árvore mais pesada para esquerda
            //rotação para a direita
            if (fb(AVLno->esquerda) > 0) {
                printf("RSD(%d)\n",AVLno->valor);
                rsd(AVLarvore, AVLno); //rotação simples a direita, pois o FB do filho tem sinal igual
            } else {
                printf("RDD(%d)\n",AVLno->valor);
                rdd(AVLarvore, AVLno); //rotação dupla a direita, pois o FB do filho tem sinal diferente
            }

        } else if (fator < -1) { //árvore mais pesada para a direita
            //rotação para a esquerda
            if (fb(AVLno->direita) < 0) {
                printf("RSE(%d)\n",AVLno->valor);
                rse(AVLarvore, AVLno); //rotação simples a esquerda, pois o FB do filho tem sinal igual
            } else {
                printf("RDE(%d)\n",AVLno->valor);
                rde(AVLarvore, AVLno); //rotação dupla a esquerda, pois o FB do filho tem sinal diferente
            }
        }
        AVLno = AVLno->pai;
    }
}

int AVLaltura(AVLNo* AVLno){
    int esquerda = 0,direita = 0;

    if (AVLno->esquerda != NULL) {
        esquerda = AVLaltura(AVLno->esquerda) + 1;
    }

    if (AVLno->direita != NULL) {
        direita = AVLaltura(AVLno->direita) + 1;
    }

    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

int fb(AVLNo* AVLno) {
    AVLcontador++;
    int esquerda = 0,direita = 0;

    if (AVLno->esquerda != NULL) {
        esquerda = AVLaltura(AVLno->esquerda) + 1;
    }

    if (AVLno->direita != NULL) {
        direita = AVLaltura(AVLno->direita) + 1;
    }

    return esquerda - direita;
}

AVLNo* rse(AVLArvore* AVLarvore, AVLNo* AVLno) {
    AVLcontador++;
    AVLNo* pai = AVLno->pai;
    AVLNo* direita = AVLno->direita;
    AVLno->direita = direita->esquerda;
    AVLno->pai = direita;
    direita->esquerda = AVLno;
    direita->pai = pai;

    if (pai == NULL) {
        AVLarvore->raiz = direita;
    } else {
        if (pai->esquerda == AVLno) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

AVLNo* rsd(AVLArvore* AVLarvore, AVLNo* AVLno) {
    AVLcontador++;
    AVLNo* pai = AVLno->pai;
    AVLNo* esquerda = AVLno->esquerda;

    AVLno->esquerda = esquerda->direita;
    AVLno->pai = esquerda;

    esquerda->direita = AVLno;
    esquerda->pai = pai;

    if (pai == NULL) {
        AVLarvore->raiz = esquerda;
    } else {
        if (pai->esquerda == AVLno) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

AVLNo* rde(AVLArvore* AVLarvore, AVLNo* AVLno) {
    AVLno->direita = rsd(AVLarvore, AVLno->direita);
    return rse(AVLarvore, AVLno);
}

AVLNo* rdd(AVLArvore* AVLarvore, AVLNo* AVLno) {
    AVLno->esquerda = rse(AVLarvore, AVLno->esquerda);
    return rsd(AVLarvore, AVLno);
}

int main() {

    AVLArvore* a = AVLcriar();

    for (int i = 1; i <= 7; i++) {
        AVLadicionar(a,i);
    }

    printf("\n");
    printf("Contador: %i\n", AVLcontador);
    AVLcontador=0;

    AVLArvore* b = AVLcriar();

    AVLadicionar(b,4);
    AVLadicionar(b,2);
    AVLadicionar(b,6);
    AVLadicionar(b,1);
    AVLadicionar(b,3);
    AVLadicionar(b,7);

    printf("Contador: %i\n", AVLcontador);
    printf("\n");
    AVLcontador=0;

}
