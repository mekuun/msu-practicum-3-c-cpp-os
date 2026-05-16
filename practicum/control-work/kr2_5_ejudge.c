#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include<math.h>

volatile long long num = 0;
volatile int cnt = 0;

int is_prime(long long num){
    for (long long i = 2; i < (num); ++i){
        if (num % i == 0) return 0;
    }
    return 1;
}

void SIGINT_HNDLR(){
    signal(SIGINT, SIGINT_HNDLR);
    cnt ++;
    if (cnt == 4){
        _exit(0);
    }
    printf("%lld\n", num);
    fflush(stdout);
}

void SIGTERM_HNDLR(){
    signal(SIGTERM, SIGTERM_HNDLR);

}

int main(){
    printf("%d\n", getpid()); fflush(stdout);
    long long low, high;
    if(scanf("%lld", &low) != 1 || scanf("%lld", &high) != 1) return 0;
    signal(SIGINT, SIGINT_HNDLR);
    signal(SIGTERM, SIGTERM_HNDLR);
    for (long long i = low; i < high; ++i){
        if (is_prime(i)) num = i;
    }

    printf("-1");
    return 0;
}