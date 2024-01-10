#include <pthread.h>
#include <stdio.h>
#include<string.h>

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

//--- Global variables ---
char buffer[BUFLEN];
char source[BUFLEN];
int readCount = 0;
int writeCount = 0;
int buflen;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int thread_ids[NUMTHREADS] = {1,2,3};
int i, j = 0;

int main(){
    int i; //???

    pthread_t threads[NUMTHREADS];
    
    strcpy(source, "hello world!");
    buflen = strlen(source);

    //create consumer, producers


// join threads
    for (i = 0; i < NUMTHREADS; i++)
    {
        /* code */
    }

    return 0;
}

void* consumer(int* id){

    pthread_mutex_lock(&count_mutex);
    while (j < MAX) //50
    {
        pthread_mutex_wait(&empty, &count_mutex);
        printf(" Consumed value is:%c: by %d\n", buffer[readCount], *id);
        readCount = (readCount + 1)%BUFLEN;
        fflush(stdout); //flushes the output buffer of a stream
        j++;

        if (j < (MAX-2))
        {
            /* Last sleep might leave the condition un-processed.
	         * So we prohibit sleep towards the end
	        */
           if (rand()%100<30)
           {
            sleep(rand()%3);
           }
           
        }
    }
    /* signal the producer that the buffer has been consumed */
    /* pthread_cond_signal(&full);*/
    /* unlock the variable*/
    pthread_mutex_unlock(&count_mutex);

    return NULL;
}


void* producer(int* id){

    while (i < MAX)
    {
        pthread_mutex_lock(&count_mutex);
        /* wait for the buffer to have space */
        pthread_cond_wait(&full, &count_mutex);
        strcpy(buffer, "");
        buffer[writeCount] = source[writeCount%buflen];
        printf("%d produced :%c: by :%d:\n", i, buffer[writeCount], *id);
        fflush(stdout);
        writeCount = (writeCount+1)%BUFLEN;
        i++;

        //notify consumer:
        pthread_cond_signal(&empty);

        pthread_mutex_unlock(&count_mutex);

        if (i < (MAX - 2))
        {
            if (rand()%100>=30)
            {
                sleep(rand()%3);
            }
        }
        
    }
    


    return NULL;
}