#include<stdio.h>

int main(int argc, char const *argv[])
{
    short tam_cc = 3, tam_ec = 3;

    double notas_cc[] = {8.0, 8.5, 9.0};
    double notas_ec[] = {6.7, 7.0, 8.0};
    // double notas_es[] = {7.5, 8.5, 9.5};

    double vet_aux[tam_cc+tam_ec]; //vetor responsável por receber os outros vetores ordenados

    short i = 0, j = 0, k = 0;

    while ((i < tam_cc) && (j < tam_ec)){
        if (notas_ec[j] > notas_cc[i]) {
            vet_aux[k] = notas_cc[i]; //o menor número é copiado para o vet auxiliar
            i++;
        }
        else {
            vet_aux[k] = notas_ec[j];
            j++;
        }
        k++; //é aqui que o vet_aux faz a iteração para receber novos elementos 
    }

    //abaixo, duas iterações nos vetores quando um ou outro ficar vazio

    while (i < tam_cc)
    {
        vet_aux[k] = notas_cc[i];
        i++;
        k++;
    }
    
    while (j < tam_ec)
    {
        vet_aux[k] = notas_ec[j];
        j++;
        k++;
    }
    
    for (short m = 0; m < tam_cc+tam_ec; m++) {
        printf(" %.2f", vet_aux[m]);
    }

    return 0;
}
