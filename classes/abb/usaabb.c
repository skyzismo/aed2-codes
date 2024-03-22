#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "abb.h"

union u_medida
{
    int luminosidade; // media da luminosidade
    int umidade;      // media da umidade
    int movimento;
    double temperatura;
};

typedef struct medida_sensor
{
    int tipo;
    union u_medida medida;
    int hora, min, seg;
} t_medida_sensor;

t_medida_sensor *criar_medida_sensor(int tipo, union u_medida medida, int hora, int min, int seg)
{
    t_medida_sensor *novo = malloc(sizeof(t_medida_sensor));
    novo->tipo = tipo;
    novo->hora = hora;
    novo->min = min;
    novo->seg = seg;
    if (tipo == 3)
    {
        novo->medida.luminosidade = medida.luminosidade;
    }
    else if (tipo == 2)
    {
        novo->medida.movimento = medida.movimento;
    }
    else if (tipo == 1)
    {
        novo->medida.temperatura = medida.temperatura;
    }
    else
    {
        novo->medida.umidade = medida.umidade;
    }

    return novo;
}

long int criar_chave(t_medida_sensor *m)
{
    long int chave = m->tipo * pow(10, 6) + m->hora * pow(10, 4) + m->min * pow(10, 2) + m->seg * pow(10, 0);
    // printf("%ld %d %d:%d:%d\n", chave, m->tipo, m->hora, m->min, m->seg);

    return chave;
}

int comparar_medida_sensor(t_medida_sensor *m1, t_medida_sensor *m2)
{
    long int m1_chave = criar_chave(m1);
    long int m2_chave = criar_chave(m2);

    // printf("%ld %ld\n", m1_chave, m2_chave);

    if (m1_chave == m2_chave)
    {
        return 0;
    }
    else if (m1_chave > m2_chave)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void mostrar_medida_sensor(t_medida_sensor *m)
{
    printf("%d ", m->tipo);
    // if (m->tipo == 1)
    //     printf("%.3lf", m->medida.temperatura);
    // else if (m->tipo == 3)
    // {
    //     printf("%d", m->medida.luminosidade);
    // }
    // else if (m->tipo == 2)
    // {
    //     printf("%d", m->medida.movimento);
    // }
    // else
    // {
    //     printf("%d", m->medida.umidade);
    // }
    printf(" %02d:%02d:%02d\n", m->hora, m->min, m->seg);
}

int main()
{
    int sensor, hora, min, seg;
    union u_medida medida;
    int tamanho = 6;
    t_medida_sensor *ultimo;

    t_abb *medidas = criar_abb(mostrar_medida_sensor, comparar_medida_sensor);

    for (int i = 1; i <= tamanho; i++)
    {
        scanf("%d", &sensor);
        if (sensor == 1)
        {
            scanf("%lf", &(medida.temperatura));
        }
        else if (sensor == 2)
        {
            scanf("%d", &(medida.movimento));
        }
        else if (sensor == 3)
        {
            scanf("%d", &(medida.luminosidade));
        }
        else
        {
            scanf("%d", &(medida.umidade));
        }
        scanf("%d:%d:%d", &hora, &min, &seg);

        t_medida_sensor *novo = criar_medida_sensor(sensor, medida, hora, min, seg);
        // long int chave = criar_chave(novo);

        inserir_abb(medidas, novo);
        ultimo = novo;
    }

    mostrar_abb(medidas);

    printf("Mostrando ultimo---------\n");
    mostrar_medida_sensor(ultimo);
    printf("---------\n");

    t_medida_sensor buscado = (t_medida_sensor){.tipo = ultimo->tipo, .hora = ultimo->hora, .min = ultimo->min, .seg = ultimo->seg};

    remover_abb(medidas, &buscado);

    printf("Removendo---------\n");

    mostrar_abb(medidas);

    // ultimo->tipo = 0;

    // t_medida_sensor *m = buscar_abb(medidas, ultimo);

    // if (m != NULL)
    // {
    //     printf("buscado: ");
    //     mostrar_medida_sensor(m);
    // }
    // else
    // {
    //     printf("Não encontrado: ");
    //     mostrar_medida_sensor(ultimo);
    // }

    printf("altura: %d\n", altura_abb(medidas));
    printf("tamanho: %d\n", tamanho_abb(medidas));
    printf("FIM\n");
}
