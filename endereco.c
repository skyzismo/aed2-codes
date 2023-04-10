#include <stdio.h>

int main(int argc, char const *argv[])
{
    /* code */

    int tam = 10;

    int vet_int[tam];
    double vet_double[tam];
    char vet_char[tam];

    //imprime os enderecos de cada tipo de vetor inicializado

    printf("%p\n", vet_int);
    printf("%p\n", vet_double);
    printf("%p\n", vet_char);
    printf("vet_double + 1: %p\n\n", vet_double + 1);

    printf("\n#### A soma dos garotinhos do vet_double mais o indice ate 10 ###\n");

    for (short i = 0; i < tam; i++) {
        printf("%d valor: %p\n", i, vet_double+i);
    }
    printf("%ld\n",sizeof(vet_double)); //retorna o tamanho em 8 bytes * o numero de elementos
    return 0;
}
