/////////////////////////////////////////////////////////////////////////////////

/*
	File that contains the whole analysis of the ISMIN syllabus graph
	--
	DAVAL Quentin - Benjamin Hubinet
	ISMIN 1A - EI21
*/

/////////////////////////////////////////////////////////////////////////////////

#ifndef STAT_H_ // Include guards
#define STAT_H_

/////////////////////////////////////////////////////////////////////////////////

#include "format.h"

/////////////////////////////////////////////////////////////////////////////////

// Returns number of nodes in mat_adj g.
int get_nodes(mat_adj * g);

// Returns the number of UP in mat_adj g.
int get_UP(mat_adj * g);

// Returns the number of UP in a given semester.
int get_UP_semester(mat_adj * g, int semester);

// Returns the number of UP in a given year.
int get_UP_year(mat_adj * g, int year);

// Returns the number of GP in mat_adj g.
int get_GP(mat_adj * g);

// Returns the number of GP in a given semester.
int get_GP_semester(mat_adj * g, int semester);

// Returns the number of GP in a given year.
int get_GP_year(mat_adj * g, int year);

////////////////////////////////////////////////////////////////////////

// Returns the GP array (its length is *length).
int * get_GP_array(mat_adj * g, int * length);

// Creates the sorted array(degrees) of degree for each GP in gp_arr.
void get_degrees_GP(mat_adj * g, int * gp_arr, int length, int * degrees);

// Prints the top n GP of g with the highest GP degree.
void print_top_degrees_GP(mat_adj * g, int * gp_arr, int * degrees, int length, int n);

////////////////////////////////////////////////////////////////////////

// Returns the number of edges connceted to node u.
int get_degree_u(mat_adj * g, int u);

// Returns the max degree of mat_adj g.
// and puts its index at ind_max.
int get_max_degree(mat_adj * g, int * id_max);

// Returns the min degree of mat_adj g
// and puts its index at ind_min.
int get_min_degree(mat_adj * g, int * id_min);

// Creates an array (degrees) containing the degree for each vertex of mat_adj g.
void get_degrees(mat_adj * g, int * degrees);

// Prints the top n nodes with the highest degrees.
// nb_n is the number of nodes in the graph
void print_top_degrees(int * degrees, mat_adj * g, int n);

/////////////////////////////////////////////////////////////////////////////////

// Prints an array of integer of length length.
void print_array(int * array, int length);

/////////////////////////////////////////////////////////////////////////////////


// Sub-fonction of is_acyclic - It behaves like Depth-First Search.
int visit_v_acy(mat_adj * g, int * visited, int u);

// Returns whether g is acyclic or not.
int is_acyclic(mat_adj * g);


/////////////////////////////////////////////////////////////////////////////////


// Sub-function of cluster_search that visites neighbors of node u.
void visit_v(mat_adj * g, int * visited, int u, cluster ** list);

/*
	void cluster_search(mat_adj * g, cluster ** clus);
	--
	Performs a Depth-First Search on g until
	every vertices are visited. Then returns
	each cluster (if exists) in *clus.
	(a linked-list of linked-list structure). 
*/
void cluster_search(mat_adj * g, cluster ** clus);


/////////////////////////////////////////////////////////////////////////////////


// Returns the max element in array. Its index is stored in *ind.
int max_array(int * array, int length, int * ind);

// Sub-function from longest_path_u - Computes the distance from u to v
void distance_update(int * distance, int * v_path, queue ** q, int mode, int v_s, int u, int v);

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
int longest_path_u(mat_adj * g, int u, int mode, queue ** path);


/*
	Returns a list of the longest path for each vertex of mat_adj g.
	--
	mode :=  {0 : whole curriculum, 1-3 : year mode or 5-10 : semester}.
*/
int longest_path(mat_adj * g, queue ** path, int mode);

/////////////////////////////////////////////////////////////////////////////////

#endif

/////////////////////////////////////////////////////////////////////////////////