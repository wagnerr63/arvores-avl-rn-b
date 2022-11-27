typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

void balanceamento(Arvore*, No*);
int altura(No*);
int fb(No*);
void visitar(int valor);
void percorrerProfundidadeInOrder(No* no, void (*callback)(int));
void percorrerProfundidadePreOrder(No* no, void (*callback)(int));
void percorrerProfundidadePosOrder(No* no, void (callback)(int));
No* rsd(Arvore*, No*);
No* rse(Arvore*, No*);
No* rdd(Arvore*, No*);
No* rde(Arvore*, No*);
No* adicionar(Arvore* arvore, int valor);
Arvore* criar();
int vazia(Arvore* arvore);