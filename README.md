# ISMIN's syllabus analysis project

DAVAL Quentin - HUBINET Benjamin - ISMIN 1A - EI21

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

  | Header file | Purpose |
  | ----------- | -------- |
  | ***reader_matAdj.h*** | Gathers the functions used to read both *nodes.csv* and *edges.csv*, and then creates the graph structure out of it. |
  | ***stat.h*** | Gathers the analysis functions used on the ISMIN syllabus graph. |
  | ***format.h*** | Gathers the definition of every data-structure used, for either importing or analyzing data. |
  | ***sort.h*** | Implements a decreasing order quick sort. |
  | ***main.c*** | Core of the project, uses functions from modules to import and process data. |
  | ***formater.py*** | Formats both *edges.csv* and *nodes.csv* files : Handles duplicates, loop edges, replaces special characters, spaces and commas |
  




## Algorithm choices

This overall project revolved around graph algorithm, the graph considered in this project is an oriented graph that is represented by two files, namely : *nodes.csv* and *edges.csv*. Each node of this graph are identified by two number \(x, y)\. First of, a loading function uses a linked-list to load the graph of yet \"unknown\" size in memory. The graph is then converted into an adjacency matrix structure for both simplicity and complexity sake. Each (x, y) identifier of the graph is mapped to a unique number identifier (the row number of the node in *nodes.csv*) through a matrix of (Xmax * Ymax) dimension. Acyclism checking function revolves on a depth-first search algorithm, if the graph tries to visit an already visited node, it means that the graph is cyclic. In order to find
clusters in the graph, we used a cluster search function that runs a depth-first search on the whole graph, starting from node zero and then on other nodes until the graph is completely visited. We also built functions that sorts nodes in a decreasing order (either UP or GP) depending on their degree value. Thus, a quick sort is used due to its average O(nlog(n)) time complexity given a list of size n as an input. In addition, it is memory friendly compared to merge sort.
The longest path algorithm revolves on breadth-first search as there is no need to select a specific edge at each step of the algorithm, compared to Dijkstra algorithm or Bellman-Ford algorithm, as each edge has a weight of one. In the Python CSV formater script, we used a hashing table in order to efficiently check if an edge already exists in the *edges.csv* file. The CSV formater program was written in Python as it was quick to implement and as we were allowed to.




## Time and spatial complexity

Let G = (V, E) an oriented graph, where V is its nodes set and E its edges set.
Let L be a list of N integers.
- Python CSV formater :
  + Formating *edges.csv* : Time complexity : **O(|E|)**, spatial complexity : **O(|E|)**
      - Append to hashtable and checking if elements already exists : **O(1)**
      - Parsing each line : **O(1)**
  + Formating *nodes.csv* : Time complexity : **O(|V|)**, spatial complexity : **O(1)**
- Adjacency matrix implementation : spatial complexity : **O(|V|²)**
  + Looping through node u neighbors : Time complexity : **O(|V|)**
  + Accessing one of node u neighbors : Time complexity : **O(1)**
  + Checking if a node is one of u neighbors : Time complexity : **O(1)**
  + Searching for one node in the graph : Time complexity : **O(|V|)**
- Quick sort : Time complexity : Time complexity : **O(N\*log(N))**, spatial complexity : **O(1)**
- Depth-first search : Time complexity : **O(|V| + |E|)**, spatial complexity : **O(|V|)**
- Breadth-first search : Time complexity : **O(|V| + |E|)**, spatial complexity : **(|V|)**
- Longest path building function : Time complexity : **O(|V|² + |V|x|E|)**, spatial complexity : **O(|V|²)**
- Earliest semester to begin a specific subject : Time complexity : **O(|V| + |E|)**, spatial complexity : **O(|V|)**
- Latest semester to begin a subject without disturbing the ISMIN curriculum duration : Time complexity : **O(|V| + |E|)**, spatial complexity : **O(|V|)**




## Project features

This project allows you to determine :
  - ***The number of nodes in the graph, the number of children/ successors of each node,***
  - ***The node with either maximum or the minimum degree in the graph,***
  - ***The number of UP, GP in either a specific semester or specific year,***
  - ***N nodes (UP or GP) sorted by their degree in a decreasing order,***
  - ***Whether the graph is acyclic or not,***
  - ***Each cluster of nodes in the graph,***
  - ***The length of the longest path in the (oriented and acyclic) graph,***
  - ***The length and longest path from a node u,***
  - ***The earliest semester from which a specific subject can be taken,***
  - ***The latest semester a subject can be taken without disturbing the ISMIN curriculum duration,***
  - ***Save the previously computed statistics in various files of ./stats directory.***





