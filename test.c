
//Plan du programme :

//Biblioth�ques

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


//Variables globales

#define TAILLE_MAX 50
#define nombreS 6
#define nombreA 120

//Structures de donnees

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

//remplit le tableau S avec les semestres, les adresses d'UP et les noms d'UP
int Lire_nodes(char* nom_fic_n,char S[nombreS][nombreA][50]){
    FILE* fp = fopen(nom_fic_n, "r");
    int nS=0;
    if (!fp)
        printf("Can't open file\n");
    else {
        char buffer[1024];
        int row = 0;
        int column = 0;
        int x=0,y=0;
        char* nom;
        while (fgets(buffer,1024,fp)) {
            column = 0;
            row++;
            char* value = strtok(buffer, ", ");
            while (value) {

                if (column%3 == 0) {
                    nom = value;
                }

                if (column%3 == 1) {
                    x = strtol(value, NULL, 10);
                }

                if (column%3 == 2) {
                    y = strtol(value, NULL, 10);
                    strcpy(S[x-1][y-1],nom);
                    nS++;
                }
                value = strtok(NULL, ", ");
                column++;
            }
            printf("\n");
        }
        fclose(fp);
    }
    return nS;
}

//fonction d'affichage
void Afficher_nodes(char S[nombreS][nombreA][50]){
    for(int i=0;i<nombreS;i++){
        printf("\n\tSemestre %d\n",i+1);
        for(int j=0;j<nombreA;j++){
            if(strlen(S[i][j])>0) printf("%d : %s\n",j+1,S[i][j]);
        }
    }
    return;
}


//affichage dans le menu
void print_node(char S[nombreS][nombreA][50]){
        int x=0,y=0;
        printf("\nEntrez un semestre : ");
        scanf("%d",&x);
        if(x>0 && x<nombreS+1){
            printf("\nEntrez un id : ");
            scanf("%d",&y);
            if(strlen(S[x-1][y-1])!=0) printf("L'UP d'identifiant %d du semestre %d est : %s \n",y,x,S[x-1][y-1]);
            else printf("Il n'y a pas d'UP d'identifiant %d du semestre %d",y,x);
        }
        else printf("Il n'y a pas de Semestre %d",x);
        return;
}


//trouve les doublons et rempli le tableau A sans doublons � partir de E qui contient toutes les aretes
int Lire_edges(char S[nombreS][nombreA][50],char* nom_fic_e,Edge A[400],int listedeg[nombreS][nombreA]){
    FILE* fp = fopen(nom_fic_e, "r");
    int compt = 0;
    if (!fp)
        printf("Can't open file\n");
    else {
        char buffer[20];
        int row = 0;
        int column = 0;
        Edge E;
        int doublon = 0;
        int exist = 0;
        char* nom;
        while (fgets(buffer,20,fp)) {
            column = 0;
            row++;
            char* value = strtok(buffer, ", ");
            while (value) {

                if (column%4 == 0) {
                    E.n1[0] = strtol(value, NULL, 10);
                }

                if (column%4 == 1) {
                    E.n1[1] = strtol(value, NULL, 10);
                }

                if (column%4 == 2) {
                    E.n2[0]  = strtol(value, NULL, 10);
                }
                if (column%4 == 3) {
                    E.n2[1] = strtol(value, NULL, 10);
                    for(int i=0;i<=compt;i++){
                        if((A[i].n1[0]==E.n1[0])&&(A[i].n1[1]==E.n1[1])&&(A[i].n2[0] == E.n2[0])&&(A[i].n2[1]==E.n2[1])) doublon=1;
                        if((A[i].n1[0]==E.n2[0])&&(A[i].n1[1]==E.n2[1])&&(A[i].n2[0] == E.n1[0])&&(A[i].n2[1]==E.n1[1])) doublon=1;
                        if((E.n1[0]==E.n2[0])&&(E.n1[1]==E.n2[1])) doublon=1;
                    }
                    if(!doublon){
                            if((strlen(S[E.n1[0]-1][E.n1[1]-1])>0)&&(strlen(S[E.n2[0]-1][E.n2[1]-1])>0)) exist = 1;
                            else{
                                    printf("%ld  %d",strlen(S[E.n1[0]-1][E.n1[1]-1]),strlen(S[E.n2[0]-1][E.n2[1]-1])>0);
                                    printf("\n[%d %d],[%d %d]\n",E.n1[0],E.n1[1],E.n2[0],E.n2[1]);
                            }
                            if(exist){
                                A[compt]=E;
                                listedeg[E.n1[0]-1][E.n1[1]-1]++;
                                listedeg[E.n2[0]-1][E.n2[1]-1]++;
                                compt++;
                            }
                    }
                    exist = 0;
                    doublon = 0;
                }
                value = strtok(NULL, ", ");
                column++;
            }
            printf("\n");
        }
        printf("%d",compt);
        fclose(fp);
    }
    return(compt);
}


