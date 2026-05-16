#include<stdio.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>

volatile sig_atomic_t flag = 0;


void Sig_Handler(int s){
    signal(SIGUSR1, Sig_Handler);
    flag = 1;
}


void do_work(const char * str, int * count, int N, int index, pid_t pid0, pid_t pid1, pid_t pid2, int *fd){
    int next;
    if (!flag) {
        pause();
    }
    flag = 0;

    read(fd[0], count, sizeof(int));

    (*count) ++;
    next = (index + (*count)) % 3;
    if (next == index) next = (index+2) % 3;


    if ((*count) > N)
    {
        write(fd[1], count, sizeof(int));
        write(fd[1], count, sizeof(int));

        switch (index)
        {
            case 0: kill(pid1, SIGUSR1); kill(pid2, SIGUSR1); break;

            case 1: kill(pid0, SIGUSR1); kill(pid2, SIGUSR1); break;

            case 2: kill(pid0, SIGUSR1); kill(pid1, SIGUSR1); break;
        }
        return;

    }
    printf("%s %d %d\n", str, *count, next);

    fflush(stdout);

    write(fd[1], count, sizeof(int));


    switch (next)
    {
        case 0: kill(pid0, SIGUSR1); break;

        case 1: kill(pid1, SIGUSR1); break;

        case 2: kill(pid2, SIGUSR1); break;
    }
}

int main()
{
    int n, fd[2], count = 0, index = 0;
    pid_t pid1;
    pid_t pid2;

    signal(SIGUSR1, Sig_Handler);

    scanf("%d", &n);
    pipe(fd);

    pid1 = fork();

    if (pid1 == 0)
    {
        index = 1;
        read(fd[0], &pid2, sizeof(pid2));
        while (count <= n)
            do_work("son1", &count, n, index, getppid(), getpid(), pid2, fd);
        close(fd[0]);
        close(fd[1]);
        return 0;
    }

    pid2 = fork();

    if (pid2 == 0)
    {
        index = 2;
        while (count <= n)
            do_work("son2", &count, n, index, getppid(), pid1, getpid(), fd);
        close(fd[0]);
        close(fd[1]);
        return 0;
    }

    write(fd[1], &pid2, sizeof(pid_t));
    write(fd[1], &count, sizeof(int));

    kill(pid2, SIGUSR1);
    while (count <= n)
        do_work("father", &count, n, index, getpid(), pid1, pid2, fd);

    close(fd[1]); close(fd[0]);

    wait(NULL);
    wait(NULL);
    return 0;
}