/////////////////////////////////////////////////////////////////////////////////

#include "stat.h"
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/////////////////////////////////////////////////////////////////////////////////

// Returns number of nodes in mat_adj g.
int get_nodes(mat_adj * g) {
	return g[0].nb_n;
}


// Returns the number of UP in mat_adj g.
int get_UP(mat_adj * g) {
	int nb_UP = 0;
	for(int u = 0; u < get_nodes(g); u++) {
		// If name[1] belongs to ASCII(a-z).
		if(g[u].name[1] >= 97) nb_UP++;
	}
	return nb_UP;
}


// Returns the number of UP in a given semester.
int get_UP_semester(mat_adj * g, int semester) {
	int nb_UP = 0;
	for(int u = 0; u < get_nodes(g); u++) {
		if(g[u].name[1] >= 97 && g[u].x == semester-4) nb_UP++;
	}
	return nb_UP;
}


// Returns the number of UP in a given year.
int get_UP_year(mat_adj * g, int year) {
	return get_UP_semester(g, 2*year+3) + get_UP_semester(g, 2*year+4);
}


// Returns the number of GP in mat_adj g.
int get_GP(mat_adj * g) {
	return get_nodes(g)  - get_UP(g);
}


// Returns the number of GP in a given semester.
int get_GP_semester(mat_adj * g, int semester) {
	int nb_GP = 0;
	for(int u = 0; u < get_nodes(g); u++) {
		// If g[u].name[1] belongs to ASCII(A-Z).
		if(g[u].name[1] <= 90 && g[u].x == semester-4) nb_GP++;
	}
	return nb_GP;
}


// Returns the number of GP in a given year.
int get_GP_year(mat_adj * g, int year) {
	return get_GP_semester(g, 2*year+3) + get_GP_semester(g, 2*year+4);
}


// Returns the number of edges connceted to node u.
int get_degree_u(mat_adj * g, int u) {
	int nb_child  = 0;
	for(int v = 0; v < get_nodes(g); v++) {
		if(g[u].list[v]) { // If v is a neighbor of u
			nb_child++;
		}
	}
	return nb_child;
}


// Returns the max degree of mat_adj g
// and puts its index at ind_max.
int get_max_degree(mat_adj * g, int * id_max) {
	int tmp = 0;
	for(int u = 0; u < get_nodes(g); u++) {
		int nb_child = get_degree_u(g, u);
		if(tmp < nb_child) {
			tmp = nb_child;
			*id_max = u;
		}
	}
	return tmp;
}


// Returns the min degree of mat_adj g
// and puts its index at ind_min.
int get_min_degree(mat_adj * g, int * id_min) {
	int tmp = get_max_degree(g, id_min);
	for(int u = 0; u < get_nodes(g); u++) {
		int nb_child = get_degree_u(g, u);
		if(tmp > nb_child) {
			tmp = nb_child;
			*id_min = u;
		}
	}
	return tmp;
}


// Creates an array (degrees) containing the degree for each vertex of mat_adj g.
void get_degrees(mat_adj * g, int * degrees) {
	for(int u = 0; u < get_nodes(g); u++) {
		degrees[u] = get_degree_u(g, u);
	}
}


// Prints the top n nodes with the highest degrees.
void print_top_degrees(int * degrees, int nb_n, int n) {

}




/////////////////////////////////////////////////////////////////////////////////


