#include "graph.h"


graph* newGraph(int nodes){
  graph* g = malloc(sizeof(graph));
  g->nodes = nodes;

  g->data = malloc(nodes * sizeof(double*));
  int i,j;
  for(i = 0; i < nodes; i++){
    g->data[i] = malloc(nodes * sizeof(double));
    for(j = 0; j < nodes; j++){
      g->data[i][j] = 0;
    }
  }

  return g;
}

int setCapacity(graph* g, int from, int to, double value){
  if(from < 0 || from >= g->nodes){
    return NODE_OUT_OF_RANGE;
  }

  if(to < 0 || to >= g->nodes){
    return NODE_OUT_OF_RANGE;
  }

  g->data[from][to] = value;
  return 0;
}

double getCapacity(graph* g, int from, int to){
  if(from < 0 || from >= g->nodes || to < 0 || to >= g->nodes){
    fprintf(stderr, "getCapacity => node out of range (from: %d, to: %d, g->nodes: %d\n",from,to,g->nodes);
    return 0;
  }

  return g->data[from][to];
}

graph* loadGraph(char* file){
  FILE* f = fopen(file, "r");
  int size = 0;
  fscanf(f, "%d", &size);
  graph* g = newGraph(size);
  char cur = fgetc(f);
  int from, to;
  double value;
  while(cur == ' ' || cur == '\n'){
    fscanf(f,"%d", &from);
    fscanf(f,"%d", &to);
    fscanf(f,"%lf", &value);
    printf("Adding : %d --(%f)-->%d\n", from,value,to);
    setCapacity(g,from,to,value);
    cur = fgetc(f);
  }

  return g;
}

list* getNeighbors(graph* g, int node){
  list* l = NULL;
  int i;
  for(i = 0 ; i < g->nodes ; i++){
    if(g->data[node][i] != 0){
      if(l==NULL){
        l = newList(i);
      } else {
        addToList(l, i);
      }
    }
  }
  return l;
}