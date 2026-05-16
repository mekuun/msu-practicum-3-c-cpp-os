#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

void* func(void* arg){
    sleep(time(0) % 10);
    pthread_exit(NULL);
}


int main(){
    pthread_t bitch; int i;
    pthread_create(&bitch, NULL, func, (void *) i);
    time_t tm_start = time(0);
    pthread_join(bitch, NULL);
    printf("THREAD %#x EXEC TIME = %u", bitch, time(0) - tm_start);
    return 0;
}