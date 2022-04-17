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

/*
// UP data structure
typedef struct _UP {
    int id; // Unique identifier that corresponds to its row number in nodes.csv
    char name[MAX_LENGTH]; // UP name
    int x; // UP occuring semester
    int y; // UP identifier within the semester
} UP;


typedef struct _node {
    UP element;
    int GP;
    int index;
    struct _node * next;
} node;*/


// Graph structure : adjacency matrix
typedef struct {
    int nb_n;
    int id;
    int x;
    int y;
    char name[MAX_LENGTH];
    int nb_child;
    int * list;
} mat_adj;

// Transforms the graph g represented as an
// adjacency matrix into a graph de précédence
void adj_to_pre(mat_adj * g, mat_adj ** gp);

/////////////////////////////////////////////////////////////////////////////////
/*/*
    
    Vertices structure - (inherent to cluster structure) - Linked-list



typedef struct _vert {
    int vertex;
    struct _vert * next;
} vertices;

void append_vertices(vertices ** l_vert, int vertex);

void pop_vertices(vertices ** l_vert);

void print_vertices(vertices ** l_vert);*/


/*

    Cluster structure
    --
    Linked-list of linked-list of vertices
    --
    Which you can also consider as a main-list
    whose elements are list of vertices forming
    a cluster.

*/

typedef struct _clus {
    int key;
    struct _clus * list;
    struct _clus * next;
} cluster ;

// Adds a new cluster into the cluster main-list
void append_cluster_list(cluster ** clus);

// Adds a key in the considered cluster list
void append_cluster_key(cluster ** clus, int key);

// Pops from cluster main-list head
void pop_cluster(cluster ** clus);

// Prints the cluster elements
void print_cluster(mat_adj * g, cluster ** clus);

/////////////////////////////////////////////////////////////////////////////////

// Queue data structure
typedef struct _queue {
    struct _queue * next;
    int key;
} queue;

void append_queue(queue ** q, int key);

// Pops and returns from queue head
int pop_queue(queue ** q);

// Prints queue elements
void print_queue(queue ** q);

/////////////////////////////////////////////////////////////////////////////////

#endif

/////////////////////////////////////////////////////////////////////////////////