#include "ford.h"

// Cherche un chemin non saturé allant de 'from' à 'to'
list* getPath(graph* g, int from, int to, list* path){
	if(from == to){
		return addOrInit(path,from);
	}

	list* neighbors = getNeighbors(g, from);
	int i;
	list* test_path = NULL;

	path = addOrInit(path, from);
	for(i = 0; i < listSize(neighbors); i++){
		int neighbor = getList(neighbors, i);
		if(! sequenceInList(path, from, neighbor)){
			test_path = getPath(g, neighbor, to, copy(path));
			if(test_path != NULL){
				freeList(path);
				return test_path;
			}
			freeList(test_path);
		}
	}
	freeList(path);
	return NULL;
}

// Cherche la capacité minimum dans un chemin
double getMinCapacity(graph* g, list* l){
	if(listSize(l) < 2){
		fprintf(stderr, "getMinCapacity : Wrong list size : %d\n", listSize(l));
		return -1;
	}
	double min = getCapacity(g, getList(l,0), getList(l,1)); // On initialise avec la capacité du premier noeud
	int i = 0;
	//
	for(i=1; i < listSize(l) - 1; i++){
		double current = getCapacity(g, getList(l,i), getList(l,i+1));
		if(current < min) {
			min = current;
		}
	}
	return min;
}

// Met a jour le graph en fonction du chemin trouvé
void updateGraph(graph* g, list* p, double flow){
	if(listSize(p) < 2){
		fprintf(stderr, "updateGraph : Wrong path size : %d\n", listSize(p));
		return;
	}

	int i, from, to;

	for(i = 0 ; i < listSize(p)-1 ; i++){
		from = getList(p, i);
		to = getList(p, i + 1);
		setCapacity(g, from, to, getCapacity(g,from,to) - flow);
		setCapacity(g, to, from, getCapacity(g,to,from) + flow);
	}
}

double ford_fulkerson(graph* g, int from, int to){
	double flow = 0;
	list *path = getPath(g, from, to, NULL);
	while(path != NULL){
		printf("Saturing : ");
		printList(path);
		double current_flow = getMinCapacity(g, path);
		updateGraph(g, path, current_flow);
		freeList(path);
		flow += current_flow;
		path = getPath(g, from, to, NULL);
	}
	return flow;
}