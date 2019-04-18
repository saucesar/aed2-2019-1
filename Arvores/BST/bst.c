;#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int altura(No *raiz){
  if(raiz == NULL){
    return 0;
  }else{
    return 1+maior(altura(raiz->esq),altura(raiz->dir));
  }
}

int maior(int a,int b){
  if(a > b){return a;}
  else {return b;}
}

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

int menor_elemento(No *raiz){
  if(raiz == NULL){
    return -1;
  }
  else{
    if(raiz->esq == NULL){
      return raiz->valor;
    }
    else{
      return menor_elemento(raiz->esq);
    }
  }
}

int buscar_pai(No *pai,No *raiz, int elemento){
  if(raiz == NULL){
    return -1;
  }
  if(raiz->valor == elemento){
    if(pai != NULL){
      return pai->valor;
    }else{
      return -1;
    }
  }
  else{
    if(elemento > raiz->valor){
      return buscar_pai(raiz,raiz->dir,elemento);
    }
    else{
      return buscar_pai(raiz,raiz->esq,elemento);
    }
  }
}

void copiar_em_ordem(No *raiz,No **aux){
  if(raiz != NULL){
    copiar_em_ordem(raiz->esq,aux);
    *aux = adicionar(*aux,raiz->valor);
    copiar_em_ordem(raiz->dir,aux);
  }
}

int sucessor(No *raiz,int elemento){
  No *aux = NULL;
  copiar_em_ordem(raiz,&aux);

  No *no = buscar(aux,elemento);

  if(no->dir != NULL){return no->dir->valor;}
  else{return -1;}
}

int antecessor(No *raiz,int elemento){
  No *aux = NULL;
  copiar_em_ordem(raiz,&aux);

  return buscar_pai(NULL,aux,elemento);
}

void exibir_pre_order(No *raiz){
  if(raiz != NULL){
    printf("[%d]",raiz->valor);
    exibir_pre_order(raiz->esq);
    exibir_pre_order(raiz->dir);
  }
}

void exibir_in_order(No *raiz){
  if(raiz != N  ULL){
    exibir_in_order(raiz->esq);
    printf("[%d]",raiz->valor);
    exibir_in_order(raiz->dir);
  }
}

void exibir_pos_order(No *raiz){
  if(raiz != NULL){
    exibir_pos_order(raiz->esq);
    exibir_pos_order(raiz->dir);
    printf("[%d]",raiz->valor);
  }
}

No* buscar(No* raiz,int valor){
  if(raiz == NULL || raiz->valor == valor){
    return raiz;
  }
  else{
    if(valor > raiz->valor){
      return buscar(raiz->dir,valor);
    }
    else{
      return buscar(raiz->esq,valor);
    }
  }
}

No* adicionar(No *raiz, int valor){
  if(raiz == NULL){
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
  }
  else{
    if(valor > raiz->valor){
      raiz->dir = adicionar(raiz->dir,valor);
    }
    else{
      raiz->esq = adicionar(raiz->esq,valor);
    }
    return raiz;
  }
}

No* remover(No *raiz,int valor){
  if(raiz == NULL){
    return raiz;
  }
  else{
    if(raiz->valor == valor){
      if(raiz->esq == NULL){
        free(raiz);
        return raiz->dir;
      }
      if(raiz->dir == NULL){
        free(raiz);
        return raiz->esq;
      }
      else{
        raiz->valor = maior_elemento(raiz->esq);
        raiz->esq = remover(raiz->esq,raiz->valor);
        return raiz;
      }
    }
    else{
      if(valor > raiz->valor){
        raiz->dir = remover(raiz->dir,valor);
      }
      else{
        raiz->esq = remover(raiz->esq,valor);
      }
      return raiz;
    }
  }
}
