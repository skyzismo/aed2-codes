#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

typedef struct de t_de;
typedef int (*t_comparar_de)(void *, void *);
typedef void *(*t_buscar_de)(t_de *d, void *chave);

struct de
{
    void **elems;
    int tamanho;
    int ocupacao;
    t_comparar_de comparar;
    t_buscar_de buscar;
};

static void *busca_sequencial(t_de *d, void *chave)
{
    int i = 0;
    while (i < d->ocupacao && (d->comparar(d->elems[i], chave) != 0))
    {
        i++;
    }

    if (i < d->ocupacao)
    {
        return d->elems[i];
    }

    else
    {
        return NULL;
    }
}

static void *__busca_binaria(void *elems[], int lim_i, int lim_f, void *chave, t_comparar_de comparar)
{
    if (lim_i > lim_f)
    {
        return NULL;
    }

    int meio = (lim_i + lim_f) / 2;
    int status = comparar(elems[meio], chave);

    if (status == 0)
    {
        return elems[meio];
    }
    else if (status > 0)
    {
        return __busca_binaria(elems, lim_i, meio - 1, chave, comparar);
    }
    else
    {
        return __busca_binaria(elems, meio + 1, lim_f, chave, comparar);
    }
}

static void *busca_binaria(t_de *d, void *chave)
{
    return __busca_binaria(d->elems, 0, d->ocupacao - 1, chave, d->comparar);
}

t_de *criar_de(int tam, int ordenado, t_comparar_de comparar)
{
    t_de *de = malloc(sizeof(t_de));
    de->tamanho = tam;
    de->ocupacao = 0;
    de->elems = malloc(sizeof(void *) * tam);
    de->comparar = comparar;

    de->buscar = (ordenado ? busca_binaria : busca_sequencial);

    return de;
}

void popular_de(t_de *d, void *elem)
{
    // TODO: erro de semantica
    assert(d->ocupacao < d->tamanho);
    d->elems[d->ocupacao] = elem;
    d->ocupacao++;
}

void *busca_de(t_de *d, void *chave)
{
    d->buscar(d, chave);
}
