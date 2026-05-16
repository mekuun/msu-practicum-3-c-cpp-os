#include<stdio.h>
#include<signal.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

int son_pid;
int fd[2];


void Sig_hndlr1(){
    signal(SIGUSR1, Sig_hndlr1);
}

void Sig_hndlr2(){
    signal(SIGUSR2, Sig_hndlr2);
    kill(son_pid, SIGKILL);
    close(fd[1]), close(fd[0]);
    wait(NULL);
    _exit(0);
}

int main(int argc, char **argv){
    signal(SIGUSR1, Sig_hndlr1);
    signal(SIGUSR2, Sig_hndlr2);

    int finp;
    finp = open(argv[1], O_RDONLY);
    lseek(finp, 0, SEEK_SET);
    int first_num, second_num;
    int sum;

    pipe(fd);

    son_pid = fork();
    if (son_pid == 0) { //we are in son
        while ((read(finp, &first_num, sizeof(int)) == sizeof(int)) && (read(finp, &second_num, sizeof(int)) == sizeof(int))) {
            write(fd[1], &first_num, sizeof(int));
            write(fd[1], &second_num, sizeof(int));
            kill(getppid(), SIGUSR1);
            pause();
            read(fd[0], &sum, sizeof(int));
            printf("son: %x\n", sum);
            fflush(stdout);
        }
        kill(getppid(), SIGUSR2);
        close(fd[1]);
        close(fd[0]);
    }
    if (son_pid != 0){
        while(1){
            pause();
            read(fd[0], &first_num, sizeof(int));
            read(fd[0], &second_num, sizeof(int));
            printf("father: %x %x\n", first_num, second_num);
            fflush(stdout);
            sum = first_num + second_num;
            fflush(stdout);
            write(fd[1], &sum, sizeof(int));
            kill(son_pid, SIGUSR1);
        }
    }
}
