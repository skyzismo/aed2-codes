#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "ab.h"

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

struct ab
{
    t_no *raiz;
    int tamanho;

    t_imprimir_ab impressora;
};

t_ab *criar_ab(t_imprimir_ab impressora)
{
    t_ab *nova = malloc(sizeof(t_ab));
    nova->raiz = NULL;
    nova->tamanho = 0;
    nova->impressora = impressora;

    return nova;
}

static int sorteio()
{
    static int seed = 1;
    if (seed == 1)
    {
        srand(time(NULL));
        seed = 2;
    }
    int k = rand();
    printf("random:%d\n", k);
    return k;
}

static t_no *_inserir_ab(t_no *raiz, t_no *ancestral, void *info)
{
    if (raiz == NULL)
    {
        return criar_no(info, ancestral);
    }
    else
    {
        int k = (sorteio() % 2);
        if (k == 0)
        {
            raiz->sae = _inserir_ab(raiz->sae, raiz, info);
        }
        else
        {
            raiz->sad = _inserir_ab(raiz->sad, raiz, info);
        }
        return raiz;
    }
}

void inserir_ab(t_ab *ab, void *info)
{

    ab->raiz = _inserir_ab(ab->raiz, NULL, info);
}

void _mostrar_ab(t_no *no, t_imprimir_ab impressora)
{
    if (no == NULL)
    {
        return;
    }
    _mostrar_ab(no->sae, impressora);
    printf("no: %p sae:%p ancestral:%p sad:%p\n", no, no->sae, no->ancestral, no->sad);
    impressora(no->info);
    _mostrar_ab(no->sad, impressora);
}

void mostrar_ab(t_ab *ab)
{
    _mostrar_ab(ab->raiz, ab->impressora);
}

#define max(a, b) (a > b ? a : b)
static int _altura_ab(t_no *raiz)
{
    if (raiz == NULL)
    {
        return -1;
    }
    else
    {
        max(_altura_ab(raiz->sae), _altura_ab(raiz->sad));
    }
}

int altura_ab(t_ab *ab)
{
    return _altura_ab(ab->raiz);
}

int vazia_ab(t_no *raiz)
{
    return (raiz == NULL);
}

int vazia_ab(t_ab *ab)
{
    return ((raiz != NULL) && _vazia_ab(ab->raiz));
}

int tamanho_ab(t_ab *ab)
{
    return ab->tamanho;
}