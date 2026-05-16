#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(){
	char number;
	long long buf = 0;
	while (scanf("%c", &number) != EOF){
		if ((number >= '0') && (number <= '9')) buf += (number - '0');
		if ((number >= 'a') && (number <= 'f')) buf += (number - 'a' + 10);
		if ((number >= 'A') && (number <= 'F')) buf += (number - 'A' + 10);
	
	}
printf("%lld\n",buf);
		
return 0;


}

