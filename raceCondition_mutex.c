//https://www.classes.cs.uchicago.edu/archive/2018/spring/12300-1/lab6.html
//* Race condition *
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define MAX_THREADS 20

//global variable - accessible, shared, modifiable by all threads
int accum = 0;


void* square(void* _x){
    int x = (int) _x;
    accum += x*x;

    return NULL; /* nothing to return, prevent warning */
}


int main(int argc, char** argv){

    pthread_t threadIDs[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; i++)
    {
        pthread_create(&threadIDs[i], NULL, square, (void*)(i+1));        
        printf("%d.thread created \n", i);
    }
    
    for (int i = 0; i < MAX_THREADS; i++)
    {
        void* result;
        printf("%d.thread joining: \n", i);
        //** Important: call join() on all our threads, which is a blocking operation that waits for the thread to finish, 
        //before continuing the execution. Without join() to wait, the some threads will be skipped!
        pthread_join(threadIDs[i], &result); //&result - address of a void pointer
    }

    int sumSquare = 0;
    for (int i = 0; i < MAX_THREADS; i++)
    {
        sumSquare += (i+1)*(i+1);
    }

    printf("Result, accum = %d\n", accum);
    printf("No thread, sum = %d\n", sumSquare);




    return 0;
}