/////////////////////////////////////////////////////////////////////////////////
#include "stat.h"

int get_nodes(graph * g) {
	return g->nb_n;
}

int get_edges(graph * g) {
	return g->nb_e;
}

int get_max_degree(graph * g) {
	int tmp = 0;
	for(int i = 0; i < get_nodes(g); i++) {
		if(tmp < g->g[i][0]) {
			tmp = g->g[i][0];
		}
	}
	return tmp;
}

int get_min_degree(graph * g) {
	int tmp = get_max_degree(g);
	for(int i = 0; i < get_nodes(g); i++) {
		if(tmp > g->g[i][0]) {
			tmp = g->g[i][0];
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////