// $ gcc -o thread thread_example1.c
//https://www.classes.cs.uchicago.edu/archive/2018/spring/12300-1/threads1.c.txt
//https://www.mkssoftware.com/docs/man3/pthread_join.3.asp
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h> //unsigned sleep(unsigned seconds);


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
//     int xi = (int)x;//pthread needs to pass-by-value, not pass-by-reference
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
    printf("Hello from CHILD1\n");
    pthread_exit(NULL);
}

//5.passing a single argument to threads
// https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/ThreadArgs.html
void *child_thread2(void* args){

    /* POTENTIALLY DANGEROUS TIMING -- also leads to Seg fault 11 */
    // int* argPtr = (int*) args;
    // int arg = *argPtr;


    /* Safe whenever size of int <= size of pointer (which is
     usually true) */
     int arg = (int) args; // pass-by-value


    /* Print the local copy of the argument */
    printf("Local argument: %d\n", arg);
    pthread_exit(NULL);
}

//6.Thread id, sleep()
// $ gcc thread_example2.c  -o example2 -lpthread
// http://www.csc.villanova.edu/~mdamian/threads/posixthreads.html
// https://www.youtube.com/watch?v=KEiur5aZnIM&t=9s

void* printHello(void* data){
    int my_data = (int)data; /* data received by thread */

    //A thread can get its own thread id by calling pthread_self(), which returns the thread id
    pthread_detach(pthread_self()); //????
    
    //thread sleeps for 1 second and then resume execution 
    //(we are trying to make this thread finish after the main thread)
    sleep(3); 
    
    printf("-->Hello from new thread %u - received data: %d\n", pthread_self(),  my_data);
    pthread_exit(NULL);/* terminate the thread, the equivalent of exit for processes */
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
    // pthread_t child_thread;
    // pthread_t child_threads[10];


    //int pthread_create (pthread_t *thread, const pthread_attr_t *attr, 
    // void *(*start_routine)(void*), void *arg);
        // Create a new thread starting with at the start_routine function.
        // requests the allocation of resources for a new thread and returns 0 if the request is successful.
    // assert (pthread_create(&child_thread, NULL, start_thred, NULL)==0);//--------

    /* Wait for the child to finish, then exit */
    // int pthread_join (pthread_t thread, void **value_ptr);
        // wait for the thread running start_thread() to call pthread_exit()
    // pthread_join(child_thread, NULL);//--------
    //void pthread_exit (void *value_ptr);
        // Exit from the current thread.
    // pthread_exit(NULL);//--------

    //5.passing a single argument to threads
    // printf("\nChild_thread2 function\n");
    // for (int i = 1; i <= 10; i++)//--------
    // {
        /* BAD CODE - DON'T DO THIS */
        /* What value is actually passed to the thread? */
        // The key problem is that thread creation and execution is asynchronous. That means that it is impossible to predict when each of the new threads start running. 
        // One possible timing is that all 10 threads are created first, leading to i storing the value 11. 
        // At that point, each of the threads dereference their respective argptr variable and all get the same value of 11.

        // assert (pthread_create (&child[i], NULL, child_thread, &i) == 0);

        /* FIXED VERSION */
        /* ints are passed by value, so a COPY gets passed to each call */
        // Each thread should be given a separate value, rather than a shared address
        // One common solution to this problem is to cast numeric values as pointers. 
        // That is, the int i variable gets cast as a (void*) argument in the call to pthread_create(). 
        // Then, the void* argument to child_thread() casts the argument back to a int instance.
        // printf("%d --> ", i); //--------
        // assert(pthread_create(&child_threads[i], NULL, child_thread2, (void*)i)==0); //pass-by-value //--------
    // }
    

    //6.Thread id, sleep()
    pthread_t test_id;
    test_id = pthread_self();

    int create_return_value;
    pthread_t pthread_id; /* thread's ID (just an integer-memory address)*/
    int data = 100; /* data passed to the new thread */

    create_return_value = pthread_create(&pthread_id, NULL, printHello, (void*)data);

    if (create_return_value)
    {
        printf("\nERROR: return code from pthread_create is %d\n", create_return_value);
        exit(1);//terminate entire program at here
    }
    printf("-->I am thread id %u. Created new thread(%u) ... \n", test_id, pthread_id);//format specifier %u (unsigned) to print out the thread identifier

    pthread_exit(NULL);

   

}
