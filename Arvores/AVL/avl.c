#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int maior_elemento(No *raiz){
  if(raiz == NULL){
    return -1;
  }
  else{
    if(raiz->dir == NULL){
      return raiz->valor;
    }
    else{;
      return maior_elemento(raiz->dir);
    }
  }
}

void exibir_pre_order(No *raiz){
  if(raiz != NULL){
    printf("[%d,%d]",raiz->valor,raiz->fator_bal);
    exibir_pre_order(raiz->esq);
    exibir_pre_order(raiz->dir);
  }
}

No* rotacao_simples_direita(No *raiz){
  No *u = raiz->esq;
  raiz->esq = u->dir;
  u->dir = raiz;

  return u;
}

No* rotacao_simples_esquerda(No *raiz){
  No *u = raiz->dir;
  raiz->dir = u->esq;
  u->esq = raiz;

  return u;
}

No* rotacao_dupla_direita(No *raiz){
  No *u = raiz->esq;
  No *v = u->dir;

  if(v->fator_bal == 0){
    raiz->fator_bal = 0;
    u->fator_bal = 0;
    v->fator_bal = 0;
  }
  if(v->fator_bal == 1){
    raiz->fator_bal = 0;
    u->fator_bal = -1;
    v->fator_bal = 0;
  }
  if(v->fator_bal == -1){
    raiz->fator_bal = 1;
    u->fator_bal = 0;
    v->fator_bal = 0;
  }

  raiz->esq = rotacao_simples_esquerda(raiz->esq);
  raiz = rotacao_simples_direita(raiz);
  return raiz;
}

No* rotacao_dupla_esquerda(No *raiz){
  No *u = raiz->dir;
  No *v = u->esq;

  if(v->fator_bal == 0){
    raiz->fator_bal = 0;
    u->fator_bal = 0;
    v->fator_bal = 0;
  }
  if(v->fator_bal == 1){
    raiz->fator_bal = -1;
    u->fator_bal = 0;
    v->fator_bal = 0;
  }
  if(v->fator_bal == -1){
    raiz->fator_bal = 0;
    u->fator_bal = 1;
    v->fator_bal = 0;
  }

  raiz->dir = rotacao_simples_direita(raiz->dir);
  raiz = rotacao_simples_esquerda(raiz);
  return raiz;
}

No* rotacionar(No *raiz,No *filho){
  switch (raiz->fator_bal) {
    case 1:
      switch (filho->fator_bal) {
        case 1:
          raiz->fator_bal = 0;
          raiz->dir->fator_bal = 0;
          return rotacao_simples_esquerda(raiz);
        case -1:
          return rotacao_dupla_esquerda(raiz);
        case 0:
          raiz->fator_bal = 1;
          raiz->dir->fator_bal = -1;
          return rotacao_simples_esquerda(raiz);
      }
    case -1:
      switch (filho->fator_bal) {
        case 1:
          return rotacao_dupla_direita(raiz);
        case -1:
          raiz->fator_bal = 0;
          raiz->esq->fator_bal = 0;
          return rotacao_simples_direita(raiz);
        case 0:
          raiz->fator_bal = -1;
          raiz->esq->fator_bal = 1;
          return rotacao_simples_direita(raiz);
      }
  }
}

No* adicionar(No *raiz, int valor,int *cresceu){
  if(raiz == NULL){
    No *novo = (No*)malloc(sizeof(No));
    novo->fator_bal = 0;
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    *cresceu = 1;

    return novo;
  }
  else{
    if(valor > raiz->valor){
      raiz->dir = adicionar(raiz->dir,valor,cresceu);
      if(*cresceu){
        switch (raiz->fator_bal) {
          case 1:
            *cresceu = 0;
            return rotacionar(raiz,raiz->dir);
          case -1:
            raiz->fator_bal = 0;
            *cresceu = 0;
            break;
          case 0:
            raiz->fator_bal = 1;
            break;
        }
      }
    }
    else{
      raiz->esq = adicionar(raiz->esq,valor,cresceu);
      if(*cresceu){
        switch (raiz->fator_bal) {
          case 1:
            raiz->fator_bal = 0;
            *cresceu = 0;
            break;
          case -1:
            *cresceu = 0;
            raiz = rotacionar(raiz,raiz->esq);
            break;
          case 0:
            raiz->fator_bal = -1;
            break;
        }
      }
    }
    return raiz;
  }
}

No* remover(No *raiz,int valor,int *diminuiu){
  if(raiz == NULL){
    *diminuiu = 0;
  }
  else{
    if(raiz->valor == valor){
      if(raiz->esq == NULL){
        free(raiz);
        *diminuiu = 1;
        return raiz->dir;
      }
      if(raiz->dir == NULL){
        free(raiz);
        *diminuiu = 1;
        return raiz->esq;
      }
      else{
        raiz->valor = maior_elemento(raiz->esq);
        raiz->esq = remover(raiz->esq,raiz->valor,diminuiu);
        switch (raiz->fator_bal) {
          case 1:
            raiz = rotacionar(raiz,raiz->dir);
            break;
          case 0:
            raiz->fator_bal = 1;
            *diminuiu = 0;
            break;
          case -1:
            raiz->fator_bal = 0;
            break;
        }
      }
    }
    else{
      if(valor > raiz->valor){
        raiz->dir = remover(raiz->dir,valor,diminuiu);
        if(*diminuiu){
          switch (raiz->fator_bal) {
            case 1:
              raiz->fator_bal = 0;
              break;
            case 0:
              raiz->fator_bal = -1;
              *diminuiu = 0;
              break;
            case -1:
              raiz = rotacionar(raiz,raiz->esq);
              break;
          }
        }
      }
      else{
        raiz->esq = remover(raiz->esq,valor,diminuiu);
        if(*diminuiu){
          switch (raiz->fator_bal) {
            case 1:
              raiz = rotacionar(raiz,raiz->dir);
              break;
            case 0:
              raiz->fator_bal = 1;
              *diminuiu = 0;
              break;
            case -1:
              raiz->fator_bal = 0;
              break;
          }
        }
      }
      return raiz;
    }
    return raiz;
  }
  return raiz;
}
