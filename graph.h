#ifndef FAST_GRAPH_H
#define FAST_GRAPH_H

#include <stdint.h>

typedef uint64_t node;
typedef uint64_t edge_count;
typedef uint64_t node_count;

typedef struct {
  node a;
  node b;
} edge;

typedef struct {
  edge_count edges;
  node_count nodes;
} graph_size;
// size of graph: total number of edges and links

typedef struct {
  double density;
  node* nodes;
  node_count size;
} dens_subgraph;
// contains a list of nodes together with density value


graph_size
read_graph_iterator (char* filename,
                     void (*do_one_edge_function)
                     (edge, edge_count));
// File should contain a graph in edge_list format:
//  an edge is a pair of nodes separated by one ' '
//  edges should be separated by '\n'
// Uses provided do_one_edge_function to do smth for every edge
//  the second argument of do_one_edge_function recives
//  a number of current edge
// do_one_edge_function can be NULL, in this case we do nothing
// for every edge
// UWAGA: number of nodes is just a max of nodes' ids  + 1

graph_size get_graph_size (char* filename);
// Iterates over a graph containing in a file in edge_list format
//  graph_size.links is a number of links
//  graph_size.nodes is just a max nodeid + 1

#endif
