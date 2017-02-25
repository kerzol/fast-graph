Fast graph library
------------------

by [Sergey Kirgizov](http://kirgizov.link) and [Maximilien Danisch](http://perso.crans.org/danisch/max/home.html)


**`madmax.c`**
MADMAX algorithm, an approach to find a maximal subgraph with maximal
average degree (MAD).  We suppose that your graph is so big that it
doesn't fit into the memory.  So we are going to do some hardwork with
your hard drive.  More information will be added soon.

**`graph.c`**
contains a function that iterates over edges of a graph in edge list
format.  We use
[wc](http://git.savannah.gnu.org/gitweb/?p=coreutils.git;a=blob;f=src/wc.c;hb=HEAD)-like
approach: buffered
[`read(2)`](http://man7.org/linux/man-pages/man2/read.2.html) with
read-ahead hint, without any `fscanf`.


Before any tests do not forget to drop caches `sync && echo 3 > /proc/sys/vm/drop_caches`
Also, use `hdparm -Tt /dev/bla-bla-bla` to measure the "physical" limits of your hard drive.


## Compilation
`make`

## Toy-test over Zachary Karate Club
`./madmax graphs/Zachary.txt 100`

##_Stay tuned, amazing [stuff is coming!](TODO)_