## 🎯 Faced issues

While attempting to read *.csv* files, we ran into issues. Namely, each row of *nodes.csv* contained a string with spaces in it. When we tried to parse the file using a `fscanf()` without formating the file, `fscanf()` considered spaces as a line skip character which raised issues. To face this problem, we wrote a Python script `formater.py` that formats *.csv* files beforehand. Precisely, it deletes looping edges, deletes duplicates rows, it also deletes **[5, 18]** unexisting node and replaces comma seprators by spaces in *edges.csv*. Furthermore, it replaces blank characters within strings by underscore, replaces comma seperator by spaces and deletes ASCII character with code 0xA0 in *nodes.csv*.




## Conclusion

This project was the occasion to enhance both our programming and algorithmic skills by putting into practice algorithmic concepts, precisely graph theory concepts we studied in class. Furthermore, this project was the opportunity to get an in-depth overview of the ISMIN syllabus, namely the relations between school subjects (either GP or UP).





## 🛠️ Compilation & running the project

The overall project was written using both Python 3 and C.
Actually, the only part that requires Python is the `.csv`
files formatting step, as well as a visual representation of the
whole graph. The rest of the of the implementation uses C only.

#### :warning: Requirements

As long as you have GCC compiler and GNU Make tool installed,
the code should run flawlessly on Linux systems. Having the
Python 3 interpreter is not mandatory as `.csv` files are
yet formatted. Nonetheless you can still try this script out
on un-formatted data stored in `./*.csv.bak` files. Furthermore,
if you would like to try the Python script used to render the
whole graph vizualisation, make sure to have *numpy*, *matplotlib*,
*scipy*, *networkx* and *pandas* modules installed. Please note that
a vizualisation is already enclosed in ./stats directory.

+ 🛠️ **Compiling** :
      `make`

+ 💻 **Running** :
  - *Unix systems*
      ```bash
      ./main
      ```


  - *Running the Python csv formater script* ***(Not mandatory)***
      ```bash
      python3 formater.py
      ```


- *Running the Python graph renderer script* ***(Not mandatory)***
      ```bash
      python3 graphe.py
      ```


- *Installing graphe.py dependencies* ***(Not mandatory)***
      ```bash
      python3 pip -m install MODULE_NAME
      ```
      
      
## 🌳 Project tree

