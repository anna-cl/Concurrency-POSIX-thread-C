// $ gcc -o thread thread_example1.c
//https://www.classes.cs.uchicago.edu/archive/2018/spring/12300-1/threads1.c.txt
//https://www.mkssoftware.com/docs/man3/pthread_join.3.asp
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>


// ==== Bug Warning! ====
// https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/ThreadArgs.html
//--> Casting integral values to pointers and back again is a common practice for passing parameters to pthreads.
//However, while it is generally safe in practice, it is potentially a bug on some platforms. 
//Specifically, this technique relies on the fact that pointers are at least as large as standard integer types. 
//That is, int variables are typically (but not required to be) 32 bits in size. 
//Modern CPU architectures tend to use 32- or 64-bit addresses. As such, casting a 32-bit int up to a void* then back to a 32-bit int is safe.
//On the other hand, assume the argument was declared as a long variable instance. 
//If the code is running on a 32-bit architecture (which is not uncommon for virtualized systems) but the long type is 64 bits in size, 
//then half of the argument is lost by down-casting to the pointer for the call to pthread_create()!


// ==== create and join threads ====
//Three functions define the core functionality for creating and managing threads.
//The pthread_create() function will create and start a new thread inside a process. 
//The start_routine parameter specifies the name of the function to use as the thread’s entry point, 
//just as main() serves as the main thread’s entry point.
// The pthread_exit() is used to exit the current thread and optionally return a value. 
//Finally, the pthread_join() function is the thread equivalent of the wait() function for processes. 
//That is, calling pthread_join() on a child thread will cause the current (parent) thread to wait until the child finishes and calls pthread_exit().

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
// https://www.classes.cs.uchicago.edu/archive/2018/spring/12300-1/lab6.html
// This code demonstrates:
// How to create a thread
// How to pass an argument to a thread
// How to force C to accept an int into the generic void* parameter, by casting
// How to return a result from a thread
// How to use casting to work between the generic and the specific again here
// How to wait for a thread to complete, and get its return value
// void* func(void* x){
//     int xi = (int)x;//???
//     // int xi = *(int*)x;
//     printf("Inside thread: x= %d\n", xi);

//     return (void*)(xi+111);
// }

//3.Multithreading
// https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/ProcVThreads.html
// int num = 9; //global variable
// void* thread_A(void* args){
//     int x = 5;
//     printf("A: %d\n", x + num);//the kernal runs line 57 and line 58 is a thread
//     //Exit thread
// }

// void* thread_B(void* args){
//     int y = 10;
//     printf("B: %d\n", y + num);
//     //Exit thread
// }

//4.pthread example 3
//function pointer:
void *start_thred(void* args){
    printf("Hello from CHILD\n");
    pthread_exit(NULL);
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
    // pthread_t th; //the thread to wait for
    // pthread_create(&th, NULL, func, (void*)100);

    // void* ret_from_thread;//status;  the location where the exit status of the joined thread is stored. 
    //This can be set to NULL if the exit status is not required.
    // int ri;
    // pthread_join(th, &ret_from_thread);
    // ri = (int)ret_from_thread;

    // printf("Outside thread, which returned %d\n", ri);

    //3.Multithreading
    /* Create thread A */
    /* Create thread B */
    /* Wait for threads to finish */

    //4.pthread example 3
    //int pthread_create (pthread_t *thread, const pthread_attr_t *attr, 
        // void *(*start_routine)(void*), void *arg);
        // Create a new thread starting with at the start_routine function.
    pthread_t child_thread;
    
    // requests the allocation of resources for a new thread and returns 0 if the request is successful.
    assert (pthread_create(&child_thread, NULL, start_thred, NULL)==0);

    /* Wait for the child to finish, then exit */
    // int pthread_join (pthread_t thread, void **value_ptr);
        // wait for the thread running start_thread() to call pthread_exit()
    pthread_join(child_thread, NULL);
    //void pthread_exit (void *value_ptr);
        // Exit from the current thread.
    pthread_exit(NULL);
}
