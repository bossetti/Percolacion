#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     2700	         // iteraciones dentro de las funciones
#define N     2            // lado de la red simulada
#define R     2700           // numero de iteraciones para la dispersion

int main()
{
	
	int n,na,div,z,l,r ;
	float  prom,*var, vavar, temp;
	z=Z;
	n=N;
	r=R;
	
	var=(float *)malloc(z*sizeof(float));	
	//prob=P;
	
	div=100;
 	
	srand(time(NULL));

			      
	FILE *f;
	
	
	f = fopen("plot1d.txt", "w");
	for ( na=n ; na<65 ; na++ )
	{
		
		
		
		prom=0;
						
			
		for(l=0;l<r;l++)
		{
		  *(var+l)=pcmedio(na,1,div);    
		  	 	  		    
		}
		prom=promedio(var,z,0,0,0);
		temp=0;
		for(l=0;l<r;l++)
		{
			temp+=powf((prom-*(var+l)), 2);
			
		}
		vavar=sqrtf((temp)/na);
		printf("Pc(L) = %f sigma=%f\n",prom,vavar);
		fprintf(f,"\n %f \t %f",prom,vavar);
		 
	
		
		
		//printf("\n %f \t %f",km,k);
		//printf ( "\n%.3i  \t %.4f   \n ",na, prob);
		//fprintf(f,"\n %f \t %f",km,k);
		
		
		
	}
	
	free(var);
	fclose(f);
	return 0;
}
