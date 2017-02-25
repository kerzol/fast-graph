#define BUFFER_SIZE (16 * 1024)

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

graph_size
read_graph_iterator (char* filename,
                     void (*do_one_edge_function)
                       (edge, edge_count) ) {
  char buf[BUFFER_SIZE];
  graph_size gs = {.edges = 0, .nodes = 0};
  uint32_t node_number = 0;
  ssize_t how_many = 0;
  int i;
  edge one_edge;

  int fd = open (filename, O_RDONLY);
  posix_fadvise (fd, 0, 0, POSIX_FADV_SEQUENTIAL);
  while (1) {
    how_many = read (fd, buf, BUFFER_SIZE);
    if (how_many == 0) break;
    for (i = 0; i < how_many; i++) {
      // Here we consider that the file contains only
      // decimal digits separated by spaces and '\n'-s.
      if (buf[i] == ' ') {
        // store fist node of the link in temp variable
        one_edge.a = node_number;
        // and prepare to parse the following
        node_number = 0;
      } else if (buf[i] == '\n') {
        gs.edges++;
        // store second node of the link in temp variable
        one_edge.b = node_number;
        // call desired function
        if (do_one_edge_function != NULL)
          do_one_edge_function (one_edge, gs.edges);
        // count the number of nodes
        if (gs.nodes < one_edge.a)
          gs.nodes = one_edge.a;
        if (gs.nodes < one_edge.b)
          gs.nodes = one_edge.b;        
        // and prepare to parse the following
        node_number = 0;
      } else {
        // continue parsing
        node_number = node_number * 10 + buf[i] - '0';
      }
    }
  }
  gs.nodes++; //because nodes' ids start from 0
  close(fd);
  return gs;
}

graph_size get_graph_size (char* filename) {
  return read_graph_iterator (filename, NULL);
}


