#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main(int argc, char const *argv[]) {
  Tabela *tab = startTabela("dados.dat","indices.dat");
  menu(tab);
  return 0;
}