//return si un sommet a �t� visit� ou non
bool EntierVisit(int Visit[nombreS][nombreA])
{
    for(int i=0;i<nombreS;i++)
    {
        for(int j=0;j<nombreA;j++)
        {
            if(Visit[i][j]) return(false);
        }
    }
    return(true);
}



//trouve les composantes connexes du graphe
void connexe(int x, int y, char S[nombreS][nombreA][50],Edge A[400],int * Visit[nombreS][nombreA],int listedeg[nombreS][nombreA])
{
	int i=0;
    int nb=listedeg[x][y];
    (*Visit)[x][y]=0;
    printf("%d : %s\n",x+1,S[x][y]);
	while(nb!=0 && i<500)
	{
        if((A[i].n1[0]-1==x) && (A[i].n1[1]-1==y) && ((*Visit)[A[i].n2[0]-1][A[i].n2[1]-1]))
        {
            printf("%d : %s\n",A[y].n2[0],S[A[y].n2[0]-1][A[y].n2[1]-1]);
            nb--;
            connexe(A[y].n2[0]-1,A[y].n2[1]-1,S,A,Visit,listedeg);
        }
        if((A[i].n2[0]-1==x) && (A[i].n2[1]-1==y) && ((*Visit)[A[i].n1[0]-1][A[i].n1[1]-1]))
        {
            printf("%d : %s\n",A[y].n1[0],S[A[y].n1[0]-1][A[y].n1[1]-1]);
            nb--;
            connexe(A[y].n1[0]-1,A[y].n1[1]-1,S,A,Visit,listedeg);
        }
        i++;
 	}
    for(int i=0;i<nombreS;i++)
    {
    	for(int j=0;j<nombreA;j++)
    	{
    		if((*Visit)[i][j])
    		{
    			x=i;
    			y=j;
    			printf("\n\nUne composante connexe est :\n");
                connexe(x,y,S,A,Visit,listedeg);
                return;
    		}
    	}
    }
}


//trouve le degr� maximal et le semestre et l'arete auquel il est atteint
void fdegmax(char S[nombreS][nombreA][50],int listedeg[nombreS][nombreA])
{
	int degmax=listedeg[0][0];
	int semestre=0;
	int arete=0;
        for(int i=0;i<nombreS;i++)
        {
        	for(int j=0;j<nombreA;j++)
        	{
        		if(listedeg[i][j]>degmax)
        		{
        			degmax=listedeg[i][j];
        			semestre=i;
        			arete=j;
        		}
        	}
        }
        printf("Le degr� max est %d atteint pour l'UP %s du semestre %d \n",degmax,S[semestre][arete],semestre+1);
        return;
}


//print le nom de l'UP et trouve tous les sommets qui lui sont li�s et son degr�
void linked_nodes(char S[nombreS][nombreA][50],Edge A[400],int n,int listedeg[nombreS][nombreA]){
        int x=0,y=0;
        printf("\nEntrez un semestre : ");
        scanf("%d",&x);
        if(x>0 && x<nombreS+1){
            printf("\nEntrez un id : ");
            scanf("%d",&y);
            if(strlen(S[x-1][y-1])!=0){
                    printf("L'UP d'identifiant %d du semestre %d est : %s \n",y,x,S[x-1][y-1]);
            }
            else {
                    printf("Il n'y a pas d'UP d'identifiant %d du semestre %d",y,x);
                    return;
            }
        }

        else {
                printf("Il n'y a pas de Semestre %d",x);
                return;
        }
        printf("\nLes UP associ�s sont :\n");
        for(int j=0;j<nombreS;j++)
        {
        	for(int compt=0;compt<n;compt++)
        	{
           		if((A[compt].n1[0]==x)&&(A[compt].n1[1]==y) && (A[compt].n2[0]==j))
                {
                    printf("%d : %s\n",A[compt].n2[0],S[A[compt].n2[0]-1][A[compt].n2[1]-1]);
                }
                if((A[compt].n2[0]==x)&&(A[compt].n2[1]==y) && (A[compt].n1[0]==j))
                {
                    printf("%d : %s\n",A[compt].n1[0],S[A[compt].n1[0]-1][A[compt].n1[1]-1]);
                }
        	}
        }
        printf("Le degr� de %s est %d \n",S[x-1][y-1],listedeg[x-1][y-1]);
        return;
}


