/////////////////////////////////////////////////////////////////////////////////
#include "format.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////////
/*

	UP structure

*/


void append_UP(UP ** ups, char * name, int semestre, int id) {
	UP * tmp = (UP *) malloc(sizeof(UP));
	if(tmp == NULL) {
		printf("Cannot allocate enough memory to UP.\n");
		return;
	}
	strcpy(tmp->name, name);
	tmp->semestre = semestre;
	tmp->id = id;
	tmp->next = *ups;
	*ups = tmp;
}

void pop_UP(UP ** ups) {
	if(*ups != NULL) {
		UP * tmp = *ups;
		*ups = (*ups)->next;
		free(tmp);
	}
}

void print_UP(UP ** ups) {
	UP * tmp = *ups;
	while(tmp != NULL) {
		printf("(name: %s, semester: %d, id: %d) ", tmp->name, tmp->semestre, tmp->id);
		tmp = tmp->next;
	}
	printf("\n");
}

/////////////////////////////////////////////////////////////////////////////////
/*

	vertices structure - (inherent to cluster structure)

*/

void append_vertices(vertices ** l_vert, int vertex) {
    vertices * tmp = (vertices *) malloc(sizeof(vertices));
    if(tmp == NULL) {
        printf("Cannot allocate enough memory for vertices.\n");
        return;
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
}

/////////////////////////////////////////////////////////////////////////////////
/*

	cluster structure

*/


void append_cluster(cluster ** clus, vertices ** l_vert) {
    cluster *  tmp = (cluster *) malloc(sizeof(cluster));
    if(tmp == NULL) {
        printf("Cannot allocate enough memory for cluster.\n");
        return;
    }
    tmp->l_vert = l_vert;
    tmp->next = *clus;
    *clus = tmp;
}

void pop_cluster(cluster ** clus) {
    if(*clus != NULL) {
    	cluster * tmp = *clus;
    	*clus = (*clus)->next;
    	free(tmp);
    }
}

void print_cluster(cluster ** clus) {
	cluster * tmp = *clus;
	int i = 0;
	while(tmp != NULL) {
		printf("%d  ->  ", i);
		print_vertices(tmp->l_vert);
		tmp = tmp->next;
		i++;
	}
	printf("\n");
}

/////////////////////////////////////////////////////////////////////////////////

void append_queue(queue ** q, int key) {
    queue * tmp = (queue *) malloc(sizeof(queue));
    if(tmp == NULL) {
    	printf("Cannot allocate enough memory for queue.\n");
    	return;
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

int pop_queue(queue ** q) {
	if(*q != NULL) {
		queue * tmp = *q;
		int tmp_key = tmp->key;
		*q = (*q)->next;
		free(tmp);
		return tmp_key;
	}
}

void print_queue(queue ** q) {
	queue * tmp = *q;
	while(tmp != NULL) {
		printf("%d ", tmp->key);
		tmp = tmp->next;
	}
	printf("\n");
}

/////////////////////////////////////////////////////////////////////////////////