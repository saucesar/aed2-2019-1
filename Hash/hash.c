#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

int hash(int chave){
  return chave % MAX;
}

Tabela* startTabela(char *dados,char *indices){
  Tabela *tab = (Tabela*)malloc(sizeof(Tabela));

  tab->arquivo_dados = "dados.data";
  tab->arquivo_indices = "indices.data";
  tab->dados = fopen(tab->arquivo_dados,"a");
  tab->indices = fopen(tab->arquivo_indices,"r+b");

  for(int i = 0;i<MAX;i++){ tab->lista_indices[i] = startLista();}

  int chave,ref;
  while (fread(&chave,sizeof(int),1,tab->indices) && fread(&ref,sizeof(int),1,tab->indices)){
    adic_no_inicio(tab->lista_indices[hash(chave)], chave, ref);
  }
  fclose(tab->indices);
  return tab;
}

int buscar_indice(Tabela *tab, int chave){
  No *no = buscar_na_lista(tab->lista_indices[hash(chave)],chave);
  if(no != NULL){return no->ref;}
  else{ return -1;}
}

No* buscar_na_lista(Lista *lista,int chave){
  No* temp = lista->primeiro;
  while (temp != NULL && temp->chave != chave) {
    temp = temp->prox;
  }
  return temp;
}

void finalizar (Tabela *tab) {
	fclose(tab->dados);
	salvar_indices(tab);
  exit(0);
}

void salvar_indices(Tabela *tab){
  tab->indices = fopen(tab->arquivo_indices,"w+b");
  for(int i = 0;i<MAX;i++){
    Lista* lista = tab->lista_indices[i];
    No *temp = lista->primeiro;
    while (temp != NULL) {
      fwrite(temp,(2*sizeof(int)),1,tab->indices);
      free(temp);
    }
    free(lista);
  }
  fclose(tab->indices);
}

No* startNo(int chave, int refer, No* proximo){
  No *novo = malloc(sizeof(No));
  novo->chave = chave;
  novo->ref = refer;
  novo->prox = proximo;
  return novo;
}

Lista* startLista(){
  Lista *lista = malloc(sizeof(Lista));
  lista->primeiro = NULL;
  return lista;
}

void adic_no_inicio(Lista *lista, int chave, int refer){
  lista->primeiro = startNo(chave,refer,lista->primeiro);
}

void remover(Lista *lista, int chave){

  No *temp = lista->primeiro, *anterior = NULL;

  while (temp != NULL && temp->chave != chave) {
    anterior = temp;
    temp = temp->prox;
  }
  if(temp == NULL){ return;}
  if(anterior == NULL){ lista->primeiro = temp->prox;}
  else{ anterior->prox = temp->prox;}
  free(temp);
}
