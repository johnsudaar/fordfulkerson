#include "ford.h"

// Cherche un chemin non saturé allant de 'from' à 'to'
list* getPath(graph* g, int from, int to, list* path){
	// Si nous sommes arrivé au puit
	if(from == to){
		return addOrInit(path,from);
	}
	// Sinon

	// On recupere la liste des noeuds potentiels
	list* neighbors = getNeighbors(g, from);
	int i;
	list* test_path = NULL;

	// On ajoute le noeud courant au chemin
	path = addOrInit(path, from);

	// Pour chacun des noeuds potentiels
	for(i = 0; i < listSize(neighbors); i++){
		int neighbor = getList(neighbors, i);
		// Si l'on est pas encore passé par cet arc
		if(! sequenceInList(path, from, neighbor)){
			// On essaie de trouver un chemin en passant par cet arc
			test_path = getPath(g, neighbor, to, copy(path));

			// Si le chemin est trouvé on s'arrete
			if(test_path != NULL){
				freeList(path);
				return test_path;
			}
			// Sinon on passe au voisin suivant
			freeList(test_path);
		}
	}
	freeList(path);
	// Si l'on a trouvé aucun chemin
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

	// On parcour tous les noeuds a la recherche de la plus petite valeur possible
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
	// Pour chacun des arcs
	for(i = 0 ; i < listSize(p)-1 ; i++){
		from = getList(p, i);
		to = getList(p, i + 1);
		// Mise a jour des flots
		setCapacity(g, from, to, getCapacity(g,from,to) - flow);
		setCapacity(g, to, from, getCapacity(g,to,from) + flow);
	}
}

double ford_fulkerson(graph* g, int from, int to){
	double flow = 0;
	list *path = getPath(g, from, to, NULL);
	// Tant que l'on trouve un chemin augementant
	while(path != NULL){
		printf("Saturing : ");
		printList(path);
		// On récupère la capacité minimum du chemin
		double current_flow = getMinCapacity(g, path);
		// On met a jour
		updateGraph(g, path, current_flow);
		freeList(path);
		flow += current_flow;
		// On cherche le chemin suivant
		path = getPath(g, from, to, NULL);
	}
	return flow;
}