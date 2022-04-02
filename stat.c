/////////////////////////////////////////////////////////////////////////////////

#include "stat.h"
#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////

int get_nodes(graph * g) {
	return g->nb_n;
}

int get_edges(graph * g) {
	return g->nb_e;
}

int get_max_degree(graph * g) {
	int tmp = 0;
	for(int i = 0; i < get_nodes(g); i++) {
		if(tmp < g->g[i][0].id) { // Don't mind : ->id : for test only
			tmp = g->g[i][0].id;
		}
	}
	return tmp;
}

int get_min_degree(graph * g) {
	int tmp = get_max_degree(g);
	for(int i = 0; i < get_nodes(g); i++) {
		if(tmp > g->g[i][0].id) { // Don't mind : .id : for test only
			tmp = g->g[i][0].id;
		}
	}
	return tmp;
}

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//

int visit_v_acy(graph * g, int * visited, int v) {
	if(!visited[v]) {
		for(int vv = 1; vv <= g->g[v][vv].id; v++) {
			visited[v] = 1;
			return visit_v_acy(g, visited, g->g[v][vv].id);
		}
	}
	return 0;
}

int is_acyclic(graph * g) {
	int * visited = (int *) calloc(g->nb_n, sizeof(int));
	if(visited == NULL) {
		printf("Cannot allocate enough memory for visited array.\n");
		return 0;
	}
	for(int v = 0; v < g->nb_n; v++) {
		if(!visit_v_acy(g, visited, v)) {
			return 0;
		}
	}
	return 1;
}

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//

void visit_v(graph * g, int * visited, int v, vertices ** l_vert) {
	if(!visited[v]) {
		visited[v] = 1;
		append_vertices(l_vert, v); // v is part of the current l_vert cluster
		for(int vv = 1; vv <= g->g[v][0].id; vv++) { // Don't mind : .id : for test only
			visit_v(g, visited, g->g[v][vv].id, l_vert); // Don't mind : .id fot test only
		}
	}
}

void cluster_search(graph * g, cluster ** clus) {
	int * visited = (int *) calloc(g->nb_n, sizeof(int)); // Inits the whole array to zero
	if(visited == NULL) {
		printf("Cannot allocate enough memory for visited array.\n");
		return;
	}

	vertices * l_vert = NULL; // New cluster

	for(int v = 0; v < g->nb_n; v++) {
		visit_v(g, visited, v, &l_vert);
		append_cluster(clus, &l_vert); // Adding the l_vert cluster to the cluster list
		l_vert = NULL; // New cluster
	}
}

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//

int max_array(int * array, int length, int * ind) {
	if(length == 0) {
		int m = array[0];
		*ind = 0;
		for(int i = 1; i < length; i++) {
			if(m < array[i]) {
				m = array[i];
				*ind = i;
			}
		}
		return m;
	}
	printf("Array is empty.\n");
	return -1;
}

void distance_update(int * distance, int * v_path, queue ** q, int mode, int u, int us, int s) {
	if(!mode) { // Whole curriculum mode
		distance[u] = distance[s] + 1;
		v_path[u] = s;
		append_queue(q, u);
	} else if(mode <= 3) { // Year mode
		if(us == 2*mode-1 || us == 2*mode) {
			distance[u] = distance[s] + 1;
			v_path[u] = s;
			append_queue(q, u);
		}
	} else if(mode == us) {
		distance[u] = distance[s] + 1;
		v_path[u] = s;
		append_queue(q, u);
	}
}

// Returns the length of the longest path from v
// Computes the path in path

int longest_path_v(graph * g, int v, int mode, queue ** path) {
	int * distance = (int *) malloc((g->nb_n) * sizeof(int));
	if(distance == NULL) {
		printf("Cannot allocate enough memory for distance array.\n");
		return -1;
	}
	for(int i = 0; i < g->nb_n; i++) {
		distance[i] = (i == v) ? 0 : -1;
	}

	int * v_path = (int *) calloc(g->nb_n, sizeof(int));
	if(path == NULL) {
		printf("Cannot allocate enough memory.\n");
		return -1;
	}
	v_path[v] = v;

	queue * q = NULL;
	append_queue(&q, v);

	// Computes all shortest path from v
	while(q != NULL) {
		int s = pop_queue(&q);
		for(int vv = 1; vv <= g->g[s][0].id; vv++) {
			int u = g->g[s][vv].id;
			int us = g->g[s][vv].semestre;
			if(distance[u] == -1) { // if vertex u is not visited
				distance_update(distance, v_path, &q, mode, u, us, s);
			}
		}
	}

	int maxi, i_maxi;
	maxi = max_array(distance, g->nb_n, &i_maxi);
	while(i_maxi != v) {
		append_queue(path, i_maxi);
		i_maxi = v_path[i_maxi];
	}
	append_queue(path, v);

	return maxi;
}

/////////////////////////////////////////////////////////////////////////////////