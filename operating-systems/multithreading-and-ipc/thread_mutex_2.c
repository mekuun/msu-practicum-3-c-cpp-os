#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>
#define NUM_THR 10
#define MASS_LENGTH 40


pthread_mutex_t bitch;
pthread_t tits[NUM_THR];
int pipi = 0;
int pupu[MASS_LENGTH];

void* func(void* i){
	pthread_mutex_lock(&bitch);
	for (int j = (int)i; j < (int)i + MASS_LENGTH / NUM_THR; j ++){
	    pupu[j] = pipi;
	}
    pipi ++;
    for(int j = 0; j < MASS_LENGTH; j ++){
        printf("%d", pupu[j]);
    }
    printf("\n");
    fflush(stdout);
    pthread_mutex_unlock(&bitch);
	return NULL;
}



int main(){
    pthread_mutex_init(&bitch, NULL);

    int i = MASS_LENGTH / NUM_THR;
    for (int i = 0; i < MASS_LENGTH; i += MASS_LENGTH / NUM_THR){
	    pthread_create(&tits[i], NULL, func, (void*)i);
    }


    while(pipi != NUM_THR - 1){sleep(1);}
    return 0;


}
