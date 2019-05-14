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

char* tirar_enter(char *string){
	string[strlen(string) -1] = '\0';
  return string;
}

Livro * ler_livro(){
  Livro *novo = (livro *) malloc(sizeof(livro));
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

void imprimir_livro(Livro *l){
    printf("ISBN: %d\n", l->isbn);
    printf("TITULO: %s\n", l->titulo);
    printf("AUTOR: %s\n", l->autor);
    printf("EDITORA: %s\n", l->editora);
}

int salvar_livro(Tabela *tab, Livro * livro){
  fseek(tab->dados, 0, SEEK_END);
  int fim = ftell(tabela->dados);

  fprintf(tabela->dados, "%d|", livro->isbn);
  fprintf(tabela->dados, "%s|", livro->titulo);
  fprintf(tabela->dados, "%s|", livro->autor);
  fprintf(tabela->dados, "%s|", livro->editora);

  return fim;
}

char* ler_campo(Tabela *tab){
  char* buffer = malloc(sizeof(char) * 256);

  for(int i = 0; i < 256; i++) {
    buffer[i] = fgetc(tab->dados);
    if(buffer[i] == '|') {
      buffer[i] = '\0';
      break;
    }
  }
  return buffer;
}

Livro* ler_livro_arquivo(Tabela *tab, int posicao) {
  Livro* livro = (Livro*) malloc(sizeof(Livro));
  fseek(tab->dados, posicao, SEEK_SET);

  livro->isbn = atoi(ler_campo(tabela->dados));
  livro->titulo = strdup(ler_campo(tabela->dados));
  livro->autor = strdup(ler_campo(tabela->dados));
  livro->editora = strdup(ler_campo(tabela->dados));

  return novo;
}

void adicionar_livro(Tabela *tab, Livro *livro) {
  int posicao = salvar_livro(tab, livro);
  adicionar_indice(tab,livro->isbn,posicao);
}

void adicionar_indice(Tabela *tab, int chave, int ref){
  adic_no_inicio(tab->lista_indices[hash(chave)],chave,ref);
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
  No *novo = startNo(chave,refer,lista->primeiro);
  lista->primeiro = novo;
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
