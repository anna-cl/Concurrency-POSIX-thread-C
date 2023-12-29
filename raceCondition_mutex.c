//*** Race condition ***

//Defination: 
//A race condition occurs when two or more processes or threads access shared data(e.g. global variables) or resources concurrently 
//and the outcome depends on the order in which they execute. 
//In other words, the result of the operation depends on the timing of the execution, 
//which can lead to unpredictable behavior and data corruption.


//https://www.classes.cs.uchicago.edu/archive/2018/spring/12300-1/lab6.html

//1.
//$ gcc raceCondition_mutex.c -Wno-int-to-void-pointer-cast -o race -lpthread
//$ for i in {1..49}; do ./race.out; done   //run this. Chances are it spits out 2870, which is the correct answer.
//$ for i in {1..1000}; do ./race; done|sort|uniq -c       
//--- definitely see plenty of incorrect answers, 
//even though most of the time it gets it right. 
//This is because of something called a race condition. When the compiler processes accum += x * x;, 
//reading the current value of accum and setting the updated value is not an atomic (meaning indivisible不可分割的) event. 
//Let's re-write square to capture this in 2.


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define MAX_THREADS 20

//1. Will cause race condition, bad
//global variable - accessible, shared, modifiable by all threads
int accum = 0;

//1.
void* square(void* _x){
    int x = (int) _x;
    accum += x*x;

    return NULL; /* nothing to return, prevent warning */
}

//2.Try to rewrite square() to fix race condition:
//this second version looks different, the fact is that when you compile the earlier version, 
//it needs to do these intermediate steps as well. There is no practical difference between these versions, 
//other than that this new version makes explicit the steps that were implicit, but still present, in the prior version.
void* squareRewrite(void* _x){
    int temp = accum;
    temp += (int)_x * (int)_x;
    accum = temp;

    return NULL;
}

//1. and 2.
// let's say the first two threads are interleaved over time, giving us something like this:

// Thread 1             // Thread 2
// int temp1 = accum;      int temp2 = accum;          // temp1 = temp2 = 0
//                         temp2 += 2 * 2;             // temp2 = 4
// temp1 += 1 * 1;                                     // temp1 = 1
//                         accum = temp1;              // accum = 1
// accum = temp2;                                      // accum = 4

// We end up with accum as 4, instead of the correct 5.



int main(int argc, char** argv){

    pthread_t threadIDs[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; i++)
    {
        // pthread_create(&threadIDs[i], NULL, square, (void*)(i+1));        
        pthread_create(&threadIDs[i], NULL, squareRewrite, (void*)(i+1));        

        printf("%d.thread created \n", i);
    }
    
    for (int i = 0; i < MAX_THREADS; i++)
    {
        void* result;
        printf("%d.thread joining: \n", i);
        //** Important**
        //1. call join() on all our threads, which is a blocking operation that waits for the thread to finish, 
        //before continuing the execution. Without join() to wait, the some threads will be skipped!
        //2. This is important to do before we print accum, since otherwise our threads might not be done yet. 
        //You should always join your threads before leaving main
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