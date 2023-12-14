#include <stdio.h>
#include <stdlib.h>
// #include <listase.h>

typedef struct elem_se
{
    int carga_util;
    struct elem_se *prox; // endereco próximo elemento referenciando a si mesma

} t_elemento_lse;

t_elemento_lse *criar_elemento_lse(int carga_util)
{
    t_elemento_lse *novo = malloc(sizeof(t_elemento_lse));

    novo->carga_util = carga_util;
    novo->prox = NULL;

    return novo;
}

typedef struct lse
{
    // enderecos dos elementos, ponteiros para t_elemento_lse
    t_elemento_lse *inicio;
    t_elemento_lse *fim;
    int tamanho;
} t_lse;

// criacao da lista simplesmente encadeada
t_lse *criar_lse()
{
    t_lse *l = malloc(sizeof(t_lse));
    l->inicio = l->fim = NULL;
    l->tamanho = 0;

    return l;
}

// insere o elemento no início da lista

void inserir_lse(t_lse *lse, int carga_util)
{
    t_elemento_lse *novo = criar_elemento_lse(carga_util);

    if (lse->inicio == NULL)
    {
        lse->inicio = lse->fim = novo;
    }
    else
    {
        novo->prox = lse->inicio;
        lse->inicio = novo;
    }

    lse->tamanho++;
}

void inserir_final_lse(t_lse *lse, int carga_util)
{

    t_elemento_lse *novo = criar_elemento_lse(carga_util);

    if (lse->inicio == NULL)
    {
        lse->inicio = lse->fim = novo;
    }
    else
    {
        lse->fim->prox = novo;
        lse->fim = novo;
    }

    lse->tamanho++;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}