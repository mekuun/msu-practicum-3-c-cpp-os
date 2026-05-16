#include <stdio.h>
#include <limits.h>

int main(){
	
	int A,B,C,D;

	scanf("%d %d %d %d", &A, &B, &C, &D);
	if ((long long) B == (long long) A * C) printf("%d %d", A, C);
	else if ((long long) B == (long long) A * D) printf("%d %d", A, D);
	else if ((long long) B == (long long) C * D) printf("%d %d", C, D);


	return 0;
}

