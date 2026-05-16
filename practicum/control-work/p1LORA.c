#include<stdio.h>

int main(){
	int ai, aii;
	long long x;

	scanf("%lld", &x);
	scanf("%d", &ai);

	while (scanf("%d", &aii) != EOF){
		if ((long long)ai + aii == x){
			printf("%d %d", ai, aii);
			return 0;
		}
		ai = aii;
	}

printf ("0 0");
return 0;
}

