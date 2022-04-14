# ISMIN's syllabus analysis project

DAVAL Quentin - HUBINET Benjamin - ISMIN 1A - EI21




## TO-DO - Requirements list :

Comment il faut exécuter le programme et structuration du ReadMe.txt :

- Différentes section du programme et leurs relations (brievement)

- Qu'est-ce que l'on attend en output

- Pourquoi favoriser un certain algorithme

## Idées pour le rapport :

- Avant-propos : Raisons/ finalité de ce projet

- Choix des diverses structures : Raisons, structuration de celles-ci, complexité des opérations

- Choix des algorithmes

- Résultats fournis : Analyse, mise en forme des résultats : Dashboard

- Divers problèmes et solutions apportées, structuration du projet

- Conclusions : Possibles améliorations, captialiser sur le projet

## Idées pour le README.txt/ README.md

- Introduction

- Compilation and running the project

- Project structure/ Tree

- Quick references

> Par exemple : 

| Header file |    Function header    | 	Description   |
| ----------- |    ---------------    | 	-----------   |
|  example.h  |   void function(void) | Function that ... |




## Introduction

The incentive of this project was to lead
an analysis of the ISMIN syllabus with
graph theory's tools. Namely its algorithms
such as graph traversal, shortest/ longest path
algorithms. As well as its properties : acyclic graph,
graph clusters and connected components. The analysis
emphasizes on the topology of subjects in the ISMIN syllabus :
How are they related to one another ? Which one are isolated and 
which create a cluster ?

The data processed by the analysis will serve to help the education
assembly make decisions for the 2023 ISMIN syllabus reform.


## :floppy_disk: Modularity choices

We chose to divide the specific features of the project in various
files. Namely :

  | Header file | Purppose |
  | ----------- | -------- |
  | ***reader_listAdj.h*** | Gathers the functions used to read both *nodes.csv* and *edges.csv*, and then a create the graph structure out of it. |
  | ***stat.h*** | Gathers the analysis functions used on the ISMIN syllabus graph. |
  | ***format.h*** | Gathers the definition of every data-structure used, for either importing or analyzing data. |
  | ***main.c*** | Core of the project, uses functions from modules to import and process data. |
  | ***formater.py*** | Formats both *edges.csv* and *nodes.csv* files : Handles uplicates, loop edges, replaces special characters, spaces and commas |




## Statistics analysis

* TO BE COMMENCÉ *




## 🎯 Faced issues
  While attempting to read *.csv* files, we ran into issues. Namely, each row of *nodes.csv* contains a string with spaces in it and two numbers, when we tried to parse the file using a `fscanf()`. * TO BE CONTINUED *
  
 


## 🛠️ Compilation & running the project

The overall project was written using both Python 3 and C.
Actually, the only part that requires Python is the `.csv`
files formatting step. The rest of the of the implementation
uses C only.

#### :warning: Requirements

As long as you have GCC compiler and GNU Make tool installed,
the code should run flawlessly on Linux systems. Having the
Python 3 interpreter is not mandatory as `.csv` files are
yet formatted. Nonetheless you can still try this script out
on un-formatted data stored in `./*.csv.bak` files.

+ **Installing gcc and make** :
  - *Debian systems* :
      > Installing both gcc & make
      ``` bash
      sudo apt install build-essential
      ```
  - *Windows OS* :
      > MinGW provides you with both a gcc compiler and make tool.

+ 🛠️ **Compiling** :
      `make`

+ 💻 **Running** :
  - *Unix systems*
      ```bash
      ./main
      ```
  
  - *Windows*
      ```bash
      main.exe
      ```
      
      
      
      
## 🌳 Project tree

```bash
Projet2_1A_info
├── bin/
│   └── main or main.exe
├── obj/
│   └── object files
├── pdf/
│   └── pdf files
├── src/
│   └── src files : *.c, *.h and *.py
├── Makefile
└── README.md
```
 
 
 
 
## ⌨️ Quick references

