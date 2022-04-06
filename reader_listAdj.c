/////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "format.h"
#include "reader_listAdj.h"

/////////////////////////////////////////////////////////////////////////////////

/*graph read_nodes(){
    char nom[50];
    int i=0;
    int id,x,y;
    FILE * file;
    file = fopen("nodes.csv", "rb");
    if (file == NULL){
        fprintf(stderr, "\nCouldn't  Open nodes.csv\n");
        exit(1);
    }
    UPL *upi = (UPL *)malloc(sizeof(UP));
    UPL *head=upi;
    while (fscanf(file, "%d %s %d %d", &upi->id, &upi->name, &upi->x, &upi->y)== 4){
        upi->next=(UPL *)malloc(sizeof(UP));
        //printf("élement %d: nom:%s, x:%d, y:%d\n", upi->id, &upi->name, upi->x, upi->y);
        upi=upi->next;
        i+=1;
    }
    printf("nb lignes: %d", i);

    mat_adj res[i];
    upi=head;
    for(int j=0; j<i; j++){
        res[j].list = (int *)calloc(i,sizeof(int));
        res[j].id=upi->id;
        strcpy(res[j].name, &upi->name)   ;
        res[j].x=upi->x;
        res[j].y=upi->y;
        upi=upi->next;
        printf("élement %d: nom:%s, x:%d, y:%d\n", res[j].id, &res[j].name, res[j].x, res[j].y);
    }

    return res
    
}*/


/*graph read_edges()[
    FILE * file2;
    file2 = fopen("edges.csv", "rb");
    if (file == NULL){
        fprintf(stderr, "\nCouldn't  Open edges.csv\n");
        exit(1);
    }
    int x1,y1,x2,y2;
    fscanf(file, "%d %d %d %d", &x1, &y1, &x2, &y2);
]*/

int ** main(){
    char nom[50];
    int i=0;
    int id,x,y;
    FILE * file;
    file = fopen("nodes.csv", "rb");
    if (file == NULL){
        fprintf(stderr, "\nCouldn't  Open nodes.csv\n");
        exit(1);
    }
    UPL *upi = (UPL *)malloc(sizeof(UP));
    UPL *head=upi;
    while (fscanf(file, "%d %s %d %d", &upi->id, &upi->name, &upi->x, &upi->y)== 4){
        upi->next=(UPL *)malloc(sizeof(UP));
        //printf("élement %d: nom:%s, x:%d, y:%d\n", upi->id, &upi->name, upi->x, upi->y);
        upi=upi->next;
        i+=1;
    }
    printf("nb lignes: %d", i);

    mat_adj res[i];
    upi=head;
    for(int j=0; j<i; j++){
        res[j].list = (int *)calloc(i,sizeof(int));
        res[j].id=upi->id;
        strcpy(res[j].name, &upi->name)   ;
        res[j].x=upi->x;
        res[j].y=upi->y;
        upi=upi->next;
        printf("élement %d: nom:%s, x:%d, y:%d\n", res[j].id, &res[j].name, res[j].x, res[j].y);
    }

    fclose(file);

    FILE * file2;
    file2 = fopen("edges.csv", "rb");
    if (file == NULL){
        fprintf(stderr, "\nCouldn't  Open edges.csv\n");
        exit(1);
    }
    int x1,y1,x2,y2;
    while (fscanf(file, "%d %d %d %d", &x1, &y1, &x2, &y2)==4){
        
    }

}

/////////////////////////////////////////////////////////////////////////////////