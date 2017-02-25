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

#define MAX(a,b) (((a)>(b))?(a):(b))

static int* X = NULL;
// madmax scores

static void madmax_iteration (edge e, edge_count ec) {
  // UWAGA! uses a global variable X
  if (X[e.a] <= X[e.b]) {
    X[e.a]++;
  } else {
    X[e.b]++;
  }
}
void madmax_score (char* gf, graph_size gs, int max_iter) {
  // gf is a name of a file that contains an edge list
  //  an edge is a pair of nodes separated by one ' '
  //  every node is a uint64_t number
  //  edges should be separated by '\n'
  X = (int*) calloc (gs.nodes, sizeof(int)); // UWAGA! don't forget to free 
  int t;
  for (t = 0; t < max_iter; t++) {
    read_graph_iterator (gf, madmax_iteration);
  }
}

static node_count* RANK_OF_NODE = NULL;
static edge_count* E = NULL;
static void madmax_sweep_iteration (edge e, edge_count ec) {
  node_count m  = MAX ( RANK_OF_NODE[e.a], RANK_OF_NODE[e.b]);
  E[m]++;
}
static int inderect_compare(const void *a, const void *b) {
  // pass this to qsort over an array of indexes
  // argsort
    node_count i = *(const node_count *)a;
    node_count j = *(const node_count *)b;
    
    /* Avoid return x - y, which can cause undefined behaviour
       because of signed integer overflow. */
    if (X[i] < X[j]) return  1;
    if (X[i] > X[j]) return -1;
    return 0;
}
dens_subgraph madmax_densest_subgraph (char* gf, graph_size gs) {
  // UWAGA! use of a global variable X, should contain a result of madmax_score
  // gf is a name of a file that contains an edge list
  // Returns a list of nodes and corresponding density (MAD)
  //  of an induced subgraph.
  node_count i;
  node_count* node_of_rank;

  node_of_rank = (node_count*) calloc (gs.nodes, sizeof(node_count));
  RANK_OF_NODE = (node_count*) calloc (gs.nodes, sizeof(node_count));
  E = (edge_count*) calloc (gs.nodes, sizeof(edge_count));

  // sort nodes in non decreasing order of X-scores
  // prepare an array of indexes
  for (i = 0; i < gs.nodes; i++)
    node_of_rank[i] = i;
  // sort this array using a comprator that compares original values
  qsort (node_of_rank, gs.nodes, sizeof(node_count), inderect_compare);

  for (i = 0; i < gs.nodes; i++) {
    RANK_OF_NODE [ node_of_rank[i] ] = i;
  }

  read_graph_iterator (gf, madmax_sweep_iteration);

  node_count size = 0;
  double tmp_density = 0;
  double density = 0;
  edge_count totale = 0;
  for (i = 0; i < gs.nodes; i++) {
    totale = totale + E[i];
    tmp_density = totale / (i + 1.0);
    if (tmp_density > density) {
      density = tmp_density;
      size = i+1;
    }
  }

  
  dens_subgraph ds;
  ds.density = density;
  ds.size = size;
  ds.nodes = realloc (node_of_rank, size * sizeof(node_count));

  free (RANK_OF_NODE);
  free (E);
  return ds;
}


// only for testing purposes
int main (int argc, char** argv) {
  char* gf = argv[1];
  int max_iter = atoi(argv[2]);
  
  graph_size gs = get_graph_size(gf);
  
  madmax_score(gf, gs, max_iter);
  printf ("%ld nodes, %ld edges in graph\n", gs.nodes, gs.edges);
  printf ("Madmax scores:\n");
  node_count i;
  for (i = 0; i < gs.nodes; i++) {
    printf ("%d <== %lu\n", X[i], i);
  }
  
  dens_subgraph ds = madmax_densest_subgraph (gf, gs);
  printf ("Subgraph of density %f contais following nodes: ", ds.density);
  for (i = 0; i < ds.size; i++) {
    printf ("%lu ", ds.nodes[i]);
  }
  printf ("\nBye.\n");
  free (X);
  free (ds.nodes);
}

