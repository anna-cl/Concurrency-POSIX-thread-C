//---------- Continues from raceCondition_mutex.c ----------
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

//4. ** Boolean(Condition) to notify next thread **

//4. add another global variables:
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int value = 100;
bool notified = false; //notify next thread when previous thread is finished

//4.this is for next thread:
void* squareReporter(void* unused){
    pthread_mutex_lock(&mut);
    //once notified is true, the loop stops; next thread will start its mutex work.
    while (!notified)
    {
        //the wait() lets CPU to have a short "sleep" 
        //instead of wasting resource to run this "not-so-meaningful" while loop
        //it waits for notified True, also it waits for previous thread mutex mut to be unlocked
        pthread_cond_wait(&cond_var, &mut); 
    }
    printf("The value is %d\n", value);
    
    pthread_mutex_unlock(&mut);

    return NULL;
}

void* assigner(void* unused){ //for previous thread
    value = 20;

    pthread_mutex_lock(&mut);
    notified = true;
    pthread_cond_signal(&cond_var);
    pthread_mutex_unlock(&mut);

    return NULL;
}


int main(){

        //4.
    pthread_t report, assign;
    pthread_create(&report, NULL, squareReporter, NULL);

    
    void* unused;




    return 0;
}
