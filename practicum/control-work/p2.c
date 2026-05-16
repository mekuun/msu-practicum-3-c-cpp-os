#include <stdio.h>
int main()
{
    int a, b, n;
    char hate = ' ';
    if (scanf("%d %d %d", &a, &b, &n) != 3) return 1;
    if (n <= 0) return 1;
    printf("%*c ", n, hate);
    for (int i = a; i < b; i++){
	    if (i == b - 1) printf ("%*d\n",n, i);
	    else printf ("%*d ", n, i);
	}


    for (int j = a; j < b; j++){
	    printf("%*d ", n, j);
	    for(int k = a; k < b; k ++){
		    if (k == b - 1) printf ("%*lld\n",n, (long long)k * j);
		    else printf ("%*lld ", n, (long long)k * j);
	}
    }


return 0;

}
