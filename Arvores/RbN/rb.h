#ifndef Rb_N
#define Rb_N

typedef enum cor{VERMELHO,PRETO,DUPLO_PRETO} Cor;
typedef enum boolean{FALSE,TRUE} Boolean;

typedef struct noRbN{
  int valor;
  Cor cor;
  struct noRbN *esq,*dir,*pai;
}No;

Cor cor(No *no);

Boolean e_raiz(No *no);
Boolean e_filho_esq(No *no);

No* maior_elemento(No *raiz);
No* criar_nulo(No *pai);
No* criar_no(int valor,No* pai);
No* irmao(No *no);

void exibir_pre_order(No *raiz);
void ajustar(No *no,No **raiz);
void reajustar(No *no,No **raiz);
void adicionar(No **raiz, int valor);
void remover(No **raiz,int valor);
void rotacao_simples_direita(No *pivo,No **raiz);
void rotacao_simples_esquerda(No *pivo,No **raiz);
void rotacao_dupla_direita(No *pivo,No **raiz);
void rotacao_dupla_esquerda(No *pivo,No **raiz);

#endif
