#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     2700          // iteraciones
#define N     2          // lado de la red simulada
#define D     100    		//cantidad de divisiones del diff

int main()
{
	int na,za,i;
	float  basico;
	na=N;
	za=Z;
	
	
	FILE *f;
	f = fopen("plot1a.txt", "w");
	
	for(na=N; na<256; na=na*2)
	{
		for (i=0; i<4;i++)
		{
		
			basico=volare(3,na,za);
	
			printf("N=%i Prob 1a= %f \n",na,basico);
	  	
		}
		
		fprintf(f," %i\t  %f \n",na,basico);
	}

	fclose(f);
}

