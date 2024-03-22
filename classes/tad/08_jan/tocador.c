// eh uma solucao

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lse_neutra.h"

typedef struct
{
    char nome[60];
    char genero[30];
    int duracao;
} t_musica;

void imprimir_musica(t_musica *m)
{
    int min = m->duracao / 60;
    int seg = m->duracao - min * 60;
    printf("%s %02d:%02d\n", m->nome, min, seg);
}

t_musica *criar_musica(char nome[], char genero[], int duracao)
{
    t_musica *nova = malloc(sizeof(t_musica));
    strcpy(nova->nome, nome);
    strcpy(nova->genero, genero);

    nova->duracao = duracao;

    return nova;
}

int comparar_musica(t_musica *m1, t_musica *m2)
{
    return strcmp(m1->nome, m2->nome);
}

int main(int argc, char const *argv[])
{
    char nome[60];
    char genero[30];
    int duracao;

    t_lse *playlist = criar_lse(imprimir_musica);

    scanf("%s", nome);

    while (strcmp(nome, "FIM") != 0)
    {
        scanf("%s", genero);
        scanf("%d", &duracao);

        inserir_final_lse(playlist, criar_musica(nome, genero, duracao));

        scanf("%s", nome);
    }

    imprimir_lse(playlist);
}
