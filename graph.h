#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#include "listes.h"

enum graph_errors {NODE_OUT_OF_RANGE};

typedef struct{
  int nodes;
  double **data;
} graph;

graph* newGraph(int nodes);
int setCapacity(graph* g, int from, int to, double value);
double getCapacity(graph* g, int from, int to);
graph* loadGraph(char* file);

list* getNeighbors(graph* g, int node);

#endif