```bash
Projet2_1A_info
├── obj/
│   └── object files
├── pdf/
│   ├── Project_Report.pdf
│   └── Project_Subject.pdf
├── stats/
│   ├── General_stats.txt : General statistics on the ISMIN syllabus curriculum graph
│   ├── Nodes_stats.txt   : Statistics on nodes of the syllabus and precedence graph
│   ├── Cluster_stats.txt : Statistics on clusters in the syllabus graph
│   ├── Precedence.txt    : Statistics on the longest path within the precedence graph
│   └── whole_graph.png   : Vizualisation of the whole ISMIN syllabus graph
├── source files : *.c, *.h and *.py
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
|  **stat.h**  |   `void print_top_degrees(int * degrees, mat_adj * g, int n, FILE * f)` | Prints the top n nodes with the highest degrees and saves them to f (if exists) |
|  **stat.h**  |   `int get_UP(mat_adj * g)` | Returns the number of UP in mat_adj g |
|  **stat.h**  |   `int get_UP_semester(mat_adj * g, int semester)` | Returns the number of UP in a given semester |
|  **stat.h**  |   `int get_UP_year(mat_adj * g, int year)` | Returns the number of UP in a given semester |
|  **stat.h**  |   `int get_GP(mat_adj * g)` | Returns the number of GP in mat_adj g |
|  **stat.h**  |   `int get_GP_semester(mat_adj * g, int semester)` | Returns the number of GP in a given semester |
|  **stat.h**  |   `int get_GP_year(mat_adj * g, int year)` | Returns the number of GP in a given year |
|  **stat.h**  |   `int * get_GP_array(mat_adj * g, int * length)` | Returns the GP array (its length is \*length) |
|  **stat.h**  |   `void get_degrees_GP(mat_adj * g, int * gp_arr, int length, int * degrees)` | Creates the sorted array(degrees) of degree for each GP in gp_arr |
|  **stat.h**  |   `void print_top_degrees_GP(mat_adj * g, int * gp_arr, int * degrees, int length, int n, FILE * f)` | Prints the top n GP of g with the highest GP degree and saves them to f (if exists) |
|  **stat.h**  |   `int is_acyclic(graph * g)` | Returns whether g is acyclic or not |
|  **stat.h**  |   `int visit_v_acy(graph * g, int * visited, int u)` | Sub-fonction of is_acyclic - It behaves like Depth-First Search |
|  **stat.h**  |   `void cluster_search(graph * g, cluster ** clus)` | Performs a Depth-First Search on g until every vertices are visited |
|  **stat.h**  |   `void visit_v(graph * g, int * visited, int u, cluster ** list` | Sub-function of cluster_search that visits neighbors of node u |
|  **stat.h**  |   `int longest_path_u(graph * g, int u, int mode, queue ** path)` | Returns the length of the longest path from vertex u the path is stored is \*path |
|  **stat.h**  |   `int longest_path(graph * g, queue ** path, int mode)` | Returns a list of the longest path for each vertex of graph g |
| **stat.h**  |   `void distance_update(int * distance, int * v_path, queue ** q, int mode, int v_s, int u, int v)` | Sub-function - Computes the distance from u to v |
|  **stat.h**  |   `int max_array(int * array, int length, int * ind)` | Returns the max element in array. Its index is stored in \*ind |
|  **stat.h**  |   `void print_array(int * array, int length)` | Prints an array of integer of length length |
|  **stat.h**  |   `int earliest_to_u_compute(mat_adj * g, int u, int * lookup)` | Sub function of Quickest time (semester) to begin node u related subject |
|  **stat.h**  |   `int earliest_to_u(mat_adj * g, int u)` | Quickest time (semester) to begin node u related subject |
|  **stat.h**  |   `int latest_to_u_compute(mat_adj * g, int u, int duration, int * lookup)` | Sub function of Latest time to take a specific subject u |
|  **stat.h**  |   `int latest_to_u(mat_adj * g, int u, int duration)` | Latest semester to take a subject without disturbing the duration of the curriculum |
|  **stat.h**  |   `void save_statistics(char * general_stats, char * nodes_stats, char * cluster_stats, char * precedence_stats, cluster * clus, queue ** q, mat_adj * graph, mat_adj * precedence_graph, int * degrees, int length, int * gp_array, int * degrees_GP)` | Saves various statistics computed in main.c to files in /stats directory. (Arguments are variables defined in main.c) |
| ----------- |    ---------------    | 	-----------  |
| **reader_matAdj.h**  |   `struct UPL : {int id, char name[MAX_LENGTH], int x, int y, UPL * next}` | Linked-list structure used to load the graph from .csv files |
| **reader_matAdj.h**  |   `void load_graph(char * nodes_file, char * edges_file, mat_adj ** res)` | Loads the graph defined in nodes_files and edges file nto res an adjacency matrix structure |
| ----------- |    ---------------    | 	-----------  |
| **format.h**  |   `struct mat_adj : {int nb_n, int id, int x, int y, char name[MAX_LENGTH], int nb_child , int * list}` | graph as adjacency matrix |
| **format.h**  |   `struct cluster : {int key, cluster * list, cluster * next}` | Linked-list of linked-list of vertices - Each node n is a linked-list containing vertices forming the n-th cluster |
| **format.h**  |   `void adj_to_pre(mat_adj * g, mat_adj ** gp)` | Transforms the graph g represented as an adjacency matrix into a graph de précédence |
| **format.h**  |   `void append_cluster_list(cluster ** clus)` | Appends a new cluster into the cluster main-list |
| **format.h**  |   `void append_cluster_key(cluster ** clus, int key)` | Appends a key in the considered cluster list |
| **format.h**  |   `void pop_cluster(cluster ** clus)` | Pops a cluster node from head |
| **format.h**  |   `void print_cluster(cluster ** clus)` | Prints cluster elements |
| **format.h**  |   `struct queue : {int key, queue ** next}` | Queue data structure |
| **format.h**  |   `void append_queue(queue ** q, int key)` | Appends key to queue tail |
| **format.h**  |   `int pop_queue(queue ** q)` | Pops and returns from queue head |
| **format.h**  |   `void print_queue(queue ** q)` | Prints queue elements |
| ----------- |    ---------------    |   -----------   |
| **sort.h**  | `void swap(int * arr, int i, int j)` | Swaps values at i and j in array arr |
| **sort.h**  | `int pivot(int * arr1, int * arr2, int i, int j)` | Decreasing quick sort sub-function  |
| **sort.h**  | `void quick_sort(int * arr1, int * arr2, int length)` | Decreasing quick sort function |
