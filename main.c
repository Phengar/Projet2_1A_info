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
#include "reader_matAdj.h" // Graph loader/ builder
#include "stat.h"   		// Miscellaneous data analysis functions
 

/////////////////////////////////////////////////////////////////////////////////


int main() {
    mat_adj * graph =  NULL;
    load_graph("./csv/nodes.csv", "./csv/edges.csv", &graph);
    int nodes = get_nodes(graph);
	printf("Number of nodes in the graph : %d\n", nodes);
    printf("================================\n");


    printf("Number of UP in the ISMIN syllabus : %d.\n", get_UP(graph));
    printf("Number of GP in the ISMIN syllabus : %d.\n", get_GP(graph));
    printf("================================\n");


    int semester = 5, year = 1;
    printf("Number of UP in the %d-th semester : %d.\n", semester, get_UP_semester(graph, semester));
    printf("Number of UP in the year %d : %d.\n", year, get_UP_year(graph, year));
    printf("Number of GP in the %d-th semester : %d.\n", semester, get_GP_semester(graph, semester));
    printf("Number of GP in the year %d : %d.\n", year, get_GP_year(graph, year));
    printf("================================\n");


    int id_max_degree, id_min_degree;
    int min_degree = get_min_degree(graph, &id_min_degree);
    int max_degree = get_max_degree(graph, &id_max_degree);
    printf("Minimum degree node : %s - %d.\n", graph[id_min_degree].name, min_degree);
    printf("Maximum degree node : %s - %d.\n", graph[id_max_degree].name, max_degree);
    printf("================================\n");


    int * degrees = (int *) calloc(get_nodes(graph), sizeof(int));
    if(degrees ==  NULL) {
        printf("Cannot allocate enough memory for degrees array.\n");
        exit(1);
    }
    get_degrees(graph, degrees);
    printf("Degrees per node :\n");
    print_array(degrees, get_nodes(graph));
    printf("================================\n");


    print_top_degrees(degrees, graph, 10);
    printf("================================\n");


    int length;
    int * gp_array = get_GP_array(graph, &length);
    int * degrees_GP = (int *) calloc(length, sizeof(int));
    if(degrees_GP == NULL) {
        printf("Cannot allocate enough memory.\n");
        exit(1);
    }
    get_degrees_GP(graph, gp_array, length, degrees_GP);
    print_top_degrees_GP(graph, gp_array, degrees_GP, length, 5);
    printf("================================\n");

    printf("Is the graph acyclic : %s\n", (is_acyclic(graph)) ? "oui" : "non");
    printf("================================\n");


    cluster * clus = NULL;
    cluster_search(graph, &clus);
    printf("Result of the cluster search in the graph :\n");
    print_cluster(graph, &clus);
    printf("================================\n");


    /*queue ** q = (queue **) malloc(get_nodes(graph) * sizeof(queue *));
    if(q == NULL) {
        printf("Cannot allocate enough memory.\n");
        exit(1);
    }
    for(int u = 0; u < get_nodes(graph); u++) {
        q[u] = NULL;
    }
    int mode = 0;
    int lpath = longest_path(graph, q, mode);
    printf("Longest path in the graph : %d.\n", lpath);*/

    
    free(degrees);
    free(degrees_GP);
    return 0;
}


/////////////////////////////////////////////////////////////////////////////////