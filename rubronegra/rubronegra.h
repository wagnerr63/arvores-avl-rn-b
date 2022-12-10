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

RNNo* criarRNNo(RNArvore*, RNNo*, int); 
void RNbalancear(RNArvore*, RNNo*); 
void rotacionarEsquerda(RNArvore*, RNNo*); 
void rotacionarDireita(RNArvore*, RNNo*); 

RNArvore* RNcriar(); 
int RNvazia(RNArvore*); 
RNNo* RNadicionar(RNArvore*, int); 
RNNo* RNlocalizar(RNArvore* RNarvore, int valor); 