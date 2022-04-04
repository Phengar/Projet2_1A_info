//Plan du programme :







//Bibliothèques



#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>







//variables globales
#define TAILLE_MAX 50

//Structures de données

typedef struct S{
char* nom;
int x;
int y;
struct S* V;
}UP;

typedef struct{
int n1[2];
int n2[2];
}Edge;



//Fonctions

int nb_lignes(char* nom_fic_n){
    FILE* fichier = fopen("nodes","r");
    if(fichier!=NULL){
        char nom_UP[TAILLE_MAX];
        char nom_UP2[TAILLE_MAX];
        char nom_UP3[TAILLE_MAX];
        int x;
        int y;
        int n=0;
        fscanf(fichier,"%s%*c%s%*c%s\n",nom_UP, nom_UP2, nom_UP3);
        int test=fscanf(fichier,"%s%*c %d%*c %d\n",nom_UP,&x,&y);
        while(test==1){
            n++;
        }
        
        printf("\n%d\n",n);
        return(n);
    }
    else return(0);
}


void Lire_nodes(char* nom_fic_n,UP* A){
    FILE* fichier = fopen(nom_fic_n,"r");
    printf("%s",nom_fic_n);
    if(fichier!=NULL){
        int n = nb_lignes(nom_fic_n);
        A = (UP*)malloc(n*sizeof(UP));

        int ligne = 0;
        char nom_UP[TAILLE_MAX];
        int xi;
        int yi;
        for(int ligne=0;ligne<n;ligne++){
                fscanf(fichier,"%s,%d,%d",nom_UP,xi,yi);
                A[ligne].nom = nom_UP;
                A[ligne].x = xi;
                A[ligne].y = yi;
                ligne++;

        }
        fclose(fichier);
        printf("Les noeuds sont lus\n\n");
    }
    else printf("Les noeuds n'ont pas été lus\n\n");
}












//Fonction main :

void main(){
    char* nom_fic_n = "nodes.csv";
    char* nom_fic_e = "edges.csv";
    UP* A;
    nb_lignes(nom_fic_n);
    return;
}