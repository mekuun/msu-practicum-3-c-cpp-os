#include<stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/msg.h>

void signal_hndlr(int s){
    signal(SIGUSR1, signal_hndlr);
}

int main(){
    int fd[2];
    pipe(fd);
    int N, step, numb, index;
    scanf("%d %d", &N, &step);
    signal(SIGUSR1, signal_hndlr);

    int son_pid = fork();

    if (son_pid == 0){
        pause();
        for (int i = N-1;; i-=step){
            write(fd[1], &i, sizeof(int));
            kill(getppid(), SIGUSR1);
            if (i < 0) {
                exit(0);
            }
            pause();
            read(fd[0], &numb, sizeof(int));
            printf("son: %d\n", numb);
            fflush(stdout);
        }
    }
    int *array = (int*) malloc(N*sizeof(int));

    for (int i = 0; i < N; ++i){
        scanf("%d", &array[i]);
    }
    kill(son_pid, SIGUSR1);
    while(1){
        pause();
        read(fd[0], &index, sizeof(int));
        printf("dad: %d\n", index);
        fflush(stdout);
        if (index < 0) {
            close(fd[0]);
            close(fd[1]);
            free(array);
            wait(NULL);
            exit(0);
        }
        numb = array[index];
        write(fd[1], &numb, sizeof(int));
        kill(son_pid, SIGUSR1);
    }


}