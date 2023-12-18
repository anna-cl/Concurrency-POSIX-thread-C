// $ gcc -o thread thread_example1.c
// /https://www.classes.cs.uchicago.edu/archive/2018/spring/12300-1/threads1.c.txt
// https://www.classes.cs.uchicago.edu/archive/2018/spring/12300-1/lab6.html
//https://www.mkssoftware.com/docs/man3/pthread_join.3.asp
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

//1. pthread example 1 
void* print0s(void* arg){
    while (true)
    {
        printf("0");
    }
}

void* print1s(void* arg){
    while (true)
    {
        printf("1");
    }
}

//2. pthread example 2
// This code demonstrates:
// How to create a thread
// How to pass an argument to a thread
// How to force C to accept an int into the generic void* parameter, by casting
// How to return a result from a thread
// How to use casting to work between the generic and the specific again here
// How to wait for a thread to complete, and get its return value
void* func(void* x){
    int xi = (int)x;//???
    // int xi = *(int*)x;
    printf("Inside thread: x= %d\n", xi);

    return (void*)(xi+111);
}



int main(int argc, char** argv){
    //1. pthread example 1
    // pthread_t thread1, thread2;

    // pthread_create(&thread1, NULL, print0s, NULL);
    // pthread_create(&thread2, NULL, print1s, NULL);

    // void* result;

    // pthread_join(thread1, &result);
    // pthread_join(thread2, &result);

    
    //2. pthread example 2
    pthread_t th; //the thread to wait for
    pthread_create(&th, NULL, func, (void*)100);

    void* ret_from_thread;//status;  the location where the exit status of the joined thread is stored. 
    //This can be set to NULL if the exit status is not required.
    int ri;
    pthread_join(th, &ret_from_thread);
    ri = (int)ret_from_thread;

    printf("Outside thread, which returned %d\n", ri);

}
