/////////////////////////////////////////////////////////////////////////////////

#include "stat.h"
#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////

// Returns number of nodes in graph g.
int get_nodes(graph * g) {
	return g->nb_n;
}


// Returns the number of edges connceted to node u.
int get_degree_u(graph * g, int u) {
	int nb_e  = 0;
	for(int v = 0; v < get_nodes(g); v++) {
		if(g->g[u][v]) { // If v is a neighbor of u
			nb_e++;
		}
	}
	return nb_e;
}


// Returns the max degree of graph g.
int get_max_degree(graph * g) {
	int tmp = 0;
	for(int u = 0; u < get_nodes(g); u++) {
		int nb_e = get_degree_u(g, u);
		if(tmp < nb_e) {
			tmp = nb_e;
		}
	}
	return tmp;
}


// Returns the min degree of graph g.
int get_min_degree(graph * g) {
	int tmp = get_max_degree(g);
	for(int u = 0; u < get_nodes(g); u++) {
		int nb_e = get_degree_u(g, u);
		if(tmp > nb_e) {
			tmp = nb_e;
		}
	}
	return tmp;
}

// Creates an array (degrees) containing the degree for each vertex of graph g.
void get_degrees(graph * g, int * degrees) {
	degrees = (int *) calloc(get_nodes(g), sizeof(int));
	if(degrees ==  NULL) {
		printf("Cannot allocate enough memory for degrees array.\n");
		exit(1);
	}

	for(int u = 0; u < get_nodes(g); u++) {
		degrees[u] = get_degree_u(g, u);
	}
}




/////////////////////////////////////////////////////////////////////////////////




// Sub-fonction of is_acyclic - It behaves like Depth-First Search.
int visit_v_acy(graph * g, int * visited, int u) {
	if(!visited[u]) {
		visited[u] = 1;
		for(int v = 0; v < get_nodes(g); v++) {
			if(g->g[u][v]) {  // If v is one of u neighbors
				return visit_v_acy(g, visited, v);
			}
		}
	}
	return 0;
}


// Returns whether g is acyclic or not.
int is_acyclic(graph * g) {
	int * visited = (int *) calloc(get_nodes(g), sizeof(int));
	if(visited == NULL) {
		printf("Cannot allocate enough memory for visited array.\n");
		return 0;
	}
	for(int u = 0; u < get_nodes(g); u++) {
		if(!visit_v_acy(g, visited, u)) {
			return 0;
		}
	}
	return 1;
}





//////////////////////////////////////////////////////////////////////////////////





// Sub-function of cluster_search that visites neighbors of node u.
void visit_v(graph * g, int * visited, int u, vertices ** l_vert) {
	if(!visited[u]) {
		visited[u] = 1;
		append_vertices(l_vert, u); // if u is part of the current l_vert cluster
		for(int v = 0; v < get_nodes(g); v++) { // Looping through u neighbors
			if(g->g[u][v]) visit_v(g, visited, v, l_vert);
		}
	}
}


/*
	void cluster_search(graph * g, cluster ** clus);
	--
	Performs a Depth-First Search on g until
	every vertices are visited. Then returns
	each cluster (if exists) in *clus.
	(a linked-list of linked-list structure).
	--
	Function must be called with clus as NULL pointer.
*/
void cluster_search(graph * g, cluster ** clus) {
	int * visited = (int *) calloc(g->nb_n, sizeof(int)); // Inits the whole array to zero
	if(visited == NULL) {
		printf("Cannot allocate enough memory for visited array.\n");
		exit(1);
	}

	vertices * l_vert = NULL; // New cluster

	for(int u = 0; u < get_nodes(g); u++) {
		visit_v(g, visited, u, &l_vert);
		if(l_vert != NULL) {
			append_cluster(clus, &l_vert); // Adding the l_vert cluster to the cluster list
			l_vert = NULL; //  New cluster
		}
	}
}




///////////////////////////////////////////////////////////////////////////////////////////////////




// Returns the max element in array. Its index is stored in *ind.
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


