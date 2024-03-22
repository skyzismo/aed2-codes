#include <stdio.h>
#include <stdlib.h>

typedef struct f_circular t_fila_circular;

struct f_circular
{
    void **elementos; // ponteiro de ponteiros
    int frente, atras;
    int tamanho;
};

t_fila_circular *criar_fila_circular(int tam)
{
    t_fila_circular *fc = malloc(sizeof(t_fila_circular));
    fc->elementos = malloc(sizeof(void *) * tam);
    fc->frente = -1;
    fc->atras = -1;
    fc->tamanho = tam;

    return fc;
}

int vazia_fila_circular(t_fila_circular *fc)
{
    return (fc->frente == -1);
}

int ocupacao_fila_circular(t_fila_circular *fc)
{
    if (fc->frente < fc->atras)
    {
        return (fc->atras - fc->frente) + 1;
    }
    else
    {
        return (fc->tamanho - fc->frente) + fc->atras + 1;
    }
}

short enfileirar_fila_circular(t_fila_circular *fc, void *novo)
{
    if (ocupacao_fila_circular(fc) == fc->tamanho)
    {
        return 0; // falhou a insercao
    }

    if (vazia_fila_circular(fc))
    {
        fc->atras = 0;
        fc->frente = 0;
    }
    else
    {
        fc->atras = (fc->atras + 1) % fc->tamanho;
    }

    fc->elementos[fc->atras] = novo;

    return 1;
}

void *desenfileirar_fila_circular(t_fila_circular *fc)
{
    void *el = NULL;

    if (vazia_fila_circular(fc))
    {
        return NULL;
    }
    else if (ocupacao_fila_circular(fc) == 1)
    {
        el = fc->elementos[fc->frente];
        fc->atras = -1;
        fc->frente = -1;
    }
    else
    {
        el = fc->elementos[fc->frente];
        fc->frente = (fc->frente + 1) % fc->tamanho;
    }

    return el;
}

void *primeiro_fila_circular(t_fila_circular *fc)
{
    void *el = NULL;

    if (!(vazia_fila_circular(fc)))
    {
        el = fc->elementos[fc->frente];
    }

    return el;
}

void avancar_fila_circular(t_fila_circular *fc)
{
    if (!vazia_fila_circular(fc))
    {
        fc->frente = (fc->frente + 1) % fc->tamanho;

        printf("%p\n", fc->frente);
    }
}

void retroceder_fila_circular(t_fila_circular *fc)
{
    if (!vazia_fila_circular(fc))
    {
        fc->frente = (fc->frente - 1 + fc->tamanho) % fc->tamanho;

        printf("%p\n", fc->frente);
    }
}

// Função de exemplo para imprimir os elementos da fila
void imprimir_fila(t_fila_circular *fc)
{
    if (vazia_fila_circular(fc))
    {
        printf("Fila vazia\n");
        return;
    }

    printf("Elementos da fila: ");
    int i = fc->frente;
    do
    {
        printf("%p ", fc->elementos[i]);
        i = (i + 1) % fc->tamanho;
    } while (i != (fc->atras + 1) % fc->tamanho);

    printf("\n");
}