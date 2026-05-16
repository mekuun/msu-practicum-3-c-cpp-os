#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<math.h>
#include<unistd.h>
#include<sys/wait.h>



int main(int argc, char **argv){

    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    };
    if (argc != 5) return 1;
    int shmid, p = atoi(argv[1]), k = atoi(argv[4]);
    double  x = atof(argv[2]), s = atof(argv[3]);
    double *shmaddr=NULL;
    struct sembuf block = {0,-1,0}, unblock = {0,1,0};
    key_t key;
    if ((key = ftok("/", 110)) < 0) { perror("ftok"); return 1;}; //ÐºÐ»ÑŽÑ‡Ð¸Ðº

    int semid = semget(key, 1, IPC_CREAT | 0666); //ÑÐ¾Ð·Ð´Ð°ÐµÐ¼ ÑÐ¼Ð°Ñ„Ð¾Ñ€
    semctl(semid, 0, SETVAL, 0);
    int i;
    for (i=0;i < p; i++)
        if(!fork()) {
            semop(semid, &block, 1);
            shmid = shmget(key, sizeof(int), 0666);
            shmaddr = (double *) shmat(shmid, NULL, 0);
            for (int j = 0; j < k + 1; j++) {
                shmaddr[(k + 1) * i + j] = cos((x + j * s) * (i + 1) / p * M_PI);
            }
            shmdt(shmaddr);
            semop(semid, &unblock, 1);
            return 0;
        }
    else{
        if (i == 0){
            shmid = shmget(key, sizeof(double) * p * (k + 1), IPC_CREAT | 0666);
            shmaddr = (double*)shmat(shmid, NULL, 0);
            semop(semid, &unblock, 1);
        }
        wait(NULL);
    }
    for (int m = 0; m < p; m++){
        for(int n = 0; n < k + 1; n++){
            fprintf(stdout, "%.10g ", shmaddr[m * (k + 1) + n]);
        }
            fprintf(stdout, "\n");
        }
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}