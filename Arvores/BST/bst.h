#ifndef BST_H
#define BST_H

typedef struct noBST{
  int valor;
  struct noBST *esq;
  struct noBST *dir;
}No;

int altura(No *raiz);
int maior(int a,int b);
int maior_elemento(No *raiz);
int menor_elemento(No *raiz);
int buscar_pai(No *pai,No *raiz, int elemento);
int sucessor(No *raiz, int elemento);
int antecessor(No *raiz, int elemento);
void copiar_em_ordem(No *raiz,No **aux);
void exibir_pre_order(No *raiz);
void exibir_in_order(No *raiz);
void exibir_pos_order(No *raiz);
No* buscar(No* raiz,int valor);
No* adicionar(No *raiz, int valor);
No* remover(No *raiz,int valor);

#endif
