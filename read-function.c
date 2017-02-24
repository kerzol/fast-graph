// read a graph in edge_list format into memory

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#define ALLOCATION_STEP 10000
int EMPTY_EDGES = 0;
edge* EDGES = NULL;
void do_one_edge (edge one_edge, edge_count n_lines) {
  // reallocate if needed
  if (EMPTY_EDGES == 0) {
    EDGES = realloc (EDGES,
                     (n_lines + ALLOCATION_STEP) *
                     sizeof(edge));
    EMPTY_EDGES = ALLOCATION_STEP;
    if (EDGES == NULL) {
      printf ("realloc fails \n");
      exit (EXIT_FAILURE);
    }          
  }
  // store temp variable in real one
  EDGES[n_lines-1] = one_edge;        
  EMPTY_EDGES--;
}


// only for testing purposes
int main (int argc, char** argv) {
  graph_size gs;
  gs = read_graph_iterator (argv[1], do_one_edge);
  EDGES = realloc (EDGES, gs.edges * sizeof(edge));
  printf ("%lu edges\n", gs.edges);
  printf ("%lu nodes\n", gs.nodes);
  printf ("1 edge = %lu %lu\n", EDGES[0].a, EDGES[0].b);
  printf ("2 edge = %lu %lu\n", EDGES[1].a, EDGES[1].b);
  
}
