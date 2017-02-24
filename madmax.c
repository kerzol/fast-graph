// Sergey Kirgizov's implementation of
// Maximilien Danisch's algorithm that finds
// maximal subgraph with maximal average degree (MAD)
// UWAGA! in this file density means MAD.

// We suppose that your graph is so big
// that it doesn't fit into the memory.
// So we are going to do some hardwork with your hard drive.

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

static int* X;
graph_size GS;

void madmax_iteration (edge e, edge_count ec) {
  if (X[e.a] <= X[e.b]) {
    X[e.a]++;
  } else {
    X[e.b]++;
  }
}

void madmax_score (char* gf, int max_iter) {
  // gf is a name of a file that contains an edge list
  //  an edge is a pair of nodes separated by one ' '
  //  every node is a uint64_t number
  //  edges should be separated by '\n'
  // get the size of graph
  GS = read_graph_iterator (gf, NULL);
  // allocate and initialize 
  X = (int*) calloc (GS.nodes, sizeof(int));
  int t;
  for (t = 0; t < max_iter; t++) {
    read_graph_iterator (gf, madmax_iteration);
  }
}

//dens_subgraph madmax_densest (node* scores, char* gf) {
  // scores is a result of madmax_score
  // gf is a name of a file that contains an edge list
//TODO:
//}


// only for testing purposes
int main (int argc, char** argv) {
  char* gf = argv[1];
  int max_iter = atoi(argv[2]);
  madmax_score(gf, max_iter);
  //  dens_subgraph = madmax_densest (X, gf);

  int i;
  for (i = 0; i < GS.nodes; i++) {
    printf ("%d <== %d\n", X[i], i);
  }


}

