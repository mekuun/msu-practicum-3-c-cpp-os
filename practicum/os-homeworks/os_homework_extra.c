#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int main(){
    int a = 5, x, k[5], y;
    scanf("%d %d", &x, &y);
    a /= x;
    if (x == 0){
        printf("suka");
    }
    k[y] = 0;
    if (y >= 5){
        printf("blet");
    }
    exit(0);
}
