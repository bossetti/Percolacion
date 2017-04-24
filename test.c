#include <stdio.h>

int main()
{
	
	int k, l,n;
	n=5;
	for(k=0;k<n+1;k=k+n-1)
		{
			for(l=0;l<n*n;l=l+n)
			{	
				printf("%i\n",k+l);
			}
		}
}
