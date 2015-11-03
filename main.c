#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "ford.h"

int main(int argc, char* argv[]){
  // To remove warnings ...
  argc = argc;
  argv = argv;

  graph* g = loadGraph(argv[1]);
  double flow = ford_fulkerson(g, 0, g->nodes - 1);
  printf("MaxFlow : %f \n",flow);
  return 0;
}