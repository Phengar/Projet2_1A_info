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

// Returns number of nodes in graph g.
int get_vertices(graph * g);

// Returns the number of edges connceted to node u.
int get_degree_u(graph * g, int u);

// Returns the max degree of graph g.
int get_max_degree(graph * g);

// Returns the min degree of graph g.
int get_min_degree(graph * g);

// Creates an array (degrees) containing the degree for each vertex of graph g.
void get_degrees(graph * g, int * degrees);

/////////////////////////////////////////////////////////////////////////////////


// Sub-fonction of is_acyclic - It behaves like Depth-First Search.
int visit_v_acy(graph * g, int * visited, int u);

// Returns whether g is acyclic or not.
int is_acyclic(graph * g);


/////////////////////////////////////////////////////////////////////////////////


// Sub-function of cluster_search that visites neighbors of node u.
void visit_v(graph * g, int * visited, int u, vertices ** l_vert);

/*
	void cluster_search(graph * g, cluster ** clus);
	--
	Performs a Depth-First Search on g until
	every vertices are visited. Then returns
	each cluster (if exists) in *clus.
	(a linked-list of linked-list structure). 
*/
void cluster_search(graph * g, cluster ** clus);


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
	You can choose to consider specific parts of the graph
	either a specific year, even semester or the whole
	curriculmum.
	--
	mode :=  {0 : whole curriculum, 1-3 : year mode or 5-10 : semester}.
*/
int longest_path_u(graph * g, int u, int mode, queue ** path);


/*
	Returns a list of the longest path for each vertex of graph g.
	--
	Function must be called with path as NULL pointer.
*/
int longest_path(graph * g, queue ** path, int mode);

/////////////////////////////////////////////////////////////////////////////////

#endif

/////////////////////////////////////////////////////////////////////////////////