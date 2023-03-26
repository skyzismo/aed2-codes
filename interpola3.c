#include<stdio.h>

void intercalar(double vetor_a[], short tam_a, double vetor_b[], short tam_b, double resultado[]){

    short i = 0, j = 0, k = 0;

    while ((i < tam_a) && (j < tam_b)){
        if (vetor_b[j] > vetor_a[i]) {
            resultado[k] = vetor_a[i];
            i++;
        }
        else {
            resultado[k] = vetor_b[j];
            j++;
        }
        k++;
    }

    while (i < tam_a)
    {
        resultado[k] = vetor_a[i];
        i++;
        k++;
    }
    
    while (j < tam_b)
    {
        resultado[k] = vetor_b[j];
        j++;
        k++;
    }
}

void ler_notas(double vetor_notas[], short tam){
    for(short i = 0; i < tam; i++){
        scanf("%lf", &vetor_notas[i]);
    }
}

int main(int argc, char const *argv[])
{
    /* code */

    short tam_cc = 3, tam_ec = 3, tam_es = 3;

    double notas_cc[tam_cc];
    double notas_ec[tam_ec];
    double notas_es[tam_es];

    ler_notas(notas_cc, tam_cc);
    ler_notas(notas_ec, tam_ec);
    ler_notas(notas_es, tam_es);

    double medias_cc_ec[tam_cc+tam_ec]; //vetor auxiliar que ordenará os dois primeiros vetores
    double medias[tam_cc+tam_ec+tam_es]; //vetor final que ordena os três vetores

    intercalar(notas_cc, tam_cc, notas_ec, tam_ec, medias_cc_ec);
    intercalar(medias_cc_ec, tam_cc+tam_ec, notas_es, tam_es, medias);

    for (short j = 0; j < tam_cc+tam_ec+tam_es; j++) {
        printf("%.2lf ", medias[j]);
    }
    printf("\n");

    return 0;
}
