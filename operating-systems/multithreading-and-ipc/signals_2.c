#include <stdio.h>
#include <signal.h>
#include<unistd.h>


volatile int count = 0;

void SIGHNDLR(int s){
	signal(SIGINT, SIGHNDLR);
	count ++;
}




int main(){
	signal(SIGINT, SIGHNDLR);
	while(1){};
	return 0;

}
