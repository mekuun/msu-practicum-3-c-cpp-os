#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

char execute(char *cmd){
    switch(fork()){
        case -1: exit(1);
        case 0: execlp(cmd, cmd, NULL);
            exit(1);
    }
    int status;
    wait(&status);
    if ((WIFEXITED(status) != 0) && (WEXITSTATUS(status) == 0)) return 0;
    return 1;
}

