#include <stdio.h>
#include <stdlib.h>
#include "lse_neutra.h"

// TODO: lista que armazena valores

typedef struct
{
    int a;
    double b;
    /* data */
} t_composto;

t_composto *criar_composto(int a, double b)
{
    t_composto *c = malloc(sizeof(t_composto));

    c->a = a;
    c->b = b;

    return c;
}

// cria uma variavel anonima para as entradas
int *criar_int(int init)
{

    int *x = malloc(sizeof(init));

    *x = init;

    return x;
}

void imprimir_composto(t_composto *c)
{
    printf("a: %d, b: %lf", c->a, c->b);
}

void imprimir_inteiro(int *num)
{
    printf("%d\n", *num); // derreferencia
}

int main()
{
    t_lse *nros = criar_lse(imprimir_inteiro);
    t_lse *nros_compostos = criar_lse(imprimir_composto);

    // povoando a lista
    // int num;
    // scanf("%d", &num);
    // while (num >= 0)
    // {
    //     inserir_final_lse(nros, criar_int(num));
    //     scanf("%d", &num);
    // }

    // TODO: povoar a lista para comspoto

    int a;
    double b;
    scanf("%d %lf", &a, &b);
    while (a >= 0)
    {
        inserir_final_lse(nros, criar_composto(a, b));
        scanf("%d %lf", &a, &b);
    }

    // acessado a lista
    // int pos;
    // scanf("%d", &pos);
    // while (pos > 0)
    // {
    //     int *p = acessar_lse(nros, pos);
    //     printf("valor: %d na posicao: %d\n", *p, pos);
    //     scanf("%d", &pos);
    // }

    // imprimir_lse(nros);
    imprimir_composto(nros_compostos);
    // posicao
}
