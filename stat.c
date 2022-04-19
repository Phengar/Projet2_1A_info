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


// Returns the GP array (its length is *length).
int * get_GP_array(mat_adj * g, int * length) {
	*length = get_GP(g);
	int * gp_arr = (int *) malloc((*length) * sizeof(int));
	if(gp_arr == NULL) {
		printf("Cannot allocate enough memory for GP array.\n");
		exit(1);
	}
	int cur = 0;
	for(int u = 0; u < get_nodes(g); u++) {
		// If u is a GP
		if(g[u].name[1] <= 90) {
			gp_arr[cur] = u;
			cur++;
		}
	}
	return gp_arr;
}

// Creates the sorted array(degrees) of degree for each GP in gp_arr.
void get_degrees_GP(mat_adj * g, int * gp_arr, int length, int * degrees) {
	for(int i = 0; i < length; i++) {
		for(int u = 0; u < get_nodes(g); u++) {
			// If u is oneof gp_arr[i] neighbors and u is a GP
			if(g[gp_arr[i]].list[u] && g[u].name[1] <= 90) {
				degrees[i]++;
			}
		}
	}
	quick_sort(degrees, gp_arr, length);
}


// Prints the top n GP of g with the highest GP degree.
void print_top_degrees_GP(mat_adj * g, int * gp_arr, int * degrees, int length, int n) {
	if(n > length) {
		return;
	}
	printf("Top %d GP with the higest GP degree :\n", n);
	for(int i = 0; i < n; i++) {
		printf("%d : %s - degree : %d\n", i+1, g[gp_arr[i]].name, degrees[i]);
	}
}


// Returns the number of edges connceted to node u.
int get_degree_u(mat_adj * g, int u) {
	/*int nb_child  = 0;
	for(int v = 0; v < get_nodes(g); v++) {
		if(g[u].list[v]) { // If v is a neighbor of u
			nb_child++;
		}
	}
	return nb_child;*/
	return g[u].nb_child;
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
void print_top_degrees(int * degrees, mat_adj * g, int n) {
	if(n > get_nodes(g)) {
		return;
	}
	int * index = (int *) malloc(get_nodes(g) * sizeof(int));
	if(index == NULL) {
		printf("Cannot allocate enough memory.\n");
		exit(1);
	}
	for(int u = 0; u < get_nodes(g); u++) {
		index[u] = u;
	}
	quick_sort(degrees, index, get_nodes(g));
	printf("Top %d vertices with the highest degree :\n", n);
	for(int i = 0; i < n; i++) {
		printf("%d : %s - degree : %d.\n", i+1, g[index[i]].name, degrees[i]);
	}
	free(index);
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
	free(visited);
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
	free(visited);
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
	
	int uu; // Considered node
	int v_s; // Semester number of node v


	// Computes all shortest path from v
	while(q != NULL) {
		uu = pop_queue(&q);
		for(int v = 0; v < get_nodes(g); v++) {
			// If v is one of u neighbors and vertex v is not visited
			if(g[uu].list[v] && distance[v] == -1) {
				v_s = g[v].x; // v semester number
				// Either curriculum mode := 0, or semester mode
				if(!mode || mode == v_s) {
					distance[v] = distance[uu] + 1;
					u_path[v] = uu;
					append_queue(&q, v); // Adds v to the visiting queue
				// Year mode := 1, 2 or 3
				} else if(1 <= mode && mode <= 3) {
					if(v_s == 2*mode+3 || v_s == 2*mode+4) {
						distance[v] = distance[uu] + 1;
						u_path[v] = uu;
						append_queue(&q, v); // Adds v to the visiting queue
					}
				}
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
	free(distance);
	free(u_path);
	return maxi;
}


/*
	Returns a list of the longest path for each vertex of mat_adj g.
	--
	mode :=  {0 : whole curriculum, 1-3 : year mode or 5-10 : semester}.
*/
int longest_path(mat_adj * g, queue ** path, int mode) {
	int max_path = 0; // Max-path length
	int tmp; // Partial longest path
	for(int u = 0; u < get_nodes(g); u++) {
		tmp = longest_path_u(g, u, mode, &(path[u]));
		if(tmp > max_path) {
			max_path = tmp;
		}
	}
	return max_path;
}


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//


// Sub function of Quickest time (semester) to begin node u related subject.
int earliest_to_u_compute(mat_adj * g, int u, int * lookup) {
	int tmp_quick = 0;
	for(int v = 0; v < get_nodes(g); v++) {
		// If (v, u) edge exists in g
		if(g[v].list[u]) {
			if(lookup[v] == -1) {
				earliest_to_u_compute(g, v, lookup);
			}
			if(lookup[v] + g[v].list[u] > tmp_quick) {
				tmp_quick = lookup[v] + g[v].list[u];
			}
		}
	}
	lookup[u] = tmp_quick;
	return tmp_quick;
}


/*
	Quickest time (semester) to begin node u related subject.
*/
int earliest_to_u(mat_adj * g, int u) {
	int * lookup = (int *) malloc(get_nodes(g) * sizeof(int));
	if(lookup == NULL) {
		printf("Cannot allocate enough memory.\n");
		exit(1);
	}
	for(int v = 0; v < get_nodes(g); v++) {
		lookup[v] = -1;
	}
	int res = earliest_to_u_compute(g, u, lookup);
	free(lookup);
	return res;
}


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//


// Sub function of Latest time to take a specific subject u.
int latest_to_u_compute(mat_adj * g, int u, int duration, int * lookup) {
	int tmp_latest = duration;
	for(int v = 0; v < get_nodes(g); v++) {
		// If (u, v) edge exists
		if(g[u].list[v]) {
			if(lookup[v] == -1) {
				latest_to_u_compute(g, v, duration, lookup);
			}
			if(lookup[v] - g[u].list[v] < tmp_latest) {
				tmp_latest = lookup[v] - g[u].list[v];
			}
		}
	}
	lookup[u] = tmp_latest;
	return tmp_latest;
}


/*
	Latest semester to take a subject without disturbing the duration
	of the curriculum.
*/
int latest_to_u(mat_adj * g, int u, int duration) {
	int * lookup = (int *) malloc(get_nodes(g) * sizeof(int));
	if(lookup == NULL) {
		printf("Cannot allocate enough memory.\n");
		exit(1);
	}
	for(int v = 0; v < get_nodes(g); v++) {
		lookup[v] = -1;
	}
	int res = latest_to_u_compute(g, u, duration, lookup);
	free(lookup);
	return res;
}


/////////////////////////////////////////////////////////////////////////////////