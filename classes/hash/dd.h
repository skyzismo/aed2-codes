typedef struct dd t_dd;
typedef struct elem_dd t_elem_dd;
t_elem_dd *criar_elem_dd(int chave, void *info);
int comparar_elem_dd(void *e1, void *e2);
static int funcao_hash(int M, int chave);
static void internal_destruir_dd(t_dd *dd);
static t_dd *internal_criar_dd(int M, int fc);
static double check_dd(t_dd *dd);
t_dd *criar_dd();
static void rehashing_dd(t_dd *dd);
void inserir_dd(t_dd *dd, int chave, void *info);
void *buscar_dd(t_dd *dd, int chave);
void *remover_dd(t_dd *dd, int chave);
void destruir_dd(t_dd *dd);
void stats_dd(t_dd *dd);