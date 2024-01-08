// funcoes de manipulacao a lista, anda junto com a lse_neutra.c
typedef struct lse t_lse;

t_lse *criar_lse();
void inserir_lse(t_lse *lse, void *carga_util);
void inserir_final_lse(t_lse *lse, void *carga_util);
void *acessar_lse(t_lse *lse, int pos);
void destruir_lse(t_lse *lse);