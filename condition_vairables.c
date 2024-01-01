//---------- Continues from raceCondition_mutex.c ----------
//reference: https://www.classes.cs.uchicago.edu/archive/2018/spring/12300-1/lab6.html
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

//4. for next thread:
void* reporter(void* unused){
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

//5.**  Producer-consumer problem **

//You should now have all the tools needed to fix an instance of the producer-consumer problem. 
//Simply put, one thread is producing goods and another thread is consuming goods. 
//We want the consumer thread to wait using a condition variable, 
//and we want adding something to the list of available goods to be mutually exclusive to removing it, 
//so are data doesn't get corrupted. We are letting c++ and c-- be surrogates for items being produced and consumed. 
//In other words, the producer generates another item that is being counted by c, and the consumer uses it, decrementing c. 
//(We use this proxy so that we don't clutter the code with actual list manipulation statements.) 
//We can easily check if we correctly end up with 0 in the end. Run the code as it is, 
//and you will see that the net value can be way off (though you may get lucky some of the time):



int main(){

    //4.
    pthread_t report, assign;
    pthread_create(&report, NULL, reporter, NULL);
    pthread_create(&assign, NULL, assigner, NULL);
    
    void* unused;

    pthread_join(report, &unused);
    pthread_join(assign, &unused);

    return 0;
}
