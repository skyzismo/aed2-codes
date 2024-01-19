#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lse_neutra.h"

#define PLAYING 1
#define PAUSE 2
#define STOP 3
#define LOAD 4
#define FINAL 5
#define RESUME 6

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

// TODO: TAD playlist e biblioteca

struct playlist
{
    char nome[60];
    int duracao;
    char descricao[1000];
    int qtd;
    int dia, mes, ano;
    void *musicas;
};

typedef struct biblioteca t_biblioteca;

struct biblioteca
{
    t_lse *musicas;
    t_lse *playlists;
};

typedef struct tocador t_tocador;

struct tocador
{
    int status;
    t_musica *faixa_carregada;

    // biblioteca de musicas
};

t_tocador *criar_tocador()
{
    t_tocador *novo = malloc(sizeof(t_tocador));

    novo->status = STOP;
    novo->faixa_carregada = NULL;

    return novo;
}

void play_tocador(t_tocador *t)
{
    if (t->status == LOAD)
    {
        printf("Reproduzindo\n");
        imprimir_musica(t->faixa_carregada);

        t->status = PLAYING;
    }
}

void pause_tocador(t_tocador *t)
{
    printf("Pausando\n");
    imprimir_musica(t->faixa_carregada);

    t->status = PAUSE;
}

void stop_tocador(t_tocador *t)
{
    if (t->status != STOP)
    {
        printf("Parando\n");
        t->status = STOP;
    }
}

void loading_tocador(t_tocador *t)
{
    if (t->status == STOP)
    {
        t->faixa_carregada = malloc(sizeof(t_musica));
        scanf("%s", t->faixa_carregada->nome);
        scanf("%s", t->faixa_carregada->genero);
        scanf("%d", &(t->faixa_carregada->duracao));

        t->status = LOAD;
    }
}

void resume_tocador(t_tocador *t)
{
    if (t->status == PAUSE)
    {
        printf("Retomando\n");
        imprimir_musica(t->faixa_carregada);
        t->status = PLAYING;
    }
}

int main(int argc, char const *argv[])
{
    int acao;
    t_tocador *tocador = criar_tocador();

    do
    {
        scanf("%d", &acao);

        switch (acao)
        {
        case LOAD:
            loading_tocador(tocador);
            break;

        case PLAYING:
            play_tocador(tocador);
            break;

        case PAUSE:
            pause_tocador(tocador);
            break;

        case STOP:
            stop_tocador(tocador);
            break;

        case RESUME:
            resume_tocador(tocador);
            break;

        default:
            break;
        }
    } while (acao != FINAL);
}
