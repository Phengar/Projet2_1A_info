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

int get_vertices(graph * g);

int get_edges(graph * g);

int get_max_degree(graph * g);

int get_min_degree(graph * g);

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//

int visit_v_acy(graph * g, int * visited, int v);

int is_acyclic(graph * g);

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//

/*
	void cluster_search(graph * g, UP ** ups);
	--
	Performs a Depth-First Search on g until
	every vertices are visited. Then returns
	each cluster (if exists) in ups
	(a linked-list of linked-list structure). 
*/

// visit_v is a sub-fonction from cluster_search that visits v neighbors
void visit_v(graph * g, int * visited, int v, vertices ** l_vert);

void cluster_search(graph * g, cluster ** clus);

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//

// Returns the maximum of an array
// *ind contains the index of one maximum
int max_array(int * array, int length, int * ind);

void distance_update(int * distance, int * v_path, queue ** q, int mode, int u, int us, int s);

/*

	Returns length of the longest path from v
	path contains the path from v to the farthest vertex
	--
	mode := 5-6 : semester, 1-3 : year mode or 0 : whole curriculum

*/

int longest_path_v(graph * g, int v, int mode, queue ** path);

//------

//void longest_path(graph * g, int v);

/////////////////////////////////////////////////////////////////////////////////

#endif

/////////////////////////////////////////////////////////////////////////////////