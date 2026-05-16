#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 10
char stroka[NUM_THREADS + 1];
pthread_t tits[NUM_THREADS];
pthread_mutex_t bitch;

void* func(void* i){
    pthread_mutex_lock(&bitch);
    if (strlen(stroka) == 0) {
        stroka[0] = '0';
    }
    else{
        stroka[strlen(stroka)] = stroka[strlen(stroka) - 1] + 1;
    }
    pthread_mutex_unlock(&bitch);
    pthread_exit(NULL);
}



int main() {
    memset(stroka, '\0', strlen(stroka));
    pthread_mutex_init(&bitch, NULL);
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&tits[i], NULL, func, (void*)i);
    }
    pthread_join(tits[NUM_THREADS - 1], NULL);

    printf("%s", stroka);
    return 0;
}