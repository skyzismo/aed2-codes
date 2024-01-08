#include "stdio.h"
#include "stdlib.h"

// TODO: implementar void *remover_inicio_lse(t_lse *lse) e void *remover_final_lse(t_lse *lse)

typedef struct elem_se
{
    int carga_util;
    struct elem_se *prox;
} t_elemento_lse;

/**
 * cria um elemento da LSE
 */
t_elemento_lse *criar_elemento_lse(int carga_util)
{
    t_elemento_lse *novo = malloc(sizeof(t_elemento_lse));
    novo->carga_util = carga_util;
    novo->prox = NULL;

    // printf("Criando: %p %p %p\n", novo, novo->carga_util, novo->prox);

    return novo;
}

typedef struct lse t_lse;
struct lse
{
    t_elemento_lse *inicio;
    t_elemento_lse *fim;
    int tamanho;
};

t_lse *criar_lse()
{ //, t_comparar_lse comparar){
    t_lse *l = malloc(sizeof(t_lse));
    l->inicio = l->fim = NULL;
    l->tamanho = 0;
    return l;
}

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

int acessar_lse(t_lse *lse, int pos)
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

int main()
{
    t_lse *nros = criar_lse();

    // povoando a lista
    int num;
    scanf("%d", &num);
    while (num >= 0)
    {
        inserir_final_lse(nros, num);
        scanf("%d", &num);
    }

    // acessado a lista
    int pos;
    scanf("%d", &pos);
    while (pos > 0)
    {
        num = acessar_lse(nros, pos);
        printf("valor: %d na posicao: %d", num, pos);
        scanf("%d", &pos);
    }
    // posicao
}