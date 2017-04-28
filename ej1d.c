#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     2700	         // iteraciones
#define N     2            // lado de la red simulada
#define R     10            // lado de la red simulada

int main()
{
	
	int n,na,div,z,l,r ;
	float  prob,prom,*var, vavar, temp;
	z=Z;
	n=N;
	r=R;
	
	var=(float *)malloc(z*sizeof(float));	
	//prob=P;
	
	div=1000;
 	
	srand(time(NULL));

			      
	FILE *f;
	
	
	f = fopen("plot.txt", "w");
	for ( na=n ; na<65 ; na++ )
	{
		
		
		
		prom=0;
						
			
		for(l=0;l<r;l++)
		{
		  prob=pcmedio(na,z,div);    
		      
	 	  printf("prob:%f\n",prob);
		  
		  *(var+l)=prob;
			
			prom+=(float)prom/z;
			  
		    
		}
		for(l=0;l<r;l++)
		{
			temp=powf((prom-*(var+l)), 2);
			vavar=sqrtf((temp)/n);
		}
		printf("Lado = %i M=%f\n",na,vavar);
		fprintf(f,"\n %i \t %f",na,vavar);
		 
	
		
		
		//printf("\n %f \t %f",km,k);
		//printf ( "\n%.3i  \t %.4f   \n ",na, prob);
		//fprintf(f,"\n %f \t %f",km,k);
		
		
		
	}
	
	free(var);
	fclose(f);
	return 0;
}
