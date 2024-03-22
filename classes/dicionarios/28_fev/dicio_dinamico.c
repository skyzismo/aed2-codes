#include "stdio.h"
#include "stdlib.h"
#include "lse_neutra.h"

typedef struct elem_dd t_elem_dd;

struct elem_dd
{
    int chave;
    void *carga;
};

t_elem_dd *criar_elem_dd(int chave, void *info)
{
    t_elem_dd *novo = malloc(sizeof(t_elem_dd));
    novo->chave = chave;
    novo->carga = info;

    return novo;
}

int comparar_elem_dd(void *e1, void *e2)
{
    t_elem_dd *ee1 = e1;
    t_elem_dd *ee2 = e2;

    return (ee1->chave - ee2->chave);
}

static int funcao_hash(int M, int chave)
{
    return (chave % M);
}

typedef struct dd t_dd;
struct dd
{
    t_lse **entradas;
    int M; // tamanho da tabela
    int fc;
};

t_dd *criar_dd(int M, int fc)
{
    t_dd *dd = malloc(sizeof(t_dd));
    dd->entradas = malloc(sizeof(t_lse *) * M);
    dd->M = M;
    dd->fc = fc;
    for (int i = 0; i < M; i++)
    {
        dd->entradas[i] = criar_lse(NULL, comparar_elem_dd);
    }

    return dd;
}

void inserir_dd(t_dd *dd, int chave, void *info)
{
    t_elem_dd *novo = criar_elem_dd(chave, info);

    int k = funcao_hash(dd->M, chave);

    inserir_lse(dd->entradas[k], novo);
}

void *buscar_dd(t_dd *dd, int chave)
{
    int k = funcao_hash(dd->M, chave);

    t_elem_dd *e = buscar_lse(dd->entradas[k], &chave);

    if (e != NULL)
    {
        return e->carga;
    }
    else
    {
        return NULL;
    }
}

void *remover_dd(t_dd *dd, int chave)
{
    int k = funcao_hash(dd->M, chave);

    t_elem_dd *e = remover_inicio_lse(dd->entradas[k]); //, &chave);

    void *retorno = e->carga;

    free(e);

    return retorno;
}