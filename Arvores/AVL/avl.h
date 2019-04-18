#ifndef AVL_H
#define AVL_H

typedef struct noAVL{
  int valor;
  int fator_bal;
  struct noAVL *esq,*dir;
}No;

int maior_elemento(No *raiz);
void exibir_pre_order(No *raiz);
No* adicionar(No *raiz, int valor, int *cresceu);
No* remover(No *raiz,int valor,int *diminuiu);
No* rotacionar(No *raiz,No *filho);
No* rotacao_simples_direita(No *raiz);
No* rotacao_simples_esquerda(No *raiz);
No* rotacao_dupla_direita(No *raiz);
No* rotacao_dupla_esquerda(No *raiz);

#endif
