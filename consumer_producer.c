#include <pthread.h>
#include <stdio.h>

// https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/ProdCons.html
// 8.3.1. Producer-Consumer with Unbounded Queue





// https://www.eg.bucknell.edu/~xmeng/Course/CS4334/Example/Pthread/producer-consumer.c
/* It illustrates the idea of shared memory programming */
/* oct-03-2000 */
#define MAX 50
#define BUFLEN 24
#define MAX_COUNT 15
#define NUMTHREADS 3

