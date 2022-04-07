/////////////////////////////////////////////////////////////////////////////////

/*

    Projet Algorithmique & Programmation 2
    Analyse du syllabus du cycle ISMIN
    --
    DAVAL Quentin - HUBINET Benjamin
    ISMIN 1A - EI21

*/

/////////////////////////////////////////////////////////////////////////////////

// Libraries includes
#include <stdio.h>
#include <stdlib.h>
#include "format.h" 		// Data format definition
#include "reader_listAdj.h" // Graph loader/ builder
#include "stat.h"   		// Miscellaneous data analysis functions
 

/////////////////////////////////////////////////////////////////////////////////

int main() {
    mat_adj * graph =  NULL;
    load_graph("nodes.csv", "edges.csv", &graph);
    printf("%d\n", (graph == NULL));
    int nodes = get_nodes(graph);
	printf("Number of nodes in the graph : %d\n", nodes);
    

    int * degrees = NULL;
    get_degrees(graph, degrees);
    printf("Is the graph acyclic : %s\n", (is_acyclic(graph)) ? "oui" : "non");
    
    printf("Coucou1.\n");
    cluster * clus = NULL;
    cluster_search(graph, &clus);
    printf("Result of the cluster search in the graph :\n");
    print_cluster(&clus);


    queue * q = NULL;
    int mode = 0;
    int lpath = longest_path(graph, &q, mode);
    printf("Longest path in the graph : %d.\n", lpath);
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////