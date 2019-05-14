#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

Cor cor(No *no){
  if(no == NULL){return PRETO;}
  else{
    return no->cor;
  }
}

Boolean e_raiz(No *no){
  if(no->pai == NULL){return TRUE;}
  else{return FALSE;}
}

Boolean e_filho_esq(No *no){
  if(no->pai == NULL){return FALSE;}
  if(no == no->pai->esq){return TRUE;}
  else{return FALSE;}
}

No* maior_elemento(No *raiz){
  if(raiz == NULL || raiz->dir == NULL){return raiz;}
  else{return maior_elemento(raiz->dir);}
}

No* tio(No *raiz){
  if(e_filho_esq(raiz->pai)){return raiz->pai->pai->dir;}
  else{return raiz->pai->pai->esq;}
}

No* criar_nulo(No *pai){
  No *nulo = (No*)malloc(sizeof(No));

  nulo->valor = -1;
  nulo->cor = DUPLO_PRETO;
  nulo->pai = pai;
  nulo->esq = NULL;
  nulo->dir = NULL;
  return nulo;
}

No* criar_no(int valor,No* pai){
  No *no = (No*)malloc(sizeof(No));
  no->valor = valor;
  no->cor = VERMELHO;
  no->pai = pai;
  no->esq = NULL;
  no->dir = NULL;
  return no;
}

No* irmao(No *no){
  if(e_filho_esq(no)){return no->pai->dir;}
  else{return no->pai->esq;}
}

void exibir_pre_order(No *raiz){
  if(raiz != NULL){
    if(cor(raiz) == PRETO){ printf("\33[0;30m[%d]\33[0m",raiz->valor);}
    else{ printf("\33[0;31m[%d]\33[0m",raiz->valor);}
    exibir_pre_order(raiz->esq);
    exibir_pre_order(raiz->dir);
  }
}

void ajustar(No *no,No **raiz){
  if(e_raiz(no)){
    no->cor = PRETO;
    return;
  }
  if(cor(no->pai) == VERMELHO){
    if(cor(tio(no)) == VERMELHO){
      no->pai->cor = PRETO;
      tio(no)->cor = PRETO;
      no->pai->pai->cor = VERMELHO;
      ajustar(no->pai->pai,raiz);
      return;
    }
    else{//tio do elemento é PRETO
      if(e_filho_esq(no) && e_filho_esq(no->pai)){
        no->pai->pai->cor = VERMELHO;
        no->pai->cor = PRETO;
        rotacao_simples_direita(no->pai->pai,raiz);
        return;
      }
      if(e_filho_esq(no) && !e_filho_esq(no->pai)){
        rotacao_dupla_esquerda(no->pai->pai,raiz);
        return;
      }
      if(!e_filho_esq(no) && !e_filho_esq(no->pai)){
        no->pai->pai->cor = VERMELHO;
        no->pai->cor = PRETO;
        rotacao_simples_esquerda(no->pai->pai,raiz);
        return;
      }
      if(!e_filho_esq(no) && e_filho_esq(no->pai)){
        rotacao_dupla_direita(no->pai->pai,raiz);
        return;
      }
    }
  }
}

void reajustar(No *nulo,No **raiz){
  if(e_raiz(nulo)){//caso 1
    if(cor(nulo)==DUPLO_PRETO){
      *raiz = NULL;
      free(nulo);
    }else{
      (*raiz)->cor = PRETO;
    }
    return;
  }//caso 2
  if(cor(nulo->pai) == PRETO && cor(irmao(nulo)) == VERMELHO){
    irmao(nulo)->cor = PRETO;
    nulo->pai->cor = VERMELHO;
    if(e_filho_esq(nulo)){ rotacao_simples_esquerda(nulo->pai,raiz);//Caso 2a
    }else{ rotacao_simples_direita(nulo->pai,raiz);}//Caso 2b
    reajustar(nulo,raiz);
    return;
  }//caso 3
  if(cor(nulo->pai)==PRETO && cor(irmao(nulo))==PRETO && cor(irmao(nulo)->esq)==PRETO && cor(irmao(nulo)->dir)==PRETO){
    irmao(nulo)->cor = VERMELHO;
    if(e_filho_esq(nulo)){nulo->pai->esq = NULL;}
    else{nulo->pai->dir = NULL;}
    reajustar(nulo->pai,raiz);
    free(nulo);
    return;
  }//caso 4
  if(cor(nulo->pai)==VERMELHO && cor(irmao(nulo))==PRETO&&cor(irmao(nulo)->esq)==PRETO &&cor(irmao(nulo)->dir)==PRETO){
    irmao(nulo)->cor = VERMELHO;
    nulo->pai->cor = PRETO;
    if(cor(nulo) == DUPLO_PRETO){
      if(e_filho_esq(nulo)){nulo->pai->esq = NULL;}//caso 4a
      else{nulo->pai->dir = NULL;}//caso 4b
      free(nulo);
    }else{
      nulo->cor = PRETO;
    }
    return;
  }//caso 5a
  if(e_filho_esq(nulo) && cor(irmao(nulo))==PRETO && cor(irmao(nulo)->esq)==VERMELHO && cor(irmao(nulo)->dir)==PRETO){
    irmao(nulo)->cor = VERMELHO;
    irmao(nulo)->esq->cor = PRETO;
    rotacao_simples_direita(irmao(nulo),raiz);
    reajustar(nulo,raiz);
    return;
  }//caso 5b
  if(!(e_filho_esq(nulo)) && cor(irmao(nulo))==PRETO &&cor(irmao(nulo)->dir)==VERMELHO&&cor(irmao(nulo)->esq)==PRETO){
    irmao(nulo)->cor = VERMELHO;
    irmao(nulo)->dir->cor = PRETO;
    rotacao_simples_esquerda(irmao(nulo),raiz);
    reajustar(nulo,raiz);
    return;
  }//caso 6a
  if(e_filho_esq(nulo) && cor(irmao(nulo)) == PRETO && cor(irmao(nulo)->dir) == VERMELHO && cor(irmao(nulo)->esq) == PRETO){
    irmao(nulo)->cor = nulo->pai->cor;
    irmao(nulo)->dir->cor = PRETO;
    nulo->pai->cor = PRETO;
    if(cor(nulo)==DUPLO_PRETO){
        nulo->pai->esq = NULL;
        free(nulo);
    }else{
      nulo->cor = PRETO;
    }
    rotacao_simples_esquerda(nulo->pai,raiz);
    return;
  }//caso 6b
  if(!(e_filho_esq(nulo)) && cor(irmao(nulo)) == PRETO && cor(irmao(nulo)->esq) == VERMELHO && cor(irmao(nulo)->dir) == PRETO){
    irmao(nulo)->cor = nulo->pai->cor;
    irmao(nulo)->esq->cor = PRETO;
    nulo->pai->cor = PRETO;
    if(cor(nulo)==DUPLO_PRETO){
        nulo->pai->dir = NULL;
        free(nulo);
    }else{
      nulo->cor = PRETO;
    }
    rotacao_simples_direita(nulo->pai,raiz);
    return;
  }
}

