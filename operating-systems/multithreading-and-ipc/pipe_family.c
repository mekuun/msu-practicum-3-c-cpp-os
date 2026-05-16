#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>


int main(){
    int fd[2];
    pipe(fd);
    if (fork() == 0){
        if (fork() == 0) { //in gson A
            pid_t tmp = getpid();
            write(fd[1], &tmp, sizeof(pid_t));
            tmp = getppid();
            write(fd[1], &tmp, sizeof(pid_t));
            close(fd[0]);
            close(fd[1]);
            return 0;
        }
        if (fork() == 0) { //in gson B
            pid_t tmp = getpid();
            read(fd[0], &tmp, sizeof(pid_t));
            fprintf(stdout, "my cousin name is %d \n", tmp);
            read(fd[0], &tmp, sizeof(pid_t));
            fprintf(stdout, "my uncle name is %d \n", tmp);
            close(fd[0]);
            close(fd[1]);
            return 0;
        }
        wait(NULL);
        wait(NULL);
        close(fd[0]);
        close(fd[1]);
        return 0;
    }
    wait(NULL);
    close(fd[0]);
    close(fd[1]);
    return 0;
}