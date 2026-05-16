#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int execute(char *popa){
    switch (fork()){
        case -1: return 1;
        case 0: execl(popa, popa, NULL); return 1;
    }
    int status;
    wait(&status);
    if ((WIFEXITED(status) != 0) && (WEXITSTATUS(status) == 0)) return 0;
    return 1;
}