// Prints an array of integer of length length.
void print_array(int * array, int length) {
	for(int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}




/////////////////////////////////////////////////////////////////////////////////




// Sub-fonction of is_acyclic - It behaves like Depth-First Search.
int visit_v_acy(mat_adj * g, int * visited, int u) {
	if(!visited[u]) {
		visited[u] = 1;
		for(int v = 0; v < get_nodes(g); v++) {
			if(g[u].list[v]) {  // If v is one of u neighbors
				return visit_v_acy(g, visited, v);
			}
		}
	}
	return 0;
}


// Returns whether g is acyclic or not.
int is_acyclic(mat_adj * g) {
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
void visit_v(mat_adj * g, int * visited, int u, cluster ** list) {
	if(!visited[u]) {
		visited[u] = 1;
		append_cluster_key(list, u); // if u is part of the current l_vert cluster
		for(int v = 0; v < get_nodes(g); v++) { // Looping through u neighbors
			if(g[u].list[v]) visit_v(g, visited, v, list);
		}
	}
}


/*
	void cluster_search(mat_adj * g, cluster ** clus);
	--
	Performs a Depth-First Search on g until
	every vertices are visited. Then returns
	each cluster (if exists) in *clus.
	(a linked-list of linked-list structure).
	--
	Function must be called with clus as NULL pointer.
*/
void cluster_search(mat_adj * g, cluster ** clus) {
	int * visited = (int *) calloc(get_nodes(g), sizeof(int)); // Inits the whole array to zero
	if(visited == NULL) {
		printf("Cannot allocate enough memory for visited array.\n");
		exit(1);
	}

	for(int u = 0; u < get_nodes(g); u++) {
		append_cluster_list(clus);
		visit_v(g, visited, u, &((*clus)->list));
		if((*clus)->list == NULL) pop_cluster(clus);
	}
}




///////////////////////////////////////////////////////////////////////////////////////////////////




// Returns the max element in array. Its index is stored in *ind.
int max_array(int * array, int length, int * ind) {
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


// Sub-function from longest_path_u - Computes the distance from u to v
void distance_update(int * distance, int * u_path, queue ** q, int mode, int v_s, int u, int v) {
	if(!mode || mode == v_s) { // Whole curriculum mode := 0
		distance[v] = distance[u] + 1;
		u_path[v] = u;
		append_queue(q, v); // Adds v to the visiting queue
	} else if(0 < mode && mode <= 3) { // Year mode := 1, 2 or 3
		if(v_s == 2*mode+3 || v_s == 2*mode+4) {
			distance[v] = distance[u] + 1;
			u_path[v] = u;
			append_queue(q, v); // Adds v to the visiting queue
		}
	}
}


/*

	Returns the length of the longest path from vertex u
	and creates the path to the farthest vertex in path
	linked-list. It relies on Breadth-First Search.
	--
	You can choose to consider specific parts of the mat_adj
	either a specific year, even semester or the whole
	curriculmum.
	--
	mode :=  {0 : whole curriculum, 1-3 : year mode or 5-10 : semester}.

*/
int longest_path_u(mat_adj * g, int u, int mode, queue ** path) {
	// Distance from each node of mat_adj g to u
	int * distance = (int *) malloc(get_nodes(g) * sizeof(int));
	// Predecessor of each node considering it starts from vertex u
	int * u_path = (int *) malloc(get_nodes(g) * sizeof(int));
	if(distance == NULL || u_path == NULL) {
		printf("Cannot allocate enough memory for either distance array or u_path array.\n");
		return -1;
	}

	for(int v = 0; v < get_nodes(g); v++) {
		distance[v] = -1;
		u_path[v] = -1;
	}

	distance[u] = 0;
	u_path[u] = u;

	queue * q = NULL;
	append_queue(&q, u);
	int size = 1;

	// Computes all shortest path from v
	while(q != NULL) {
		int v_s; // Semester number of node v
		int u = pop_queue(&q);
		int unv = g[u].nb_child;
		for(int v = 0; v < get_nodes(g); v++) {
			printf("u : %d - unv : %d - v : %d.\n", u, unv, v);
			// If v is one of u neighbors and vertex v is not visited
			if(g[u].list[v] && distance[v] == -1) {
				printf("v : %d - v_s : %d.\n", v, g[v].x);
				v_s = g[v].x; // v semester number
				// Either curriculum mode := 0, or semester mode
				if(!mode || mode == v_s) {
					distance[v] = distance[u] + 1;
					u_path[v] = u;
					append_queue(&q, v); // Adds v to the visiting queue
					size++;
				// Year mode := 1, 2 or 3
				} else if(1 <= mode && mode <= 3) {
					if(v_s == 2*mode+3 || v_s == 2*mode+4) {
						distance[v] = distance[u] + 1;
						u_path[v] = u;
						append_queue(&q, v); // Adds v to the visiting queue
						size++;
					}
				}
				printf("Queue length : %d.\n", size);
				unv--;
			}
		}
	}

	int maxi;
	int i_maxi = 0;
	maxi = max_array(distance, get_nodes(g), &i_maxi);
	if(maxi == -1) exit(1); // Error catching
	while(i_maxi != u) { // Copying the max path to path
		append_queue(path, i_maxi);
		i_maxi = u_path[i_maxi];
	}
	append_queue(path, u);

	return maxi;
}


/*
	Returns a list of the longest path for each vertex of mat_adj g.
	--
	mode :=  {0 : whole curriculum, 1-3 : year mode or 5-10 : semester}.
*/
int longest_path(mat_adj * g, queue ** path, int mode) {
	int max_path = 0; // Max-path length
	for(int u = 0; u < get_nodes(g); u++) {
		int tmp = longest_path_u(g, u, mode, &(path[u]));
		if(tmp > max_path) {
			max_path = tmp;
		}
	}
	return max_path;
}

/////////////////////////////////////////////////////////////////////////////////