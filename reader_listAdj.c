/////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "format.h"
#include "reader_listAdj.h"

/////////////////////////////////////////////////////////////////////////////////

graph read_nodes(){
    UP res;
    char nom[50];
    int i=0;
    int id,x,y;
    FILE * file;
    file = fopen("nodes.csv", "rb");
    if (file == NULL){
        fprintf(stderr, "\nCouldn't open nodes.csv\n");
        exit(1);
    }
    UP *upi = (UP *)malloc(sizeof(UP));
    while (fscanf(file, "%d %s %d %d", &upi->id, &upi->name, &upi->x, &upi->y)== 4){
        upi->next=(UP *)malloc(sizeof(UP));
        printf("ligne %d: nom:%s, x:%d, y:%d\n", upi->id, &upi->name, &upi->x, &upi->y);
        upi=upi->next;
        i+=1;
    }
    printf("nb lignes: %d", i+1);
    
}


/*graph read_edges()[
    FILE * file2;
    file2 = fopen("edges.csv", "rb");
    if (file == NULL){
        fprintf(stderr, "\nCouldn't open edges.csv\n");
        exit(1);
    }
    int x1,y1,x2,y2;
    fscanf(file, "%d %d %d %d", &x1, &y1, &x2, &y2);
]*/

int ** main(){

    read_nodes();

}

/////////////////////////////////////////////////////////////////////////////////