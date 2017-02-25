CFLAGS=-Wall -O3

all: madmax read-function

madmax: madmax.c graph.o
	gcc $(CFLAGS) -o madmax madmax.c graph.o

read-function: read-function.c graph.o
	gcc $(CFLAGS) -o read-function read-function.c graph.o

graph.o: graph.c graph.h
	gcc $(CFLAGS) -c graph.c
