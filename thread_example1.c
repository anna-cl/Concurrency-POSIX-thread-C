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

//6.Thread id, sleep(), pthread_exit(), pthread_join()
// $ gcc thread_example2.c  -o example2 -lpthread
// http://www.csc.villanova.edu/~mdamian/threads/posixthreads.html
// https://www.youtube.com/watch?v=KEiur5aZnIM&t=9s

void* printHello(void* data){
    //6.1 ===========
    int my_data = (int)data; /* data received by thread */ //-------

    //At any point in time, a thread is either joinable or detached (default state is joinable). 
    //Joinable threads must be reaped or killed by other threads (using pthread_join) in order to free memory resources. 
    //Detached threads cannot be reaped or killed by other threads, and resources are automatically reaped on termination. 
    //So unless threads need to synchronize among themselves, it is better to call
    // pthread_detach(pthread_self()); instead of pthread_join.
    pthread_detach(pthread_self()); //-------
    
    //thread sleeps for 1 second and then resume execution 
    //(we are trying to make this thread finish after the main thread)
    // sleep(3); //-------
    
    printf("6.1-->Hello from new thread %u - received data: %d\n", pthread_self(),  my_data);//-------

    //6.2 ===========
    //The pthread_join() function for threads is the equivalent of wait for processes. 
    //A call to pthread_join blocks the calling thread until the thread with identifier equal to the first argument terminates.
    pthread_t tid = (pthread_t)data;
    pthread_join(tid, NULL); /* wait for thread tid */
    printf("6.2-->Hello from new thread %u - received data: %d\n", pthread_self(), data);

    pthread_exit(NULL);/* terminate the thread, the equivalent of exit for processes */

}

//7.create N threads:  http://www.csc.villanova.edu/~mdamian/threads/posixthreads.html
// Create a number N threads specified in the command line, 
// each of which prints out a hello message and its own thread ID. 
// To see how the execution of the threads interleaves, make the main thread sleep for 1 second for every 4 or 5 threads it creates. 
// The output of your code should be similar to:
/*       
       I am thread 1. Created new thread (4) in iteration 0...
       Hello from thread 4 - I was created in iteration 0
       I am thread 1. Created new thread (6) in iteration 1...
       I am thread 1. Created new thread (7) in iteration 2...
       I am thread 1. Created new thread (8) in iteration 3...
       I am thread 1. Created new thread (9) in iteration 4...
       I am thread 1. Created new thread (10) in iteration 5...
       Hello from thread 6 - I was created in iteration 1
       Hello from thread 7 - I was created in iteration 2
       Hello from thread 8 - I was created in iteration 3
       Hello from thread 9 - I was created in iteration 4
       Hello from thread 10 - I was created in iteration 5
       I am thread 1. Created new thread (11) in iteration 6...
       I am thread 1. Created new thread (12) in iteration 7...
       Hello from thread 11 - I was created in iteration 6
       Hello from thread 12 - I was created in iteration 7
*/
    void* printEachthreads(void* _data){
        int i = (int)_data;

        pthread_t tid = (pthread_t) _data;
        pthread_join(tid, NULL); //no join in solution, but it's better to have join() because it waits for 
        //each thread to execute and finish.

        printf("Hey from thread %u - I was created in iteration %d!\n", tid, i);
        // printf("Hello from thread %u, %u - I was created in iteration %d!\n", (int)pthread_self(), tid, i);

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
    // pthread_t th; //thread id, the thread to wait for
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
        // assert(pthread_create(&child_threads[i], NULL, child_thread2, (void*)i) == 0); //pass-by-value //--------
    // }
    

    //6.Thread id, sleep(), pthread_exit(), pthread_join()
    // pthread_t test_id;
    // //A thread can get its own thread id by calling pthread_self(), which returns the thread id
    // test_id = pthread_self();

    // int create_return_value;
    // pthread_t pthread_id; /* thread's ID (just an integer-memory address)*/
    // int data = 5555; /* data passed to the new thread */

    // create_return_value = pthread_create(&pthread_id, NULL, printHello, (void*)data);

    // if (create_return_value)
    // {
    //     printf("\nERROR: return code from pthread_create is %d\n", create_return_value);
    //     exit(1);//terminate entire program at here
    // }

    // printf("-->I am thread id %u.\n", test_id);
    // sleep(3);
    // printf("-->Created new thread(%u) ... \n", pthread_id);//format specifier %u (unsigned) to print out the thread identifier

    // //IMPORTANT: It is necessary to use pthread_exit at the end of the main program. 
    // //Otherwise, when it exits, all running threads will be killed.
    // pthread_exit(NULL); //------------
    // //6.1.1try: comment out this when sleep(3) added in printHello(), the sleeping thread printHello() will not print
    // //6.1.2try: uncomment this pthread_exit(NULL); and comment out pthread_exit(NULL); in printHello(),
    // // Also add the sleep call to the main routine, just before the second printf call, 
    // //and remove it from the PrintHello routine (so now the main thread finishes last)


    //7.printNthreads
    # define MAX_THREADS 50
    pthread_t thread_ids[MAX_THREADS];
    pthread_t test_thread; //just a pthread type variable, no pthread created
    if(argc == 2){
        int nThreads = atoi(argv[1]); //number of threads

        if(nThreads <= MAX_THREADS){
            for (int i = 0; i < nThreads; i++)
            {
                pthread_create(&(thread_ids[i]), NULL, printEachthreads, (void*)i);
                printf("\n-->Main: First pthread variable id %u(not pthread created). --> Second pthread variable  %u(not pthread created)."
                    "Created new thread (%u) in iteration %d...\n", (int)test_thread, (int)pthread_self(), (int)thread_ids[i], i);

                if (i%5 == 0)
                {
                    sleep(2);
                }
                
            } 

        }else{
            printf("Max threads are 50.\n");
            exit(1);
        }

    }else{
        printf("Argc: %d\n", argc);
    }

    pthread_exit(NULL); 

}
