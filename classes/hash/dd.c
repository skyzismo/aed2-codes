#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "assert.h"
#include <stdint.h>
#include "lseneutra.h"
#include "dd.h"

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

struct dd
{
    t_lse **entradas;

    int M; // tamanho da tabela
    int fc;

    int ocupacao; // elementos na tabela
    double limite_carga;
};

static void internal_destruir_dd(t_dd *dd)
{
    for (int i = 0; i < dd->M; i++)
    {
        t_lse *lst = dd->entradas[i];
        assert(tamanho_lse(lst) == 0);
        destruir_lse(lst);
    }
    free(dd->entradas);
}

static t_dd *internal_criar_dd(int M, int fc)
{

    t_dd *dd = malloc(sizeof(t_dd));
    dd->M = M;        // 101 entrada
    dd->fc = fc;      // 10 por entrada
    dd->ocupacao = 0; //
    dd->limite_carga = 0.75;

    dd->entradas = malloc(sizeof(t_lse *) * M);
    for (int i = 0; i < M; i++)
    {
        dd->entradas[i] = criar_lse(NULL, comparar_elem_dd);
    }

    return dd;
}

static double check_dd(t_dd *dd)
{
    double soma_xi = 0.0;

    for (int i = 0; i < dd->M; i++)
    {
        t_lse *l = dd->entradas[i];
        int xi = tamanho_lse(l);
        soma_xi += (double)(xi * xi) / dd->ocupacao;
    }
    double C = soma_xi - dd->fc;

    return C;
}

/// @brief reconstruir o dicionário a partir da medida de espalhamento
/// @param dd dicionário a ser reconstruído
static void rehashing_dd(t_dd *dd)
{
    double carga = (double)(dd->ocupacao) / (dd->M * dd->fc);

    // testa o limite
    if (carga < dd->limite_carga)
    {
        return;
    }
    else
    {
        // teste a espalhamento
        double C = check_dd(dd);
        if (C <= 1.0)
            return;
    }

    /// Criar e inicializar a nova tabela
    t_dd *novo = internal_criar_dd(dd->M * 2, dd->fc);

    // movendo os itens para a nova tabela
    for (int i = 0; i < dd->M; i++)
    {
        t_lse *lst = dd->entradas[i];
        t_elem_dd *e = remover_inicio_lse(lst);
        while (e != NULL)
        {
            inserir_dd(novo, e->chave, e->carga);
            free(e);
            e = remover_inicio_lse(lst);
        }
    }

    // liberar espaço na memória mas não destroi completamente o dd
    internal_destruir_dd(dd);

    dd->entradas = novo->entradas;
    dd->fc = novo->fc;
    dd->M = novo->M;
    dd->ocupacao = novo->ocupacao;

    // libera a memória criada para o novo mas não destroi
    free(novo);
}

/// @brief  cria dicionária dinâmico usando uma tabela hash como ED
/// @param M tamanho da tabela
/// @param fc fator de carga
/// @return dicionário dinâmico
t_dd *criar_dd()
{
    int M = 101;
    int fc = 3;
    return internal_criar_dd(M, fc);
}

void inserir_dd(t_dd *dd, int chave, void *info)
{
    t_elem_dd *novo = criar_elem_dd(chave, info);

    int k = funcao_hash(dd->M, chave);

    inserir_lse(dd->entradas[k], novo);
    dd->ocupacao++;

    // avaliar se precisa executar arrumação
    rehashing_dd(dd);
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

    t_elem_dd *e = remover_conteudo_lse(dd->entradas[k], &chave);
    void *retorno = NULL;
    if (e != NULL)
    {
        retorno = e->carga;
        dd->ocupacao--;
        free(e);
    }
    return retorno;
}

void destruir_dd(t_dd *dd)
{
    internal_destruir_dd(dd);
    free(dd);
}

void stats_dd(t_dd *dd)
{
    for (int i = 0; i < dd->M; i++)
    {
        t_lse *ent = dd->entradas[i];
        printf("entrada %d comparacoes: %lf tamanho: %d\n", i, stats_lse(ent), tamanho_lse(ent));
    }
}
