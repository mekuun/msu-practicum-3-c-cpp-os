#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile int cnt = 0;


void Sig_Handler(int s){
    signal(SIGUSR1, Sig_Handler);
    signal(SIGUSR2, Sig_Handler);
    if (s == SIGUSR1) {
        cnt +=5;
        fprintf(stdout, "%d %d \n", SIGUSR1, cnt);
        fflush(stdout);
    }
    if (s == SIGUSR2){
        cnt -= 4;
        fprintf(stdout, "%d %d \n", SIGUSR2, cnt);
        fflush(stdout);
        if (cnt < 0) {
            _exit(0);
        }

    }
}


int main(){
    fprintf(stdout, "%d", getpid());
    signal(SIGUSR1, Sig_Handler);
    signal(SIGUSR2, Sig_Handler);
    while(1) {pause();}
}