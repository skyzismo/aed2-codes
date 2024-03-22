#include <stdio.h>
#include <stdlib.h>

// regra de sintaxe de ponteiro pra funcao
typedef void (*t_funcao_trocar)(void **, void **);

int *criar_int(int init)
{

    int *x = malloc(sizeof(init));

    *x = init;

    return x;
}

// funcao trocar neutralizada
void __trocar(void **a, void **b)
{
    void *aux = *a; // derreferencia, aux acessa o valor que está na variavel 'a'
    *a = *b;
    *b = aux;

    printf("trocar\n");
}

void chamadora(t_funcao_trocar trocador, int **a, int **b)
{
    trocador((void **)a, (void **)b);
}

int main()
{

    int *menor = criar_int(10);
    int *maior = criar_int(20);

    t_funcao_trocar trocador;

    // trocador = __trocar;

    // trocador((void **)&maior, (void **)&menor);

    printf("%d %d\n", *menor, *maior);

    // printf("%p\n", __trocar);
    // printf("%p\n", trocador);

    // __trocar((void **)&maior, (void **)&menor);

    chamadora(__trocar, &maior, &menor);

    printf("%d %d\n", *menor, *maior);
}
