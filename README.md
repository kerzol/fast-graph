Fast graph library
------------------

by [Sergey Kirgizov](http://kirgizov.link) and [Maximilien Danisch](http://perso.crans.org/danisch/max/home.html)


**`read.c`** 
reads a graph in edge list format into memory.
We use [wc](http://git.savannah.gnu.org/gitweb/?p=coreutils.git;a=blob;f=src/wc.c;hb=HEAD)-like approach: buffered [`read(2)`](http://man7.org/linux/man-pages/man2/read.2.html) with read-ahead hint, without any `fscanf`.

Consider [this thread](http://stackoverflow.com/questions/17925051/fast-textfile-reading-in-c) for discussion about "fast textfile reading". 
Before any tests do not forget to drop caches `sync && echo 3 > /proc/sys/vm/drop_caches`
Also, use `hdparm -Tt /dev/bla-bla-bla` to measure the "physical" limits of your hard drive.
             

_Stay tuned, amazing stuff is coming!_