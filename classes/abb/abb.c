#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "abb.h"

typedef struct no t_no;
struct no
{
    void *info;
    t_no *sae;
    t_no *sad;
    t_no *ancestral;
};

t_no *criar_no(void *info, t_no *ancestral)
{
    t_no *novo = malloc(sizeof(t_no));

    novo->info = info;
    novo->ancestral = ancestral;
    novo->sad = NULL;
    novo->sae = NULL;

    return novo;
}

struct abb
{
    t_no *raiz;
    int tamanho;

    t_imprimir_abb impressora;
    t_comparar_abb comparar;
};

t_abb *criar_abb(t_imprimir_abb impressora, t_comparar_abb comparar)
{
    t_abb *nova = malloc(sizeof(t_abb));
    nova->raiz = NULL;
    nova->tamanho = 0;
    nova->impressora = impressora;
    nova->comparar = comparar;

    return nova;
}

static t_no *_inserir_abb(t_no *raiz, t_no *ancestral, void *info, t_comparar_abb comparar)
{
    if (raiz == NULL)
    {
        return criar_no(info, ancestral);
    }
    else
    {
        int k = comparar(raiz->info, info);
        if (k >= 0)
        { // inserir esquerda

            raiz->sae = _inserir_abb(raiz->sae, raiz, info, comparar);
        }
        else
        {

            raiz->sad = _inserir_abb(raiz->sad, raiz, info, comparar);
        }
        return raiz;
    }
}

void inserir_abb(t_abb *abb, void *info)
{

    abb->raiz = _inserir_abb(abb->raiz, NULL, info, abb->comparar);
    abb->tamanho++;
}

void _mostrar_abb(t_no *no, t_imprimir_abb impressora)
{
    if (no == NULL)
    {
        return; // nao faz nada mesmo
    }
    _mostrar_abb(no->sae, impressora);
    // printf("no: %p sae:%p sad:%p\n", no, no->sae, no->sad);
    impressora(no->info);
    _mostrar_abb(no->sad, impressora);
}

void *_buscar_abb(t_no *raiz, void *chave, t_comparar_abb comparar)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    else
    {
        int status = comparar(raiz->info, chave);

        if (status == 0)
        {
            return raiz;
        }
        else if (status > 0)
        {
            return _buscar_abb(raiz->sae, chave, comparar);
        }
        else
        {
            return _buscar_abb(raiz->sad, chave, comparar);
        }
    }
}

t_no *__buscar_abb(t_no *raiz, void *chave, t_comparar_abb comparar)
{
    void *retorno = NULL;
    int continua = 1;
    do
    {
        if (raiz == NULL)
        {
            continua = 0;
            retorno = NULL;
        }
        else
        {
            int status = comparar(raiz->info, chave);

            if (status == 0)
            {
                continua = 0;
                retorno = raiz;
            }
            else if (status > 0)
            {
                raiz = raiz->sae;
            }
            else
            {
                raiz = raiz->sad;
            }
        }
    } while (continua);
    return retorno;
}

void *buscar_abb(t_abb *abb, void *chave)
{
    t_no *no = _buscar_abb(abb->raiz, chave, abb->comparar);

    if (no != NULL)
    {
        return no->info;
    }
    else
    {
        return NULL;
    }
}

t_no *_remover_abb(t_no *raiz, void *chave, t_comparar_abb comparar)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    else
    {
        int status = comparar(raiz->info, chave);

        if (status > 0)
        {
            raiz->sae = _remover_abb(raiz->sae, chave, comparar);
            return raiz;
        }
        else if (status < 0)
        {
            raiz->sad = _remover_abb(raiz->sad, chave, comparar);
            return raiz;
        }
        else
        {
            if ((raiz->sae == NULL) && (raiz->sad == NULL)) // folha
            {
                free(raiz->info);
                free(raiz);

                printf("Remocao da folha!!!!\n");

                return NULL;
            }
            else if ((raiz->sae == NULL) && (raiz->sad != NULL)) // descendente na SAD
            {
                raiz->sad->ancestral = raiz->ancestral;

                t_no *aux = raiz->sad;
                aux = raiz->sad;
                free(raiz->info);
                free(raiz);

                return aux;
            }
            else if ((raiz->sae != NULL) && (raiz->sad == NULL))
            {
                raiz->sae->ancestral = raiz->ancestral;

                t_no *aux = raiz->sae;
                aux = raiz->sae;
                free(raiz->info);
                free(raiz);

                return aux;
            }
        }
    }
}

void remover_abb(t_abb *abb, void *chave)
{
    abb->raiz = _remover_abb(abb->raiz, chave, abb->comparar);
}

void mostrar_abb(t_abb *abb)
{
    _mostrar_abb(abb->raiz, abb->impressora);
}

#define max(a, b) (a > b ? a : b)
static int _altura_abb(t_no *raiz)
{
    if (raiz == NULL)
    {
        return -1;
    }
    else
    {
        return max(_altura_abb(raiz->sae), _altura_abb(raiz->sad)) + 1;
    }
}

int altura_abb(t_abb *abb)
{
    return _altura_abb(abb->raiz);
}

int _vazia_abb(t_no *raiz)
{
    return (raiz == NULL);
}

int vazia_abb(t_abb *abb)
{
    return ((abb != NULL) && _vazia_abb(abb->raiz));
}

int tamanho_abb(t_abb *abb)
{
    return abb->tamanho;
}