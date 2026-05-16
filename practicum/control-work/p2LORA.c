#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_pairs(char* str){
	char* ptr = ((char*)malloc((strlen(str) + 1)* sizeof(char)));
	int i = 0,j = 0,p = 0, k = 0;

	while (p < strlen(str)){
		i = 0;
	       	j = 1;

		while (str[i + p] != ',') (i++);
		while (str[i + j + p] != ','){
			ptr[j - 1 + p] = str[i + j + p];
			j++;
			}

		ptr[j - 1 + p] = ',';
		j++;

		for (int k = 0; k <= i; k ++){
			ptr[j + k - 1 + p] = str[k + p];
		}
		
		p += i + j;



	}
	strcpy(str, ptr);
	free(ptr);    
}






int main(){
	char str[] = "govno,zalupa,penis,her,davalka,hui,blyadina,!!,";
	swap_pairs(str);
	printf("%s", str);

	return 0;
}
