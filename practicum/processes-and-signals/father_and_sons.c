#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/wait.h>


int main(){
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    };

    struct sembuf block_daddy = {0, -1, 0}, unblock_daddy = {0, 1, 0},
            block_son1 = {1, -1, 0}, unblock_son1 = {1, 1, 0},
            block_son2 = {2, -1, 0}, unblock_son2 = {2, 1, 0},
            finish = {3, 1, 0};


    key_t key=ftok("/etc/passwd", ':');
    if(key<0) {perror("ftok error"); exit(1);}

    int semid = semget(key, 4, IPC_CREAT | 0666); //semaphore creation
    if (semid<0) {perror("semget error"); exit(1);}

    semctl(semid, 0, SETVAL, 0); //initializaton
    semctl(semid, 1, SETVAL, 0); //initializaton
    semctl(semid, 2, SETVAL, 0); //initializaton
    semctl(semid, 3, SETVAL, 0); //initializaton


    int shmid;
    int *shmaddr = NULL;
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0666); //shmem creation
    if (shmid<0) {perror("shmget error"); exit(1);}

    shmaddr = (int*)shmat(shmid, NULL, 0); //shared memory address
    if (shmaddr<0) {perror("shmat error"); exit(1);}


    if (!fork()) { //we are in first baby
        int sum = 0;
        while(1){
            semop(semid, &block_son1, 1);
            if (semctl(semid, 3, GETVAL) == 1) break;
            sum += *shmaddr;
            semop(semid, &unblock_daddy, 1);
        }
        printf("son1: %d\n", sum);
        fflush(stdout);
        return 0;
    }

    if (!fork()){ //we are in the second baby
        int sum = 0;
        while(1){
            semop(semid, &block_son2, 1);
            if (semctl(semid, 3, GETVAL) == 1) break;
            sum += *shmaddr;
            semop(semid, &unblock_daddy, 1);
        }
        printf("son2: %d\n", sum);
        fflush(stdout);
        return 0;
    }

    *shmaddr = 0;
    int flag = 1;
    while (scanf("%d", shmaddr) > 0){
        flag ++;
        if (flag % 2 == 0){
            semop(semid, &unblock_son1, 1);
            semop(semid, &block_daddy, 1);
        }
        else{
            semop(semid, &unblock_son2, 1);
            semop(semid, &block_daddy, 1);
        }
    }
    semop(semid, &finish, 1);
    semop(semid, &unblock_son1, 1);
    wait(NULL);
    semop(semid, &unblock_son2, 1);
    wait(NULL);
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, 0);
    semctl(semid, IPC_RMID, 0);
    return 0;
}