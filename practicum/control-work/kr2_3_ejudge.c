#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int execute(char *cmd){
    switch (fork()) {
        case -1: exit(1);
        case 0: execlp(cmd, cmd, NULL); exit(1);
    }
    int status;
    wait(&status);
    if (WIFEXITED(status) && (WEXITSTATUS(status) == 0)) return 0;
    return 1;
}

int main(int argc, char **argv){
    if (!execute(argv[1])) return execute(argv[3]);
    else if (!execute(argv[2])) return execute(argv[3]);
    else return 1;
}