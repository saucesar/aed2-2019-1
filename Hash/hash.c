#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

int hash(int chave){
  return (chave % MAX);
}

Tabela* startTabela(char *dados,char *indices){
  Tabela *tab = (Tabela*)malloc(sizeof(Tabela));

  tab->arquivo_dados = dados;
  tab->arquivo_indices = indices;
  tab->dados = fopen(tab->arquivo_dados, "a+b");
  tab->indices = fopen(tab->arquivo_indices, "r+b");

  for(int i = 0;i<MAX;i++){ tab->lista_indices[i] = NULL;}

  if(tab->indices == NULL){
    tab->indices = fopen(tab->arquivo_indices, "a+b");
    fclose(tab->indices);
    tab->indices = fopen(tab->arquivo_indices, "r+b");
  }

  int chave,ref;
  if(tab->dados != NULL && tab->indices != NULL){
    while (fread(&chave,sizeof(int),1,tab->indices) && fread(&ref,sizeof(int),1,tab->indices)){
      int posicao = hash(chave);
      tab->lista_indices[posicao] = adic_no_inicio(tab->lista_indices[posicao], chave, ref);
    }
    fclose(tab->indices);
    return tab;
  }else{
    if(tab->dados == NULL) printf("NÃO FOI POSSIVEL ABRIR O ARQUIVO \"%s\" \n",tab->arquivo_dados);
    if(tab->indices == NULL) printf("NÃO FOI POSSIVEL ABRIR O ARQUIVO \"%s\" \n",tab->arquivo_indices);
    exit(1);
  }
}

void adicionar_livro(Tabela *tab, Livro *livro){
  int posicao = salvar_livro(tab, livro);
  adicionar_indice(tab,livro->isbn,posicao);
}

void adicionar_indice(Tabela *tab, int chave, int ref){
  int posicao = hash(chave);
  tab->lista_indices[posicao] = adic_no_inicio(tab->lista_indices[posicao],chave,ref);
}

void remover_da_tabela(Tabela *tab, int chave){
  int posicao = hash(chave);
  tab->lista_indices[posicao] = remover_da_lista(tab->lista_indices[posicao],chave);
}

void editar()

int salvar_livro(Tabela *tab, Livro *livro){
  fseek(tab->dados, 0L, SEEK_END);
  int fim = ftell(tab->dados);
  int tamanho_campo;

  fwrite(&livro->isbn, sizeof(int),1,tab->dados);

  tamanho_campo = sizeof(livro->titulo);
  fwrite(&tamanho_campo, sizeof(int), 1, tab->dados);
  fwrite(livro->titulo, tamanho_campo, 1, tab->dados);

  tamanho_campo = sizeof(livro->autor);
  fwrite(&tamanho_campo, sizeof(int), 1, tab->dados);
  fwrite(livro->autor, tamanho_campo, 1, tab->dados);

  tamanho_campo = sizeof(livro->editora);
  fwrite(&tamanho_campo, sizeof(int), 1, tab->dados);
  fwrite(livro->editora, tamanho_campo, 1, tab->dados);

  return fim;
}

int buscar_indice(Tabela *tab, int chave){
  No *no = buscar_na_lista(tab->lista_indices[hash(chave)],chave);
  if(no != NULL){return no->ref;}
  else{ return -1;}
}

No* buscar_na_lista(No *no,int chave){
  No* temp = no;
  while (temp != NULL && temp->chave != chave) { temp = temp->prox;}
  return temp;
}

void exibir_tabela(Tabela *tab){
  for(int i = 0;i<MAX;i++){
    No *temp = tab->lista_indices[i];
    while (temp != NULL) {
      exibir_livro(ler_livro_arquivo(tab,temp->ref));
      //printf("CHAVE: %d REFER: %d\n",temp->chave,temp->ref);
      temp = temp->prox;
    }
  }
}

void finalizar(Tabela *tab){
	fclose(tab->dados);
	salvar_indices(tab);
  exit(0);
}

void salvar_indices(Tabela *tab){
  tab->indices = fopen(tab->arquivo_indices,"w+b");
  for(int i = 0;i<MAX;i++){
    No *temp = tab->lista_indices[i];
    while (temp != NULL) {
      fwrite(temp,(2*sizeof(int)),1,tab->indices);
      temp = temp->prox;
    }
  }
  fclose(tab->indices);
}

Livro* ler_livro_arquivo(Tabela *tab, int posicao){
  Livro* livro = (Livro*) malloc(sizeof(Livro));
  fseek(tab->dados, posicao, SEEK_SET);

  fread(&livro->isbn, sizeof(int), 1, tab->dados);
  livro->titulo = ler_campo(tab->dados);
  livro->autor = ler_campo(tab->dados);
  livro->editora = ler_campo(tab->dados);

  return livro;
}

char* ler_campo(FILE *dados){
  int tamanho_campo;

  fread(&tamanho_campo, sizeof(int), 1, dados);

  char* buffer = (char*)malloc(tamanho_campo*sizeof(char));
  fread(buffer, tamanho_campo, 1, dados);

  return buffer;
}

char* tirar_enter(char *string){
	string[strlen(string) -1] = '\0';
  return string;
}

Livro* ler_livro(){
  Livro *novo = (Livro *) malloc(sizeof(Livro));
  char *buffer = (char *) malloc(sizeof(char) * 256);

  printf ("DIGITE O ISBN: ");
  scanf("%d", &novo->isbn);
	getchar();

  printf ("DIGITE O TITULO: ");
  fgets(buffer, 256, stdin);
  novo->titulo = strdup(tirar_enter(buffer));

  printf ("DIGITE O AUTOR: ");
  fgets(buffer, 256, stdin);
  novo->autor = strdup(tirar_enter(buffer));

  printf ("DIGITE A EDITORA: ");
  fgets(buffer, 256, stdin);
  novo->editora = strdup(tirar_enter(buffer));

  free(buffer);
  return novo;
}

void exibir_livro(Livro *livro){
    printf("ISBN: %d\n", livro->isbn);
    printf("TITULO: %s\n", livro->titulo);
    printf("AUTOR: %s\n", livro->autor);
    printf("EDITORA: %s\n\n", livro->editora);
}

No* startNo(int chave, int refer, No *proximo){
  No *novo = malloc(sizeof(No));
  novo->chave = chave;
  novo->ref = refer;
  novo->prox = proximo;
  return novo;
}

No* adic_no_inicio(No *proximo, int chave, int refer){
  No *novo = startNo(chave,refer,proximo);
  return novo;
}

No* remover_da_lista(No *inicial, int chave){

  No *temp = inicial, *anterior = NULL;

  while (temp != NULL && temp->chave != chave) {
    anterior = temp;
    temp = temp->prox;
  }
  if(temp != NULL){
    if(anterior == NULL){ inicial = temp->prox;}
    else{ anterior->prox = temp->prox;}
    free(temp);
  }
  return inicial;
}
