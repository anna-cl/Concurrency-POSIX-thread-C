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

//should move function headers to .h file
void* consumer(int* id);
void* producer(int* id);

char buffer[BUFLEN];
char source[BUFLEN];
int readCount = 0;
int writeCount = 0;
int buflen;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int main(){

    return 0;
}