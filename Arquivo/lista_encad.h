#ifndef LISTA_ENCAD
#define LISTA_ENCAD

typedef struct no_encad{
  int valor;
  int ref;
  struct no_encad *prox;
}No;

typedef struct lista_encad{
  No *primeiro;
}Lista;

No* startNo(int valor, No* proximo);
Lista* startLista();

void adic_no_inicio(Lista *lista, int valor);
void remover(Lista *lista, int valor);

#endif
