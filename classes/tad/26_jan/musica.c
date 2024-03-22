#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "musica.h"

struct musica
{
    char nome[60];
    char genero[30];
    int duracao;
};

void imprimir_musica(void *m1)
{
    t_musica *m = m1;

    int min = m->duracao / 60;
    int seg = m->duracao - min * 60;
    printf("%s %s %02d:%02d\n", m->nome, m->genero, min, seg);
}

t_musica *criar_musica(char nome[], char genero[], int duracao)
{
    t_musica *nova = malloc(sizeof(t_musica));
    strcpy(nova->nome, nome);
    strcpy(nova->genero, genero);

    nova->duracao = duracao;

    return nova;
}

int comparar_musica(void *musica1, void *musica2)
{
    t_musica *m1 = musica1;
    t_musica *m2 = musica2;
    return strcmp(m1->nome, m2->nome);
}