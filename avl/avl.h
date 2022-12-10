typedef struct AVLno {
    struct AVLno* pai;
    struct AVLno* esquerda;
    struct AVLno* direita;
    int valor;
} AVLNo;


typedef struct AVLarvore {
    struct AVLno* raiz;
} AVLArvore;

AVLArvore* AVLcriar();
AVLNo* AVLadicionar(AVLArvore* AVLarvore, int valor);
AVLNo* AVLadicionarNo(AVLNo* AVLno, int valor);
void AVLbalanceamento(AVLArvore*, AVLNo*);
int AVLaltura(AVLNo*);
void AVLremover(AVLArvore* AVLarvore, AVLNo* AVLno);
AVLNo* AVLlocalizar(AVLNo* AVLno, int valor);
void AVLpercorrerProfundidadeInOrder(AVLNo* AVLno, void (*callback)(int));
void AVLpercorrerProfundidadePreOrder(AVLNo* AVLno, void (*callback)(int));
void AVLpercorrerProfundidadePosOrder(AVLNo* AVLno, void (callback)(int));
int fb(AVLNo*);
AVLNo* rsd(AVLArvore*, AVLNo*);
AVLNo* rse(AVLArvore*, AVLNo*);
AVLNo* rdd(AVLArvore*, AVLNo*);
AVLNo* rde(AVLArvore*, AVLNo*);