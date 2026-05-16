#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>


#define NUM_THREADS 10
int pppp = 0;
pthread_t tids[NUM_THREADS];

void* func(void* i){
    int local = 0;
    sleep(abs(5 - (int)i));
    local ++;
    fprintf(stdout, "tid %d number %d shared %d local %d\n", (unsigned int) pthread_self(), (int)i, pppp, local);
    fflush(stdout);
    pppp += 1;
    return NULL;
}

int main(){
    for (int i = 0; i < NUM_THREADS; i ++){
        pthread_create(&tids[i], NULL, func, (void *)i);
        //fprintf(stdout, "%lu", (unsigned long)tids[i]);
    }
    sleep(10);
    return 0;
}