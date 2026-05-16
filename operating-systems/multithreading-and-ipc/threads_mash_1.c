#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>


#define NUM_THREADS 10
int shared_c = 0;

void* func(void* arg){
    int local = 0;
    sleep(abs(5 - (int)arg));
    fprintf(stdout, "***Thread %#d with ID %#x : ahred val is %d, local val is %d\n", (int)arg, pthread_self() ,shared_c++, local++);
    fflush(stdout);
    return NULL;
}

int main(){
    pthread_t th_id;
    int i, err;
    for (i = 0; i < NUM_THREADS; i ++){
        err = pthread_create(&th_id, NULL, func, (void *)i);
        fprintf(stdout, "ID of bitch: %#x ", th_id);
    }
    sleep(10);
    return 0;
}