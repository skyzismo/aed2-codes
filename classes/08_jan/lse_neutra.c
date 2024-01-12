#include "stdio.h"
#include "stdlib.h"
#include "lse_neutra.h"

typedef struct elem_se
{
    void *carga_util; // quebrar acoplamento
    struct elem_se *prox;
} t_elemento_lse;

/**
 * cria um elemento da LSE
 */
t_elemento_lse *criar_elemento_lse(void *carga_util) //
{
    t_elemento_lse *novo = malloc(sizeof(t_elemento_lse));
    novo->carga_util = carga_util;
    novo->prox = NULL;

    // printf("Criando: %p %p %p\n", novo, novo->carga_util, novo->prox);

    return novo;
}

struct lse
{
    t_elemento_lse *inicio;
    t_elemento_lse *fim;
    int tamanho;
    t_imprimir_lse impressora;
};

t_lse *criar_lse(t_imprimir_lse impressora)
{ //, t_comparar_lse comparar){
    t_lse *l = malloc(sizeof(t_lse));
    l->inicio = l->fim = NULL;
    l->tamanho = 0;
    l->impressora = impressora;
    return l;
}

void imprimir_lse(t_lse *lse)
{
    t_elemento_lse *cam = lse->inicio;

    while (cam != NULL)
    {
        // printf("%p\n", cam->carga_util);
        lse->impressora(cam->carga_util);
        cam = cam->prox;
    }
}

void inserir_lse(t_lse *lse, void *carga_util) // insercao com carga util neutralizada
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

void inserir_final_lse(t_lse *lse, void *carga_util)
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

void *acessar_lse(t_lse *lse, int pos)
{
    pos = (pos % lse->tamanho);
    pos = (pos == 0 ? lse->tamanho : pos);

    t_elemento_lse *cam = lse->inicio;
    for (int i = 1; i < pos; i++)
    {
        cam = cam->prox;
    }
    return cam->carga_util;
}

void destruir_lse(t_lse *lse)
{
    t_elemento_lse *elem = lse->inicio;

    while (elem != NULL)
    {
        t_elemento_lse *proximo = elem->prox;
        // destruir_elem_lse(elem->carga)
        free(elem->carga_util);
        free(elem);
        elem = proximo;
    }
}