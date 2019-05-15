#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main(int argc, char const *argv[]) {
  Tabela *tab = startTabela("dados.dat","indices.dat");

  while (1) {
    int opcao,chave;
    scanf("%d",&opcao);
    switch (opcao) {
      case 1:
        printf("======INSIRA OS DADOS DO LIVRO=====");
        adicionar_livro(tab,ler_livro());
        break;
      case 2:
        //editar
        break;
      case 3:
        printf("INSIRA A CHAVE A SER REMOVIDA: ");
        scanf("%d",chave);
        remover_da_lista(tab,chave);
        break
      case 4:
        exibir_tabela(tab);
        break;
      case 5:
        //procurar pelo codigo
        break;
      case 99:
        finalizar(tab);
    }
  }
  return 0;
}
