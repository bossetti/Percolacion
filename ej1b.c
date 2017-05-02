#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     2700          // iteraciones
#define N     2           // lado de la red simulada
#define D     1000  

int main()
{
	
	int na,za,i, div;
	float  dif;

	srand(time(NULL));
	FILE *f;
	na=N;
	za=Z;
	div=D;	
	f = fopen("plot1b.txt", "w");
	for(na=N; na<256; na=na*2)
	{
		for (i=0; i<4;i++)
		{
		  	dif=pcmedio(na,za,div);
			
			printf ( "\n%.3i  \t %.3f   \n ",na, dif);
			fprintf(f, "\n%.3i  \t %.3f   \n",na, dif);
			
		}
	}
	fclose(f);
}
