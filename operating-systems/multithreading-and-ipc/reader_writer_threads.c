#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#define SIZE 10
int rc = 0; //chislo odnov chitateley
time_t timestart;
pthread_mutex_t writr, readr, vyvod;

void* writer(void* i){
    pthread_mutex_lock(&writr);
    sleep(3);
    pthread_mutex_unlock(&writr);
    pthread_mutex_lock(&vyvod);
    printf("Писатель %#x завершился на %d секунде\n", pthread_self(), time(0) - timestart);
    pthread_mutex_unlock(&vyvod);
    return NULL;
}

void* reader(void* i){
    pthread_mutex_lock(&readr);
    rc++;
    if (rc == 1) pthread_mutex_lock(&writr);
    pthread_mutex_unlock(&readr);
    sleep(5);
    pthread_mutex_lock(&readr);
    rc--;
    if (rc == 0) pthread_mutex_unlock(&writr);
    pthread_mutex_lock(&vyvod);
    printf("Читатель %#x завершился на %d секунде\n", pthread_self(), time(0) - timestart);
    pthread_mutex_unlock(&vyvod);
    return NULL;
}


int main(){
    int nr, nw, bFlag;
    scanf("%d %d", &nr, &nw);
    pthread_t tid;
    timestart = time(0);
    bFlag = !(nr > 0); // если читателей 0 эта херь 1, иначе 0

    while (nr > 0 || nw >0) {
        pthread_create(&tid, NULL, bFlag ? writer : reader, NULL); //если чит больше нуля - чит, иначе пис
        pthread_mutex_lock(&vyvod);
        printf("запустили хуйню %s %#x на %d секунде\n", bFlag ? "Писатель" : "Читатель", tid, time(0) - timestart);
        pthread_mutex_unlock(&vyvod);
        bFlag = bFlag ? (nw--, nr == 0) : (nr--, nw);
    }
    while(1){sleep(1);}
    return 0;
}