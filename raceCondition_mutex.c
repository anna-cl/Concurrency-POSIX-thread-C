//https://www.classes.cs.uchicago.edu/archive/2018/spring/12300-1/lab6.html
//* Race condition *
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//global variable - accessible, shared, modifiable by all threads
int accum = 0;


void* square(void* _x){
    int x = (int) _x;
    accum += x*x;

    return NULL; /* nothing to return, prevent warning */
}


int main(int argc, char** argv){
    int i;

    pthread_t threadIDs[20];

    for (size_t i = 0; i < 20; i++)
    {
        /* code */
    }
    


    return 0;
}