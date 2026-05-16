#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

void signal_hndlr_DAD(int s) {
    signal(SIGUSR1, signal_hndlr_DAD);
}

void signal_hndlr_SON(int s) {
    signal(SIGUSR1, signal_hndlr_SON);
}


int main() {
    int n, count = 0, first_baby_PID, second_baby_PID, third_baby_PID;
    key_t key = ftok("/", 1113);
    signal(SIGUSR1, signal_hndlr_DAD);
    int shmid;
    char *shmaddr = NULL;
    shmid = shmget(key, 256 * sizeof(char), IPC_CREAT | 0666);
    shmaddr = (char *) shmat(shmid, NULL, 0);
    shmaddr[0] = '\0';

    first_baby_PID = fork();
    if (!first_baby_PID) { //second son
        signal(SIGUSR1, signal_hndlr_SON);
        while (1) {
            pause();
            shmaddr[strlen(shmaddr)] = 'a' + count % 26;
            shmaddr[strlen(shmaddr)] = '\0';
            count++;
            printf("son1: %s\n", shmaddr);
            fflush(stdout);
            kill(getppid(), SIGUSR1);
        }
    }

    second_baby_PID = fork();
    if (!second_baby_PID) { //first son
        signal(SIGUSR1, signal_hndlr_SON);
        while (1) {
            pause();
            shmaddr[strlen(shmaddr)] = '0' + count % 10;
            shmaddr[strlen(shmaddr)] = '\0';
            count++;
            printf("son2: %s\n", shmaddr);
            fflush(stdout);
            kill(getppid(), SIGUSR1);
        }
    }


    third_baby_PID = fork();
    if (!third_baby_PID) { //third son
        signal(SIGUSR1, signal_hndlr_SON);
        while (1) {
            pause();
            shmaddr[strlen(shmaddr)] = 'A' + count % 26;
            shmaddr[strlen(shmaddr)] = '\0';
            count++;
            printf("son3: %s\n", shmaddr);
            fflush(stdout);
            kill(getppid(), SIGUSR1);
        }
    }

    scanf("%d", &n);

    int i;
    for (i = 0; i < n; i++) {
        switch (i % 3) {
            case 0:
                kill(first_baby_PID, SIGUSR1);
                break;
            case 1:
                kill(second_baby_PID, SIGUSR1);
                break;
            case 2:
                kill(third_baby_PID, SIGUSR1);
                break;
        }
        pause();
    }
    kill(first_baby_PID, SIGTERM);
    kill(second_baby_PID, SIGTERM);
    kill(third_baby_PID, SIGTERM);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    printf("father: %s\n", shmaddr);
    fflush(stdout);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}