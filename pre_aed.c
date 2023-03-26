#include<stdio.h>

typedef struct personagem
{
    /* data */

    char nome[10];
    int id;

}personagem;


int main(int argc, char const *argv[])
{
    /* code */

    int idade = 42;
    int *ponteiro_para_short = &idade;

    personagem jedi = {"kenoby",32};
    personagem sith = {"dookan",56};
    personagem clone = {"omega",12};

    printf("%d\n", ponteiro_para_short); //endereço de idade na memória
    printf("%d\n", *ponteiro_para_short); //valor de idade

    printf("O personagem %s tem a idade de %d anos\n", jedi.nome, jedi.id);
    printf("O personagem %s tem a idade de %d anos\n", sith.nome, sith.id);

    for (short i = 0; i < 5; i++) {
        printf("%c", clone.nome[i]);
    }
    
    return 0;
}
