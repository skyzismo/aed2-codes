typedef void (*t_imprimir_ab)(void *);
typedef struct ab t_ab;
t_ab *criar_ab(t_imprimir_ab impressora);
void inserir_ab(t_ab *ab, void *info);
void mostrar_ab(t_ab *ab);