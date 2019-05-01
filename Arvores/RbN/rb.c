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

No* menor_elemento(No *raiz){
  if(raiz == NULL || raiz->esq == NULL){return raiz;}
  else{return menor_elemento(raiz->esq);}
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
    }else{
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
    *raiz = NULL;
    free(nulo);
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
    reajustar(nulo,raiz);
    return;
  }//caso 4
  if(cor(nulo->pai)==VERMELHO && cor(irmao(nulo))==PRETO&&cor(irmao(nulo)->esq)==PRETO &&cor(irmao(nulo)->dir)==PRETO){
    irmao(nulo)->cor = VERMELHO;
    nulo->pai->cor = PRETO;
    if(e_filho_esq(nulo)){nulo->pai->esq = NULL;}//caso 4a
    else{nulo->pai->dir = NULL;}//caso 4b
    free(nulo);
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
  if(e_filho_esq(nulo) && cor(irmao(nulo)) == PRETO && cor(irmao(nulo)->dir) == VERMELHO){
    irmao(nulo)->cor = nulo->pai->cor;
    irmao(nulo)->dir->cor = PRETO;
    nulo->pai->cor = PRETO;
    nulo->pai->esq = NULL;
    rotacao_simples_esquerda(nulo->pai,raiz);
    free(nulo);
    return;
  }//caso 6b
  if(!(e_filho_esq(nulo)) && cor(irmao(nulo)) == PRETO && cor(irmao(nulo)->esq) == VERMELHO){
    irmao(nulo)->cor = nulo->pai->cor;
    irmao(nulo)->esq->cor = PRETO;
    nulo->pai->cor = PRETO;
    nulo->pai->dir = NULL;
    rotacao_simples_direita(nulo->pai,raiz);
    free(nulo);
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

No* criar_no(int valor,No* pai){
  No *no = (No*)malloc(sizeof(No));
  no->valor = valor;
  no->cor = VERMELHO;
  no->pai = pai;
  no->esq = NULL;
  no->dir = NULL;
  return no;
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
  if(cor(no) == VERMELHO){
    if(e_filho_esq(no)){
      if(no->dir != NULL && no->esq != NULL){//No VERMELHO com 2 filhos
        no->valor = maior_elemento(no->esq)->valor;
        remover(&(no->esq),no->valor);
        return;
      }
      if(no->dir != NULL){//NO VERMELHO possui apenas filho direito
        no->pai->esq = no->dir;
        no->dir->pai = no->pai;
        no->dir->cor = no->cor;
        free(no);
        return;
      }
      else{//NO VERMELHO possui apenas filho esquerdo ou nenhum
        no->pai->esq = no->esq;
        if(no->esq != NULL){
          no->esq->pai = no->pai;
          no->esq->cor = no->cor;
        }
        free(no);
        return;
      }
    }
    else{//Nó VERMELHO e filho direito
      if(no->dir != NULL && no->esq != NULL){//No VERMELHO com 2 filhos
        no->valor = maior_elemento(no->esq)->valor;
        remover(&(no->esq),no->valor);
        return;
      }
      if(no->dir != NULL){//NO VERMELHO possui apenas filho direito
        no->pai->dir = no->dir;
        no->dir->pai = no->pai;
        no->dir->cor = no->cor;
        free(no);
        return;
      }
      else{//NO VERMELHO possui apenas filho esquerdo ou nenhum
        no->pai->dir = no->esq;
        if(no->esq != NULL){
          no->esq->pai = no->pai;
          no->esq->cor = no->cor;
        }
        free(no);
        return;
      }
    }
  }
  else{//No a ser removido é PRETO
    if(e_raiz(no)){//para evitar erro de segmentacao quando for atualisar os ponteiros esq e dir do pai do elemento
      if(no->esq != NULL && no->dir != NULL){//NO possui 2 filhos
          no->valor = maior_elemento(no->esq)->valor;
          remover(&(no->esq),no->valor);
          return;
      }
      if(no->dir != NULL){//NO possui apenas filho direito
        *raiz = no->dir;
        no->dir->pai = no->pai;
        no->dir->cor = PRETO;
        free(no);
        return;
      }
      if(no->esq != NULL){//NO possui apenas filho esquerdo
        *raiz = no->esq;
        no->esq->pai = no->pai;
        no->esq->cor = PRETO;
      }
      else{//NO preto sem filhos
        *raiz = criar_nulo(no->pai);
        reajustar(*raiz,raiz);
      }
      free(no);
      return;
    }
    if(e_filho_esq(no)){//Não é raiz e é preto
      if(no->dir != NULL && no->esq != NULL){//No possui 2 filhos
        no->valor = maior_elemento(no->esq)->valor;
        remover(&(no->esq),no->valor);
        return;
      }
      if(no->esq != NULL){//NO possui apenas filho esquerdo
        no->pai->esq = no->esq;
        no->esq->cor = no->cor;
        no->esq->pai = no->pai;
        free(no);
        return;
      }
      if(no->dir != NULL){//NO possui apenas filho direito
        no->pai->esq = no->dir;
        no->dir->cor = no->cor;
        no->esq->pai = no->pai;
        free(no);
        return;
      }
      else{//NO nao possui filhos
        No *nulo = criar_nulo(no->pai);
        no->pai->esq = nulo;
        reajustar(nulo,raiz);
        return;
      }
    }
    else{//Nó PRETO e direito
      if(no->dir != NULL && no->esq != NULL){//No possui 2 filhos
        no->valor = maior_elemento(no->esq)->valor;
        remover(&(no->esq),no->valor);
        return;
      }
      if(no->esq != NULL){//NO possui apenas filho esquerdo
        no->pai->dir = no->esq;
        no->esq->cor = no->cor;
        no->esq->pai = no->pai;
        free(no);
        return;
      }
      if(no->dir != NULL){//NO possui apenas filho direito
        no->pai->dir = no->dir;
        no->dir->cor = no->cor;
        no->dir->pai = no->pai;
        free(no);
        return;
      }
      else{
        //NO nao possui filhos
          No *nulo = criar_nulo(no->pai);
          no->pai->dir = nulo;
          reajustar(nulo,raiz);
          return;
      }
    }
  }
}
