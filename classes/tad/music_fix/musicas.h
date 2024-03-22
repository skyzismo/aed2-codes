typedef struct musica t_musica;

t_musica *criar_musica(char nome[], char genero[], int duracao);

void imprimir_musica(void *m1);

int comparar_musica(void *musica1, void *musica2);