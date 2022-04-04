/////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "format.h"
#include "reader_listAdj.h"

/////////////////////////////////////////////////////////////////////////////////

graph read(){
    char nom[50];
    int x,y;
    FILE * file;
    file = fopen("nodes.csv", "rb");
    if (file == NULL){
        fprintf(stderr, "\nCouldn't  Open nodes.csv\n");
        exit(1);
    }
    fscanf(file, "%s,%d,%d", nom, &x, &y);
    while (fscanf(file, "%s,%d,%d", nom, &x, &y)== 3){

    }
}

int ** main(){

}

/////////////////////////////////////////////////////////////////////////////////