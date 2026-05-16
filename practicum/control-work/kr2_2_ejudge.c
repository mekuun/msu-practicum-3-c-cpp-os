#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
    int N;
    scanf("%d", &N);
    int i = 1;
    if (N == 0){
        return 1;
    }
    if (N == 1) {
        printf("%d\n", i); fflush(stdout);
    }
    if (N != 1) {
        printf("%d ", i); fflush(stdout);
    }
    for (i = 1; i <= N; i ++){
        if (fork()) {wait(NULL); return 0;}
        else if (i != N){
            if (i != 1) {
                printf("%d ", i); fflush(stdout);
            }
        }
        else {
            if (i != 1) {
                printf("%d\n", i); fflush(stdout);
            }
        }

    }
    return 0;
}