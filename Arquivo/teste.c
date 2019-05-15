#include <stdio.h>
#include <stdlib.h>
#include "livro.h"

int main(int argc, char * argv[]) {
    livro * l = ler_livro();
    imprimir_livro(l);
    exit(0);


}
