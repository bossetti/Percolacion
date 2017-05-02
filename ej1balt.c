#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     2700          // iteraciones
#define N     2           // lado de la red simulada


int main()
{
	
	int na,za,i,j, div;
	float  dif;

	srand(time(NULL));
	FILE *f;
	na=N;
	za=Z;
	div=1000;	
	f = fopen("plot.txt", "a");
	for (i=0; i<7;i++)
	{
		na=na*2;
		for	(j=0;j<3;j++)
		{
			
			
		  	dif=pcmedio(na,za,div);
			
			printf ( "\n%.3i  \t %.3f   \n ",na, dif);
			fprintf(f, "\n%.3i  \t %.3f   \n",na, dif);
			
		}
	}
	fclose(f);
}


