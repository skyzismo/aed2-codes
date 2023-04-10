#include<stdio.h>

int main(int argc, char const *argv[])
{
    short tam_vet = 6;
    int vet[tam_vet];

    for (short i = 0; i < tam_vet; i++) {
        scanf("%d", &vet[i]);
    }

    int aux = vet[0];  //armazena o primeiro elemento do vetor para que as comparações sejam feitas

    for (short j = 0; j < tam_vet; j++) {
        if(vet[j] > aux){
            aux = vet[j];
        }
    }

    printf("O maior elemento é: %d\n",aux);

    for (short k = 0; k < tam_vet; k++) {
        if(vet[k] == aux){
            printf("Elemento: %d, indice: %d\n",vet[k],k);
        }
    }

    return 0;
}
