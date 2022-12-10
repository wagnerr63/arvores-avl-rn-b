
typedef struct no {
    int total;
    int* chaves;
    struct no** filhos;
    struct no* pai; 
} No;

typedef struct arvoreB {
  No* raiz;
  int ordem;
} ArvoreB;


ArvoreB* criaArvoreB(int);
No* bCriaNo(ArvoreB*);
void bPercorreArvore(No*);
int bPesquisaBinaria(No*, int);
int bLocalizaChave(ArvoreB*, int);
No* bLocalizaNo(ArvoreB*, int);
void bAdicionaChaveNo(No*, No*, int);
int bTransbordo(ArvoreB*,No*);
No* bDivideNo(ArvoreB*, No*);
void bAdicionaChaveRecursivo(ArvoreB*, No*, No*, int);
void bAdicionaChave(ArvoreB*, int);

int bFillWithRandomNumbers(ArvoreB* arvore, int quantity);
int bFillWithRandomNumbersASC(ArvoreB* arvore, int quantity);