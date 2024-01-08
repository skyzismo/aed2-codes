#include <stdlib.h>
#include <stdio.h>

int *criar_variavel()
{
    return malloc(sizeof(int)); // sizeof determina quantos bytes serão necessários, ponteiro que retorna uma área de memória
}

int main(int argc, char const *argv[])
{
    int *p = criar_variavel(); // armazena a referencia de criar_variável

    // p = 10;
    *p = 10;

    printf("%d\n", p);
    printf("%p\n", *p);
    printf("%d\n", *p);

    return 0;
}
