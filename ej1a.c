#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     2700          // iteraciones
#define N     15           // lado de la red simulada
#define D     100    		//cantidad de divisiones del diff

int main()
{
	int na,za,div,i;
	float *res, prob,diff,basico;
	na=N;
	za=Z;
	div=D;
	diff=1.0/div;
	
	FILE *f;
	f = fopen("plot1a.txt", "w");

	basico=volare(3,na,za);
	res=(float *)malloc(na*na*sizeof(float));//grafico de diferenciare
	printf("La probabilidad del 1a es: %f \n",basico);
  	
	
		
	fprintf(f," %i\t  %f \n",na,basico,*(res+i));
	i+=1;

	fclose(f);
}

