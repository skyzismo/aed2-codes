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

int main(int argc, char const *argv[])
{
    char nome[60];
    char genero[30];
    int duracao;

    t_lse *playlist = criar_lse(imprimir_musica, comparar_musica);

    scanf("%s", nome);

    while (strcmp(nome, "FIM") != 0)
    {
        scanf("%s", genero);
        scanf("%d", &duracao);

        inserir_ordenado_lse(playlist, criar_musica(nome, genero, duracao));

        // inserir_final_lse(playlist, criar_musica(nome, genero, duracao));

        scanf("%s", nome);
    }

    // char buscado[60]; para string do nome

    t_musica *buscado = malloc(sizeof(t_musica)); // agora, o buscado é a música, com seus atributoa

    scanf("%s", buscado->nome);

    t_musica *m = buscar_lse(playlist, (void *)buscado);

    if (m != NULL)
    {
        imprimir_musica(m);
    }

    // imprimir_lse(playlist);
}