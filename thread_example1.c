// $ gcc -o thread thread_example1.c
// /https://www.classes.cs.uchicago.edu/archive/2018/spring/12300-1/threads1.c.txt
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

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

int main(int argc, char** argv){
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, print0s, NULL);
    pthread_create(&thread2, NULL, print1s, NULL);

    void* result;

    pthread_join(thread1, &result);
    pthread_join(thread2, &result);
}
