#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     2700          // iteraciones
#define N     2            // lado de la red simulada


int main()
{
	
	int na,za,i,j,div ;
	float  prob,diff,*res,k,m, km,norm;
	div=1000;
	diff=1.0/div;
 	
	
	FILE *f;
	na=N;
	za=Z;
	f = fopen("plot.txt", "a");
	for (na=2; na<32;na++)
	{
		
		for	(j=0;j<4;j++)
		{
			
			res=(float *)malloc(div*sizeof(float));
			//Aca defino la parte que agarra y hace operaciones en diferenciare.
		  	norm=diferenciare(3,na,za,res,div);
			
			i=0;
			k=0;
			prob=0;
			m=0;
			while(i<div)
			{
			  prob=prob+diff;
			  
			  *(res+i)=*(res+i)/norm;
			  k=k+prob*diff*(*(res+i));
			  m=m+prob*prob*diff*(*(res+i));
			  
			  //printf("\n %f \t %f \t %f",prob,k,*(res+i));
			  i=i+1;
			}
			km=m-k*k;
			printf("\n %f \t %f",km,k);
			//printf ( "\n%.3i  \t %.4f   \n ",na, prob);
			fprintf(f,"\n %f \t %f",km,k);
			free (res);
		}
	}
	fclose(f);
	
}


