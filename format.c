/////////////////////////////////////////////////////////////////////////////////

#include "format.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////////

/*/*

	Vertices structure - (inherent to cluster structure) - Linked-list



void append_vertices(vertices ** l_vert, int vertex) {
    vertices * tmp = (vertices *) malloc(sizeof(vertices));
    if(tmp == NULL) {
        printf("Cannot allocate enough memory for vertices.\n");
        exit(1);
    }
    tmp->vertex = vertex;
    tmp->next = *l_vert;
    *l_vert = tmp;
}

void pop_vertices(vertices ** l_vert) {
    if(*l_vert != NULL) {
        vertices * tmp  = *l_vert;
        *l_vert = (*l_vert)->next;
        free(tmp);
    }
}

void print_vertices(vertices ** l_vert) {
    vertices * tmp = *l_vert;
    while(tmp != NULL) {
        printf("%d ", tmp->vertex);
        tmp = tmp->next;
    }
    printf("\n");
}*/

/////////////////////////////////////////////////////////////////////////////////
/*

	Cluster structure
    --
    Linked-list of linked-list of vertices
    --
    Which you can also consider as a main-list
    whose elements are list of vertices forming
    a cluster.

*/

// Adds a new cluster into the cluster main-list
void append_cluster_list(cluster ** clus) {
    cluster *  tmp = (cluster *) malloc(sizeof(cluster));
    if(tmp == NULL) {
        printf("Cannot allocate enough memory for a new cluster.\n");
        exit(1);
    }
    tmp->key = -1;
    tmp->list = NULL;
    tmp->next = *clus;
    *clus = tmp;
}

// Adds a key in the considered cluster list
void append_cluster_key(cluster ** clus, int key) {
    cluster * tmp = (cluster *) malloc(sizeof(cluster));
    if(tmp == NULL) {
        printf("Cannot allocate enough memory for a new cluster element.\n");
        return;
    }

    tmp->key = key;
    tmp->list = *clus;
    tmp->next = NULL;
    *clus = tmp;
}

// Pops from cluster main-list head
void pop_cluster(cluster ** clus) {
    if(*clus != NULL) {
    	cluster * tmp = *clus;
    	*clus = (*clus)->next;
    	free(tmp);
    }
}

// Prints the cluster elements
void print_cluster(mat_adj * g, cluster ** clus) {
	cluster * tmp = *clus;
	int i = 0;
	while(tmp != NULL) {
		printf("%d  ->  ", i);
		cluster * cur = tmp->list;
        while(cur != NULL) {
            printf("%s, ", g[cur->key].name);
            cur = cur->list;
        }
        printf("\n");
		tmp = tmp->next;
		i++;
	}
}

/////////////////////////////////////////////////////////////////////////////////
/*
    Queue data structure
*/

// Appends key to queue tail
void append_queue(queue ** q, int key) {
    queue * tmp = (queue *) malloc(sizeof(queue));
    if(tmp == NULL) {
    	printf("Cannot allocate enough memory for queue.\n");
    	exit(1);
    }
    tmp->key = key;
    tmp->next = NULL;

    if(*q == NULL) {
    	*q = tmp;
    	return;
    }

    queue * cur = *q;
    while(cur != NULL) {
    	if(cur->next == NULL) {
    		cur->next = tmp;
    	}
    	cur = cur->next;
    }
}

// Pops from queue head
int pop_queue(queue ** q) {
	if(*q != NULL) {
		queue * tmp = *q;
		int tmp_key = tmp->key;
		*q = (*q)->next;
		free(tmp);
		return tmp_key;
	}
}

// Prints queue elements
void print_queue(queue ** q) {
	queue * tmp = *q;
	while(tmp != NULL) {
		printf("%d ", tmp->key);
		tmp = tmp->next;
	}
	printf("\n");
}

/////////////////////////////////////////////////////////////////////////////////