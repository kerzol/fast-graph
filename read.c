// read a graph in edge_list format into memory

#define BUFFER_SIZE (16 * 1024)
#define ALLOCATION_STEP 10000

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

edge* read_graph (char* filename, unsigned long long* n) {

  edge* edges = NULL;
  char buf[BUFFER_SIZE];
  int empty_edges = 0;
  unsigned long long n_lines = 0;
  uint32_t node_number = 0;
  ssize_t how_many = 0;
  int i;


  int fd = open (filename, O_RDONLY);
  posix_fadvise (fd, 0, 0, POSIX_FADV_SEQUENTIAL);
  
  while (1) {
    
    how_many = read (fd, buf, BUFFER_SIZE);
    if (how_many == 0) break;

    for (i = 0; i < how_many; i++) {

      // Here we consider that the file contains only
      // decimal digits separated by spaces and '\n'-s.
      if (buf[i] == ' ') {
        // reallocate if needed
        if (empty_edges == 0) {
          edges = realloc (edges,
                           (n_lines + ALLOCATION_STEP) *
                           sizeof(edge));
          empty_edges = ALLOCATION_STEP;
          if (edges == NULL) {
            printf ("realloc fails \n");
            exit (EXIT_FAILURE);
          }          
        }
        // store fist node of the link
        edges[n_lines].a = node_number;
        // and prepare to parse the following
        node_number = 0;
      } else if (buf[i] == '\n') {
        n_lines++;
        // store second node of the link
        edges[n_lines].b = node_number;
        empty_edges--;
        // and prepare to parse the following
        node_number = 0;
      } else {
        // continue parsing
        node_number = node_number * 10 + buf[i] - '0';
      }
    }

  }

  printf ("File %s contains %llu lines\n", filename, n_lines);
  
  //allocate
  edges = realloc (edges, n_lines * sizeof(edge));
  *n = n_lines;
  return (edges);
}

int my_atoi(char *p) {
    int k = 0;
    while (*p) {
        k = (k<<3)+(k<<1)+(*p)-'0';
        p++;
     }
     return k;
}

// only for testing purposes
int main (int argc, char** argv) {
  unsigned long long n;
  read_graph (argv[1], &n);
  printf ("%llu edges\n", n);
}
