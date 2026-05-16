#include <stdlib.h>   
#include <stdio.h>
#include <string.h>

void exchange(char *str){
	char* num1 = (char*)malloc(((strlen(str) + 1) * sizeof(char)));
	int ind = 0, k = 0, n = 0, llen = 0, flen = 0, ass = 0;
	strcpy(num1, str);


	while (n < strlen(str)){
		if (str[n] == '+') k = n;
		n++;
	}

	if (k == 0) return;

	llen = strlen(str) - (k + 1);
	n = 0;
	
	while (n < strlen(str)){
		if (str[n] == '+') break;
		n++;
	}
	flen = n;
	ass = flen;

	n = strlen(str) - flen - 1;
	num1[n] = '$';
	
	while(flen >0){
		num1[strlen(str) - flen] = str[ind];
		flen --;
		ind++;
	}
	ind = 0;


	while (llen>0){
		num1[ind] = str[strlen(str) - llen];
		llen --;
		ind ++;
	}
	num1[ind] = '+';
	
	if (ind == n){
		strcpy(str, num1);
		return;
	}

	while((num1[ind] != '$')&&(num1[ind] != '\0')){
		num1[ind] = str[ass];
		ass++;
		ind++;
	}

	num1[ind] = '+';
	strcpy(str, num1);



}

int main(){
	char str[20];
	scanf("%s", str);
	exchange(str);
	printf("%s", str);

	return 0;
}
