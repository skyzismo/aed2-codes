#include <stdio.h>

int main(int argc, char const *argv[])
{
    /* code */
    // ambas reservam memória e associam nome
    double nota;
    double media;
    double *p_nota, *media;

    printf("%p\n", p_nota);

    nota = 9.0;
    p_nota = &nota;

    printf("%lf\n", nota);
    printf("%p\n", p_nota);
    printf("%lf\n", *p_nota); // desreferenciador, retorna o valor do endereço armazenado
    return 0;
}