void rotacao_simples_direita(No *pivo,No **raiz){
  No *u = pivo->esq;
  pivo->esq = u->dir;

  if(pivo->esq != NULL){pivo->esq->pai = pivo;}

  u->pai = pivo->pai;
  if(e_raiz(u)){*raiz = u;}
  else{
    if(e_filho_esq(pivo)){u->pai->esq = u;}
    else{u->pai->dir = u;}
  }

  u->dir = pivo;
  pivo->pai = u;
}

void rotacao_simples_esquerda(No *pivo,No **raiz){
  No *u = pivo->dir;
  pivo->dir = u->esq;

  if(pivo->dir != NULL){pivo->dir->pai = pivo;}

  u->pai = pivo->pai;
  if(e_raiz(u)){*raiz = u;}
  else{
    if(e_filho_esq(pivo)){u->pai->esq = u;}
    else{u->pai->dir = u;}
  }

  u->esq = pivo;
  pivo->pai = u;
}

void rotacao_dupla_direita(No *pivo,No **raiz){
  pivo->cor = VERMELHO;
  pivo->esq->dir->cor = PRETO;
  rotacao_simples_esquerda(pivo->esq,raiz);
  rotacao_simples_direita(pivo,raiz);
}

void rotacao_dupla_esquerda(No *pivo,No **raiz){
  pivo->cor = VERMELHO;
  pivo->dir->esq->cor = PRETO;
  rotacao_simples_direita(pivo->dir,raiz);
  rotacao_simples_esquerda(pivo,raiz);
}

void adicionar(No **raiz, int valor){
  No *temp = *raiz;
  No *pai = NULL;

  while (temp != NULL) {
    pai = temp;
    if(valor > temp->valor){temp = temp->dir;}
    else{temp = temp->esq;}
  }

  No *novo = criar_no(valor,pai);

  if(*raiz != NULL){
    if(novo->valor > pai->valor){pai->dir = novo;}
    else{pai->esq = novo;}
  }
  else{*raiz = novo;}
  ajustar(novo,raiz);
}

void remover(No **raiz,int valor){
  No* temp = (*raiz);
  No* no = NULL;

  while (temp != NULL) {
    no = temp;
    if(no->valor == valor){break;}
    if(valor > temp->valor){temp = temp->dir;}
    else{temp = temp->esq;}
  }

  if(no == NULL){return;}//elemento nao existe

  if(no->dir != NULL && no->esq != NULL){//NO com 2 filhos
    no->valor = maior_elemento(no->esq)->valor;
    remover(&(no->esq),no->valor);
    return;
  }
  else if(no->dir != NULL && no->esq == NULL){//NO possui apenas filho direito
    if(e_raiz(no)){*raiz = no->dir;}
    else{
      if(e_filho_esq(no)){no->pai->esq = no->dir;}
      else{no->pai->dir = no->dir;}
    }
    no->dir->cor = no->cor;
    no->dir->pai = no->pai;
    free(no);
    return;
  }
  else if(no->esq != NULL && no->dir == NULL){//NO possui apenas filho esquerdo
    if(e_raiz(no)){*raiz = no->dir;}
    else{
      if(e_filho_esq(no)){no->pai->esq = no->esq;}
      else{no->pai->dir = no->esq;}
    }
    no->esq->pai = no->pai;
    no->esq->cor = no->cor;
    free(no);
    return;
  }
  else{//NO sem filhos
    if(cor(no) == VERMELHO){
      if(e_filho_esq(no)){no->pai->esq = NULL;}
      else{no->pai->dir = NULL;}
      }
    else{//NO PRETO sem filhos
      No *nulo = criar_nulo(no->pai);
      if(e_raiz(no)){*raiz = nulo;}
      else{
        if(e_filho_esq(no)){no->pai->esq = nulo;}
        else{no->pai->dir = nulo;}
      }
      reajustar(nulo,raiz);
    }
    free(no);
    return;
  }
}
