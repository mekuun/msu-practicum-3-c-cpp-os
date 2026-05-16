#include <stdio.h>
#include <stdlib.h>
int main(){
	unsigned long long n, S;
	scanf("%lld", &n);
	unsigned long long *x;
	x = (unsigned long long *) malloc(n * sizeof(long long));
	for (int i=0; i < n; i ++)
	{
		scanf("%llx", x+i);
	}
	scanf("%llx", &S);
	for (int i=0; i < n; i++)
	{
		for (int j=i+1; j < n; j++)
		{
			if ((S - x[i] == x[j]) && (x[i] + x[j] >= x[i]) && (x[i] + x[j] >= x[j]))
			{
				printf("%d %d\n", i, j);
				return 0;
			}
		}
	}
	printf("-1 -1\n");
	return 0;
}

	


