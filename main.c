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
#include "format.h" 	   // Data format definition
#include "reader_matAdj.h" // Graph loader/ builder
#include "stat.h"   	   // Miscellaneous data analysis functions
 

/////////////////////////////////////////////////////////////////////////////////

// Statistics file name
#define GENERAL_STATS "./stats/General_stats.txt"
#define NODES_STATS "./stats/Nodes_stats.txt"
#define CLUSTER_STATS "./stats/Cluster_stats.txt"
#define PRECEDENCE_STATS "./stats/Precedence_stats.txt"

/////////////////////////////////////////////////////////////////////////////////


int main() {
    mat_adj * graph =  NULL;
    load_graph("./csv/nodes.csv", "./csv/edges.csv", &graph);
    int nodes = get_nodes(graph);
    printf("================================\n\n");
	printf("Number of nodes in the graph : %d\n", nodes);
    printf("\n================================\n\n");


    printf("Number of UP in the ISMIN syllabus : %d.\n", get_UP(graph));
    printf("Number of GP in the ISMIN syllabus : %d.\n", get_GP(graph));
    printf("\n================================\n\n");


    int semester = 5, year = 1;
    printf("Number of UP in the %d-th semester : %d.\n", semester, get_UP_semester(graph, semester));
    printf("Number of UP in the year %d : %d.\n", year, get_UP_year(graph, year));
    printf("Number of GP in the %d-th semester : %d.\n", semester, get_GP_semester(graph, semester));
    printf("Number of GP in the year %d : %d.\n", year, get_GP_year(graph, year));
    printf("\n================================\n\n");


    int id_max_degree, id_min_degree;
    int min_degree = get_min_degree(graph, &id_min_degree);
    int max_degree = get_max_degree(graph, &id_max_degree);
    printf("Minimum degree node : %s - %d.\n", graph[id_min_degree].name, min_degree);
    printf("Maximum degree node : %s - %d.\n", graph[id_max_degree].name, max_degree);
    printf("\n================================\n\n");


    int * degrees = (int *) calloc(get_nodes(graph), sizeof(int));
    if(degrees ==  NULL) {
        printf("Cannot allocate enough memory for degrees array.\n");
        exit(1);
    }
    get_degrees(graph, degrees);
    printf("Degrees per node :\n");
    print_array(degrees, get_nodes(graph));
    printf("\n================================\n\n");


    print_top_degrees(degrees, graph, 10, NULL);
    printf("\n================================\n\n");


    int length;
    int * gp_array = get_GP_array(graph, &length);
    int * degrees_GP = (int *) calloc(length, sizeof(int));
    if(degrees_GP == NULL) {
        printf("Cannot allocate enough memory.\n");
        exit(1);
    }
    get_degrees_GP(graph, gp_array, length, degrees_GP);
    print_top_degrees_GP(graph, gp_array, degrees_GP, length, 5, NULL);
    printf("\n================================\n\n");

    int is_acy = is_acyclic(graph);
    printf("Is the graph acyclic : %s\n", (is_acy) ? "oui" : "non");
    printf("\n================================\n\n");


    cluster * clus = NULL;
    cluster_search(graph, &clus);
    printf("Result of the cluster search in the graph :\n");
    print_cluster(graph, &clus);
    printf("\n================================\n\n");


    // Creates the graph de précédence from the syllabus graph
    mat_adj * precedence_graph = NULL;
    adj_to_pre(graph, &precedence_graph);


    queue ** q = (queue **) malloc(get_nodes(precedence_graph) * sizeof(queue *));
    if(q == NULL) {
        printf("Cannot allocate enough memory.\n");
        exit(1);
    }
    for(int u = 0; u < get_nodes(precedence_graph); u++) {
        q[u] = NULL;
    }
    int mode = 0;
    int lpath = longest_path(precedence_graph, q, mode);
    printf("Longest path in the graph : %d.\n", lpath);
    printf("\n================================\n\n");


    queue * tmp = NULL;
    for(int u = 0; u < get_nodes(precedence_graph); u++) {
        tmp = q[u];
        printf("(Node %d) -> ", u);
        while(tmp != NULL) {
            printf("%s(%d), ", precedence_graph[tmp->key].name, tmp->key);
            tmp = tmp->next;
        }
        printf("\n");
    }
    printf("\n================================\n\n");


    int duration = 6;
    for(int u = 0; u < get_nodes(precedence_graph); u++) {
        printf("(Node %d) : %s\n", u, precedence_graph[u].name);
        printf("               - earliest start semester : %d\n", 5+earliest_to_u(precedence_graph, u));
        printf("               - latest start semester : %d\n", 4+latest_to_u(precedence_graph, u, duration));
    }
    printf("\n================================\n\n");


    // Saving the statistics in files

    save_statistics(GENERAL_STATS, NODES_STATS, CLUSTER_STATS, PRECEDENCE_STATS, clus, q, graph, precedence_graph, degrees, length, gp_array, degrees_GP);
    

    // Cleaning the heap memory

    for(int u = 0; u < get_nodes(graph); u++) {
        free(graph[u].list);
        free(precedence_graph[u].list);
        while(q[u] != NULL) pop_queue(&(q[u]));
    }
    free(q);
    free(graph);
    free(precedence_graph);
    free(degrees);
    free(gp_array);
    free(degrees_GP);
    return 0;
}


/////////////////////////////////////////////////////////////////////////////////