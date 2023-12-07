#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    /* code */

    int faltas[9], *p_faltas;
    int tam = 9;

    for (unsigned i = 0; i < tam; i++)
    {
        p_faltas = &faltas[i];
        printf("%p\n", p_faltas);
    }

    return 0;
}