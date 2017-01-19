#ifndef FAST_GRAPH_H
#define FAST_GRAPH_H

#include <stdint.h>

// nodes are from [0 to 4,294,967,295]
typedef struct {
  uint32_t a;
  uint32_t b;
} edge;

#endif

