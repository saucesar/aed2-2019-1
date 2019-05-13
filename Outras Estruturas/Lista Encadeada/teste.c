#include <stdio.h>
#include <stdlib.h>
#include "lista_encad.h"

int main(int argc, char const *argv[]) {
  Lista *lista = startLista();

  while (1) {
    int opcao,valor;
    scanf("%d",&opcao);
    switch (opcao) {
      case 1:
        scanf("%d",&valor);
        adic_no_inicio(lista,valor);
        break;
      case 2:
        exibir_lista(lista);
        break;
      case 3:
        scanf("%d",&valor);
        remover(lista,valor);
        break;
      case 99:
        exit(0);
    }
  }
  return 0;
}
