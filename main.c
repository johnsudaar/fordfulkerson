#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main(int argc, char* argv[]){
  // To remove warnings ...
  argc = argc;
  argv = argv;

  graph* g = newGraph(2);
  setFlow(g,0,1,10);
  printf("%f\n", getFlow(g,0,1));
  return 0;
}