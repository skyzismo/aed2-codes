#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lse_neutra.h"
#include "fila.h"
#include "pilha.h"

#define PLAYING 1
#define PAUSE 2
#define STOP 3
#define LOAD 4
#define FINAL 5
#define RESUME 6
#define END 7
#define FORWARD 8
#define BACKWARD 9

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

typedef struct playlist t_playlist;
struct playlist
{
    char nome[60];
    int duracao;
    char descricao[1000];
    int qtd;
    int dia, mes, ano;
    t_lse *musicas;
};

typedef struct biblioteca t_biblioteca;

struct biblioteca
{
    t_lse *musicas;
    t_lse *playlists;
    t_lse *generos;
    t_lse *artistas;
    t_lse *albuns;
};

typedef struct tocador t_tocador;

struct tocador
{
    int status;
    t_musica *faixa_carregada;

    // fila de reproducao
    t_fila *proximas;

    // ultimas tocadas

    t_pilha *ultimas;

    // biblioteca de musicas
};

t_tocador *criar_tocador()
{
    t_tocador *novo = malloc(sizeof(t_tocador));

    novo->status = STOP;
    novo->faixa_carregada = NULL;
    novo->proximas = criar_fila();
    novo->ultimas = criar_pilha();

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
    if (t->status == PLAYING)
    {
        printf("Pausando\n");
        imprimir_musica(t->faixa_carregada);

        t->status = PAUSE;
    }
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
        t->faixa_carregada = NULL;
        if (!(vazia_fila(t->proximas))) // se a fila nao esta vazia
        {
            t->faixa_carregada = primeiro_fila(t->proximas);
            t->status = LOAD;
        }

        // t->faixa_carregada = malloc(sizeof(t_musica));
        // scanf("%s", t->faixa_carregada->nome);
        // scanf("%s", t->faixa_carregada->genero);
        // scanf("%d", &(t->faixa_carregada->duracao));
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

void end_tocador(t_tocador *t)
{
    if (t->status == PLAYING)
    {
        t->status = STOP;
        t_musica *m = desenfileirar(t->proximas);
        empilhar(t->ultimas, m);

        // loading_tocador(t);
    }
}

void forward_tocador(t_tocador *t)
{
    if (!vazia_fila(t->proximas))
    {
        t_musica *m = desenfileirar(t->proximas);
        t->faixa_carregada = primeiro_fila(t->proximas);

        printf("Avancando...");

        imprimir_musica(m);
        empilhar(t->ultimas, m);
    }
}

void backward_tocador(t_tocador *t)
{
    if (altura_pilha(t->ultimas) > 0)
    {
        t_musica *m = desempilhar(t->ultimas);
        t->faixa_carregada = m;

        imprimir_musica(m);
        enfileirar(t->proximas, m);
    }
}

static void loading_proximas(t_tocador *t)
{
    int status;
    scanf("%d", &status);

    while (status == 1)
    {
        t_musica *musica = malloc(sizeof(t_musica));

        scanf("%s", musica->nome);
        scanf("%s", musica->genero);
        scanf("%d", &(musica->duracao));

        enfileirar(t->proximas, musica);
        scanf("%d", &status);
    }
}

int main(int argc, char const *argv[])
{
    int acao;
    t_tocador *tocador = criar_tocador();

    loading_proximas(tocador);

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

        case FORWARD:
            forward_tocador(tocador);
            break;

        case BACKWARD:
            backward_tocador(tocador);
            break;

        case END:
            end_tocador(tocador);
            break;

        default:
            break;
        }
    } while (acao != FINAL);

    imprimir_musica(topo(tocador->ultimas));
}
