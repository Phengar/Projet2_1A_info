/////////////////////////////////////////////////////////////////////////////////

/*
    Data format definition file
    --
    DAVAL Quentin - HUBINET Benjamin
    ISMIN 1A - EI21
*/

/////////////////////////////////////////////////////////////////////////////////

#ifndef FORMAT_H_ // Include guards
#define FORMAT_H_

/////////////////////////////////////////////////////////////////////////////////

#define MAX_LENGTH 100

/////////////////////////////////////////////////////////////////////////////////

// UP data structure
typedef struct _UP {
    int id; // Unique identifier that corresponds to its row number in nodes.csv
    char name[MAX_LENGTH]; // UP name
    int x; // UP occuring semester
    int y; // UP identifier within the semester
} UP;


typedef struct _node{
    UP element;
    int GP;
    int index;
    struct _node * next;
} node;


typedef struct {
    UP;
    int * list;
} mat_adj;


// Graph structure : adjacency list
typedef struct{
    int nb_n; //nb of nodes
    int nb_e; //nb of edges
    UP ** g;
} graph;

/////////////////////////////////////////////////////////////////////////////////
/*
    
    Vertices structure - (inherent to cluster structure) - Linked-list

*/

typedef struct _vert {
    int vertex;
    struct _vert * next;
} vertices;

void append_vertices(vertices ** l_vert, int vertex);

void pop_vertices(vertices ** l_vert);

void print_vertices(vertices ** l_vert);


/*

    Cluster structure - Linked-list of vertices

*/

typedef struct _clus {
    vertices  ** l_vert;
    struct _clus * next;
} cluster ;


void append_cluster(cluster ** clus, vertices ** l_vert);

void pop_cluster(cluster ** clus);

void print_cluster(cluster ** clus);

/////////////////////////////////////////////////////////////////////////////////

// Queue structure
typedef struct _queue {
    struct _queue * next;
    int key;
} queue;

void append_queue(queue ** q, int key);

// Pops and returns top queue key
int pop_queue(queue ** q);

void print_queue(queue ** q);

/////////////////////////////////////////////////////////////////////////////////

#endif

/////////////////////////////////////////////////////////////////////////////////