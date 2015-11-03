#ifndef FORD_H
#define FORD_H

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "listes.h"

list* getPath(graph* g, int from, int to, list* path);
double getMinCapacity(graph* g, list* l);
void updateGraph(graph* g, list* path, double flow);
double ford_fulkerson(graph* g, int from, int to);

#endif