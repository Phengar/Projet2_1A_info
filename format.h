typedef struct _UP{
    unsigned char name;
    int semestre;
    int id;
    struct _UP * next;
}UP;

typedef struct{
    int nb_n; //nb of nodes
    int nb_e; //nb of edges
    UP ** g;
}graph;