//matiere r�currente sur les semestres
/*void matrec(char S[nombreS][nombreA][50],Edge A[400])
{
	char* listmatrec[227];
	int compteur=0;
	for(int x=0;x<6;x++)
	{
		for(int y=0;y<120;y++)
		{
			for(int i=0;i<nombreS;i++)
			{
				for(int j=0;j<nombreA;j++)
				{
					if ((strcmp(S[i][j],S[x][y])==0) && (x!=i || y!=j))
					{
						listmatrec[compteur]=S[i][j];
						compteur++;
					}
				}
			}
		}
	}
	printf("Les matieres recurrentes sont :\n");
	for(int i=0;i<227;i++)
	{
		if (listmatrec[i]!=NULL)
			printf("%s",listmatrec[i]);
	}
}*/

//renvoie les sommets isol�s selon le degr� moyen on a �tabli qu'un sommet est isol� si son degr� est inf�rieur ou �gal � 1
void sommetisole(char S[nombreS][nombreA][50],int listedeg[nombreS][nombreA])
{
	printf("Les UP isol�s sont :\n");
	for (int i=0;i<nombreS;i++)
	{
		for (int j=0;j<nombreA;j++)
		{
			if (listedeg[i][j]<=1 && strlen(S[i][j])>0)
			{
				printf("%d : %s\n",i+1,S[i][j]);
			}
		}
	}
}


//trouve le degr� moyen des sommets
void fdegmoyen(char S[nombreS][nombreA][50],int listedeg[nombreS][nombreA])
{
	float degmoy=0;
	float somme=0;
	int compt=0;
        for(int i=0;i<nombreS;i++)
        {
        	for(int j=0;j<nombreA;j++)
        	{
			somme+=listedeg[i][j];
			if(listedeg[i][j]!=0)
			{
				compt++;
			}
        	}
        }
        degmoy=somme/compt;
        printf("Le degr� moyen est %f \n",degmoy);
        return;
}

//Fonction main :

void main(void){
    char* nom_fic_n = "nodes.csv.2";
    char* nom_fic_e = "edges.csv.2";
    int k=0,l=0;
    Edge A[400];
    int listedeg[nombreS][nombreA];
    int Visit[nombreS][nombreA];
    /*int*** Visit=(int***)malloc(nombreS*sizeof(int**));
    for (int i=0;i<nombreS;i++)
    {
    	Visit[i]=(int**)malloc(nombreA*sizeof(int*));
        for (int j=0;j<nombreA;j++)
        {
			Visit[i][j]=(int*)malloc(sizeof(int));
		}
	}*/
    char S[nombreS][nombreA][50];
    for(int a=0;a<nombreS;a++){
        for(int b=0;b<nombreA;b++){
            strcpy(S[a][b],"");
        }
    }
    int nS=Lire_nodes(nom_fic_n,S);
    for (int i=0;i<nombreS;i++)
    {
        for (int j=0;j<nombreA;j++)
        {
            listedeg[i][j]=0;
            if(strlen(S[i][j])>0) Visit[i][j]=1;
            
        }
    }
    int nA = Lire_edges(S,nom_fic_e,A,listedeg);
    for(int i=0;i<6;i++)
    {
        printf("\n");
        for(int j=0;j<120;j++)
        {
            printf("%d  ",listedeg[i][j]);
        }
    }
    int menu = 1;
    int choix;
    int L[6][120];
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    //matrec(S,A);
    while(menu){
        printf("\n\n\tMenu :\n\n1)Verifier l existence d une matiere\n2)Afficher toutes les matieres\n3)Afficher les matieres associees\n4)Affichage degr� maximal et degr� moyen\n5)Affichage du nombre d'ar�tes et de sommets\n6)Afficher composantes connexes\n7)Renvoyer la liste des sommets isol�s\n8)Quitter\n\nVotre choix : ");
        //scanf("%d",&choix);
        choix=6;
        switch(choix){
            case(1):
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                print_node(S);
                break;
            case(2):
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                Afficher_nodes(S);
                break;
            case(3):
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                linked_nodes(S,A,nA,listedeg);
                break;
            case(4):
            	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            	fdegmax(S,listedeg);
            	fdegmoyen(S,listedeg);
            	break;
            case(5):
            	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            	printf("Le nombre d'ar�tes est : %d\n",nA);
            	printf("Le nombre de sommets est : %d\n",nS);
            	break;
            case(6):
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                for(int i=0;i<nombreS;i++)
                {
                    for(int j=0;j<nombreA;j++)
                    {
                        if(strlen(S[i][j])>0)
                        	Visit[i][j]=1;
                    }
                }
                printf("\n\nUne composante connexe est :\n");
                connexe(0,0,S,A,&Visit,listedeg);
                break;
            case(7):
            	sommetisole(S,listedeg);
            	break;
            case(8):
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                menu = 0;
        }
    }
    return;
}
