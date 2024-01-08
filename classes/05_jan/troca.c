#include <stdio.h>
#include <stdlib.h>

// funcao trocar neutralizada
void trocar(void **a, void **b)
{
    void *aux = *a; // derreferencia, aux acessa o valor que está na variavel 'a'
    *a = *b;
    *b = aux;

    printf("%p %p\n", a, b);
}

double *criar_double(double init)
{
    double *x = malloc(sizeof(double));

    *x = init;

    return x;
}

// cria uma variavel anonima
int *criar_inteiro(int init)
{

    int *x = malloc(sizeof(init));

    *x = init;

    return x;
}

typedef struct
{
    int a, b;
    double x, y;
    /* data */
} t_composto;

t_composto *criar_composto(int a, int b, double x, double y)
{
    t_composto *c = malloc(sizeof(t_composto));

    c->a = a;
    c->b = b;
    c->x = x;
    c->y = y;

    return c;
}

int main(int argc, char const *argv[])
{
    // double a = 10, b = 20;

    double *a = criar_double(10);
    double *b = criar_double(20);

    t_composto *c1 = criar_composto(100, 200, 15.99, 25.90);
    t_composto *c2 = criar_composto(1000, 34, 199.99, 345.99);

    // int x = 20, y = 30;

    // int *x = criar_inteiro(20);
    // int *y = criar_inteiro(30);

    printf("%lf %lf\n", *a, *b);
    printf("%p %p\n", a, b);

    trocar((void **)&a, (void **)&b); // TODO: estudar derreferecia e passagem por referência (casting - operação forçada)

    // trocar(&a, &b);

    printf("%lf %lf\n\n", *a, *b); // o derreferenciador busca o valor

    printf("%d %lf\n", c1->a, c1->x);

    trocar((void **)&c1, (void **)&c2);

    // printf("%d %d\n", x, y);

    // trocar((void *)&x, (void *)&y); // a chamada imprime o endereço das variaveis a, b, casting

    // trocar(&x, &y);

    // printf("%d %d\n", x, y);
    return 0;
}
