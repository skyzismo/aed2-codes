#include <stdio.h>
#include <stdlib.h>
#include "lse_neutra.h"

// cria uma variavel anonima para as entradas
int *criar_int(int init)
{

    int *x = malloc(sizeof(init));

    *x = init;

    return x;
}

// TODO: lista que armazena valores

typedef struct
{
    int a, b;
    double x, y;
    /* data */
} t_composto;

int main(int argc, char const *argv[])
{
    t_lse *nros = criar_lse();

    // povoando a lista
    int num;
    scanf("%d", &num);
    while (num >= 0)
    {
        inserir_final_lse(nros, criar_int(num));
        scanf("%d", &num);
    }

    // acessado a lista
    int pos;
    scanf("%d", &pos);
    while (pos > 0)
    {
        int *p = acessar_lse(nros, pos);
        printf("valor: %d na posicao: %d\n", *p, pos);
        scanf("%d", &pos);
    }
    // posicao
}