// Sub-function from longest_path_u - Computes the distance from u to v
void distance_update(int * distance, int * u_path, queue ** q, int mode, int v_s, int u, int v) {
	if(!mode || mode == v_s) { // Whole curriculum mode := 0
		distance[v] = distance[u] + 1;
		u_path[v] = u;
		append_queue(q, v);
	} else if(mode <= 3) { // Year mode := 1, 2 or 3
		if(v_s == 2*mode-1 || v_s == 2*mode) {
			distance[v] = distance[u] + 1;
			u_path[v] = u;
			append_queue(q, v);
		}
	}
}


/*
-------------------------------------------------------------------------
	Returns the length of the longest path from vertex u
	and creates the path to the farthest vertex in path
	linked-list. It relies on Breadth-First Search.
	--
	You can choose to consider specific parts of the graph
	either a specific year, even semester or the whole
	curriculmum.
	--
	mode :=  {0 : whole curriculum, 1-3 : year mode or 5-10 : semester}.
-------------------------------------------------------------------------
*/
int longest_path_u(graph * g, int u, int mode, queue ** path) {
	// Distance from each node of graph g to u
	int * distance = (int *) malloc(get_nodes(g) * sizeof(int));
	if(distance == NULL) {
		printf("Cannot allocate enough memory for distance array.\n");
		return -1;
	}

	// Predecessor of each node considering it starts from vertex u
	int * u_path = (int *) malloc(get_nodes(g) * sizeof(int));
	if(u_path == NULL) {
		printf("Cannot allocate enough memory.\n");
		return -1;
	}

	for(int v = 0; v < get_nodes(g); v++) {
		distance[v] = (u == v) ? 0 : -1;
		u_path[v] = (u == v) ? u : 0;
	}

	queue * q = NULL;
	append_queue(&q, u);

	// Computes all shortest path from v
	while(q != NULL) {
		int u = pop_queue(&q);
		for(int v = 0; v < get_nodes(g); v++) {
			if(g->g[u][v]) {  // If v is one of u neighbors
				int v_s = g->g[u][v].x; // v semester
				if(distance[v] == -1) { // if vertex u is not visited
					distance_update(distance, u_path, &q, mode, v_s, u, v);
				}
			}
		}
	}

	int maxi, i_maxi;
	maxi = max_array(distance, get_nodes(g), &i_maxi);
	while(i_maxi != u) { // Copying the max path to path
		append_queue(path, i_maxi);
		i_maxi = u_path[i_maxi];
	}
	append_queue(path, u);

	return maxi;
}


/*
	Returns a list of the longest path for each vertex of graph g.
	--
	Function must be called with path as NULL pointer.
*/
int longest_path(graph * g, queue ** path, int mode) {
	// Array of path from each node to its farthest neighbor
	path = (queue **) malloc(get_nodes(g) * sizeof(queue *));
	if(path == NULL) {
		printf("Cannot allocate enough memory for path linked-list.\n");
		exit(1);
	}
	
	// Used to check whether or not a vertex is already the farthest path from a node
	int * is_longest_path = (int *) malloc(get_nodes(g) * sizeof(int));
	if(is_longest_path == NULL) {
		printf("Cannot allocate enough memory.\n");
		exit(1);
	}

	for(int u = 0; u < get_nodes(g); u++) {
		path[u] = NULL;
		is_longest_path[u] = -1;
	}


	int max_path = 0; // Max-path length

	for(int u = 0; u < get_nodes(g); u++) {
		// If the considered vertex is not an already farthest vertex from a previously considered one
		if(is_longest_path[u] == -1) {
			int tmp = longest_path_u(g, u, mode, &(path[u]));
			is_longest_path[path[u]->key] = u; // Vertex path[u]->key is the farthest from u
			if(tmp > max_path) {
				max_path = tmp;
			}
		} else {
			path[u] = path[is_longest_path[u]];
		}
	}
	return max_path;
}

/////////////////////////////////////////////////////////////////////////////////