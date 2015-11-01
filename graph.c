#include <stdio.h>
#include <stdlib.h>

#include "graph.h"


graph* newGraph(int nodes){
  graph* g = malloc(sizeof(graph));
  g->nodes = nodes;

  g->data = malloc(nodes * sizeof(double*));
  int i;
  for(i = 0; i < nodes; i++){
    g->data[i] = malloc(nodes * sizeof(double));
  }

  return g;
}

int setFlow(graph* g, int from, int to, double value){
  if(from < 0 || from >= g->nodes){
    return NODE_OUT_OF_RANGE;
  }

  if(to < 0 || to >= g->nodes){
    return NODE_OUT_OF_RANGE;
  }

  g->data[from][to] = value;
  return 0;
}

double getFlow(graph* g, int from, int to){
  if(from < 0 || from >= g->nodes || to < 0 || to >= g->nodes){
    fprintf(stderr, "getFlow => node out of range (from: %d, to: %d, g->nodes: %d\n",from,to,g->nodes);
    return 0;
  }

  return g->data[from][to];
}