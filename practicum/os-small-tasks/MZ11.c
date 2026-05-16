#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(){
	int N;
	scanf("%d", &N);
	int pid = getpid();


	while (N >= 0){
		N--;
        int flag = fork();
        if (flag == -1){
            perror("FORK ERROR:");
            return 1;
        }
		if (flag){
			if (pid != getpid()){
				fprintf(stdout, "%d %d \n", getpid()-getppid(), getpid() - pid);
				fflush(stdout);
				fprintf(stderr, "PID = %d PPID = %d\n", getpid(), getppid());
				fflush(stderr);
				wait(NULL);
				return 0;
			}
			wait(NULL);
			return 0;
		}
	}
return 0;
}

	

			



