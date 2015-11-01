#ifndef GRAPH_H
#define GRAPH_H

enum graph_errors {NODE_OUT_OF_RANGE};

typedef struct{
  int nodes;
  double **data;
} graph;

graph* newGraph(int nodes);

int setFlow(graph* g, int from, int to, double value);
double getFlow(graph* g, int from, int to);

#endif