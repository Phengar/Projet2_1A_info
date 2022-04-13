/////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"
#include "reader_listAdj.h"

/////////////////////////////////////////////////////////////////////////////////

// According empirical data :)
#define MAX_SEMESTER 10
#define MAX_UP 100

/////////////////////////////////////////////////////////////////////////////////

/*

    Loads the graph defined in nodes_files and
    edges_file nto res an adjacency matrix structure.

*/

void load_graph(char * nodes_file, char * edges_file, mat_adj ** res) {
    int refTable[MAX_SEMESTER][MAX_UP];
    char nom[MAX_LENGTH];
    int i = 0;
    int id, x, y;
    FILE * file;
    file = fopen(nodes_file, "rb");
    if(file == NULL) {
        fprintf(stderr, "\nCouldn't open nodes.csv\n");
        exit(1);
    }

    UPL *upi = (UPL *) malloc(sizeof(UPL));
    if(upi == NULL) {
        printf("Cannot allocate enough memory for UP list.\n");
        exit(1);
    }
    
    UPL * head = upi;
    while(fscanf(file, "%d %s %d %d", &upi->id, upi->name, &upi->x, &upi->y)== 4) {
        upi->next = (UPL *) malloc(sizeof(UPL));
        if(upi->next == NULL) {
            printf("Cannot allocate enough memory for an UP.\n");
            exit(1);
        }
        refTable[upi->x][upi->y]=upi->id;
        //printf("élement %d: nom:%s, x:%d, y:%d\n", upi->id, &upi->name, upi->x, upi->y);
        upi = upi->next;
        i += 1;
    }
    //printf("nb lignes: %d\n", i);

    //public mat_adj * pointer = (mat_adj *)malloc(sizeof(mat_adj)*i);
    *res = (mat_adj *) malloc(i * sizeof(mat_adj));
    if(res == NULL) {
        printf("Cannot allocate enough memory for adjacency matrix.\n");
        exit(1);
    }

    upi = head;
    for(int j=0; j<i; j++) {
        (*res)[j].nb_n = i;
        (*res)[j].nb_child = 0;
        (*res)[j].list = (int *) calloc(i, sizeof(int));
        if((*res)[j].list == NULL) {
            printf("Cannot allocate enough memory for a new list.\n");
            exit(1);
        }
        (*res)[j].id = upi->id;
        strcpy((*res)[j].name, upi->name);
        (*res)[j].x = upi->x;
        (*res)[j].y = upi->y;
        upi = upi->next;
        //printf("élement: %d, nom: %s, x: %d, y: %d\n", (*res)[j].id, &(*res)[j].name, (*res)[j].x, (*res)[j].y);
    }

    FILE * file2;
    file2 = fopen(edges_file, "rb");
    if (file2 == NULL){
        fprintf(stderr, "Couldn't open edges.csv\n");
        exit(1);
    }
    int x1,y1,x2,y2,id1,id2;
    while (fscanf(file2, "%d %d %d %d", &x1, &y1, &x2, &y2)==4){
        id1=refTable[x1][y1];
        id2=refTable[x2][y2];
        (*res)[id1].list[id2]=1;
        (*res)[id1].nb_child++;
        (*res)[id2].list[id1]=1;
        (*res)[id2].nb_child++;
    }

    fclose(file);
    fclose(file2);
}

/////////////////////////////////////////////////////////////////////////////////