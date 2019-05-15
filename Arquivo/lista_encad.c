#include <stdlib.h>
#include <stdio.h>
#include "lista_encad.h"

No* startNo(int valor,int refer,No* proximo){
  No *novo = malloc(sizeof(No));
  novo->valor = valor;
  novo->ref = refer;
  novo->prox = proximo;
  return novo;
}

Lista* startLista(){
  Lista *lista = malloc(sizeof(Lista));
  lista->primeiro = NULL;
  return lista;
}

void adic_no_inicio(Lista *lista, int refer,int valor){
  lista->primeiro = startNo(valor,refer,lista->primeiro);
}

void remover(Lista *lista, int valor){

  No *temp = lista->primeiro, *anterior = NULL;

  while (temp != NULL && temp->valor != valor) {
    anterior = temp;
    temp = temp->prox;
  }
  if(temp == NULL){ return;}
  if(anterior == NULL){ lista->primeiro = temp->prox;}
  else{ anterior->prox = temp->prox;}
  free(temp);
}
