#include <stdio.h>
#include <stdlib.h>
// #include <listase.h>

typedef struct elem_se
{
    int carga_util;
    struct elem_se *prox; // endereco próximo elemento referenciando a si mesma

} t_elemento_lse;

// tipo associado a ponteiro para funcoes especialistas -> sabe o TAD que colocou na lista

typedef void (*t_imprimir_lse)(int);

typedef struct lse
{
    // enderecos dos elementos, ponteiros para t_elemento_lse, atributos de manipulacao de listas
    t_elemento_lse *inicio;
    t_elemento_lse *fim;
    t_imprimir_lse imprimir;
    int tamanho;
} t_lse;

t_elemento_lse *criar_elemento_lse(int carga_util)
{
    t_elemento_lse *novo = malloc(sizeof(t_elemento_lse));

    novo->carga_util = carga_util;
    novo->prox = NULL;

    return novo;
}

// criacao da lista simplesmente encadeada
// obriga a dizer qual a funcao de impressao
t_lse *criar_lse(t_imprimir_lse impressora)
{
    t_lse *l = malloc(sizeof(t_lse));
    l->inicio = l->fim = NULL;
    l->tamanho = 0;
    l->imprimir = impressora; // recebe da criar_lse
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

// insere o elemento no final da lista

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

int remover_inicio_lse(t_lse *lse)
{
    t_elemento_lse *aux = lse->inicio;

    int carga;

    if (lse->inicio != NULL)
    {
        lse->inicio = aux->prox;
        carga = aux->carga_util;
        free(aux);
        lse->tamanho--; // a cada operação de remoção, o tamanho da lista precisa diminuir
    }

    return (carga);
}

int acessar_lse(t_lse *lse, int pos)
{
    // posicao eh colida através do tamanho da LSE
    pos = pos % lse->tamanho;

    pos = (pos == 0 ? lse->tamanho : pos);

    // variavel caminho
    t_elemento_lse *cam = lse->inicio;

    for (int i = 1; i < pos; i++)
    {
        cam = cam->prox;
    }

    return cam->carga_util;
}

// TODO: acesso reverso da lista

void imprimir_lista(t_lse *lse)
{

    t_elemento_lse *cam = lse->inicio;

    while (cam != NULL)
    {
        // printf("%d %p %ld\n", cam->carga_util, cam, sizeof(cam));
        // chama a função especialista
        lse->imprimir(cam->carga_util);
        cam = cam->prox;
    }
}

// TODO: funcoes especialistas que imprimem qualquer tipo de dado
// void imprimir_musica(t_musica *musica)
// {
//     printf("%s ", musica);
//     printf("%d (seg)", musica.duracao);
// }

void imprimir_nro(int nro)
{
    printf("%d\n", nro);
}

int main()
{
    t_lse *numeros = criar_lse(imprimir_nro);
    // t_lse *pls_ultimas_tocadas = criar_lse(imprimir_musica);

    // povoando a lista
    int num;
    scanf("%d", &num);

    while (num != 0)
    {
        inserir_final_lse(numeros, num);
        scanf("%d", &num);
    }

    // acessando a lista
    int pos;
    scanf("%d", &pos);

    while (pos > 0)
    {
        num = acessar_lse(numeros, pos);

        printf("valor: %d na posicao: %d\n ", num, pos);

        scanf("%d", &pos);
    }

    int removedor;
    int removido;
    scanf("%d", &removedor);

    while (numeros->tamanho)
    {
        removido = remover_inicio_lse(numeros);

        printf("o valor: %d foi removido \n", removido);

        scanf("%d", &removedor);
    }

    imprimir_lista(numeros);
}