| Header file |    Function header or structure    | 	Description   |
| ----------- |    ---------------    | 	-----------   |
|  **Makefile**  |   `make` or `make main` | Compiles the project's C code |
|  **Makefile**  |   `make clean` | Cleans `./obj` and `./bin` content |
| ----------- |    ---------------    | 	-----------   |
|  **stat.h**  |   `int get_nodes(graph * g)` | Returns number of nodes in graph g |
|  **stat.h**  |   `int get_degree_u(graph * g, int u)` | Returns the number of edges connceted to node u |
|  **stat.h**  |   `int get_max_degree(mat_adj * g, int * id_max)` | Returns the max degree of mat_adj g and puts its index at ind_max |
|  **stat.h**  |   `int get_min_degree(mat_adj * g, int * id_min)` | Returns the min degree of mat_adj g and puts its index at ind_min |
|  **stat.h**  |   `void get_degrees(graph * g, int * degrees)` | Creates an array (degrees) containing the degree for each vertex of graph g |
|  **stat.h**  |   `void print_top_degrees(int * degrees, int nb_n, int n)` | Prints the top n nodes with the highest degrees |
|  **stat.h**  |   `int get_UP(mat_adj * g)` | Returns the number of UP in mat_adj g |
|  **stat.h**  |   `int get_UP_semester(mat_adj * g, int semester)` | Returns the number of UP in a given semester |
|  **stat.h**  |   `int get_UP_year(mat_adj * g, int year)` | Returns the number of UP in a given semester |
|  **stat.h**  |   `int get_GP(mat_adj * g)` | Returns the number of GP in mat_adj g |
|  **stat.h**  |   `int get_GP_semester(mat_adj * g, int semester)` | Returns the number of GP in a given semester |
|  **stat.h**  |   `int get_GP_year(mat_adj * g, int year)` | Returns the number of GP in a given year |

|  **stat.h**  |   `int is_acyclic(graph * g)` | Returns whether g is acyclic or not |

|  **stat.h**  |   `int visit_v_acy(graph * g, int * visited, int u)` | Sub-fonction of is_acyclic - It behaves like Depth-First Search |
|  **stat.h**  |   `void cluster_search(graph * g, cluster ** clus)` | Performs a Depth-First Search on g until every vertices are visited |
|  **stat.h**  |   `void visit_v(graph * g, int * visited, int u, cluster ** list` | Sub-function of cluster_search that visits neighbors of node u |
|  **stat.h**  |   `int longest_path_u(graph * g, int u, int mode, queue ** path)` | Returns the length of the longest path from vertex u the path is stored is \*path |
|  **stat.h**  |   `int longest_path(graph * g, queue ** path, int mode)` | Returns a list of the longest path for each vertex of graph g |
| **stat.h**  |   `void distance_update(int * distance, int * v_path, queue ** q, int mode, int v_s, int u, int v)` | Sub-function - Computes the distance from u to v |
|  **stat.h**  |   `int max_array(int * array, int length, int * ind)` | Returns the max element in array. Its index is stored in \*ind |

|  **stat.h**  |   `void print_array(int * array, int length)` | Prints an array of integer of length length |

| ----------- |    ---------------    | 	-----------   |

| **reader_listAdj.h**  |   `struct UPL : {int id, char name[MAX_LENGTH], int x, int y, UPL * next}` | Adjacency list structure used to load the graph from .csv files |
| **reader_listAdj.h**  |   `void load_graph(char * nodes_file, char * edges_file, mat_adj ** res)` | Loads the graph defined in nodes_files and
    edges_file nto res an adjacency matrix structure |
| ----------- |    ---------------    | 	-----------   |

| **format.h**  |   `struct mat_adj : {int nb_n, int id, int x, int y, char name[MAX_LENGTH], int nb_child , int * list}` | graph as adjacency matrix |

| **format.h**  |   `struct cluster : {int key, cluster * list, cluster * next}` | Linked-list of linked-list of vertices - Each node n is a linked-list containing vertices forming the n-th cluster |
| **format.h**  |   `void append_cluster_list(cluster ** clus)` | Appends a new cluster into the cluster main-list |
| **format.h**  |   `void append_cluster_key(cluster ** clus, int key)` | Appends a key in the considered cluster list |
| **format.h**  |   `void pop_cluster(cluster ** clus)` | Pops a cluster node from head |
| **format.h**  |   `void print_cluster(cluster ** clus)` | Prints cluster elements |
| **format.h**  |   `struct queue : {int key, queue ** next}` | Queue data structure |
| **format.h**  |   `void append_queue(queue ** q, int key)` | Appends key to queue tail |
| **format.h**  |   `int pop_queue(queue ** q)` | Pops and returns from queue head |
| **format.h**  |   `void print_queue(queue ** q)` | Prints queue elements |
| ----------- |    ---------------    |   -----------   |
| **sort.h**  | `void copy_array(int * arr1, int * arr2, int i1, int i2, int length)` | Copies arr1 starting at i1 to arr2 starting at i2 on length length |
| **sort.h**  | `void copy_array(int * arr1, int * arr2, int i1, int i2, int length)` | Sorts array arr1 in a decreasing order using merge sort algorithm, arr2 contains the place of each arr1 index after the sort |

| **sort.h**  | `void merge_sort(int * arr1, int * arr2, int length)` | Sorts array arr1 in a decreasing order using merge sort algorithm, arr2 contains the place of each arr1 index after the sort |

| **sort.h**  | `void merge(int * arr1, int * arr2, int size, int i, int j, int * copy1, int * copy2)` | Decreasing merge sort sub-function : Merges elements of arr1 between i and j, does the same for arr2 |

| **sort.h**  | `void print_array(int * arr, int length)` | Prints an array of integers of length length |
