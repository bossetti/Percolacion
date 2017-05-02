#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     270         // iteraciones
#define N     32          // lado de la red simulada
#define R     1000           // lado de la red simulada

int main()
{
	
	int n,na,i,r,div,*red,z,l,*per,*clusters,*ns ;
	float  prob;
	z=Z;
	n=N;
	r=R;
	

	div=100;
	
 	
	srand(time(NULL));

				      
	FILE *f;
	
	
	f = fopen("plot1dalt.txt", "w");
	//for ( na=n ; na<n+1 ; na++ )
	//{
	na=n;
		red=(int *)malloc(na*na*sizeof(int));
		per=(int *)malloc(na*na*sizeof(int));
  		clusters=(int *)malloc(na*na*sizeof(int));
		ns=(int *)malloc(na*na*sizeof(int));
		
		prob=pcmedio(z,na,div);
		
		
		for (i=0;i<na*na;i++)  
			{
							
				*(ns+i)=0;
			}	
							
				
		for(l=0;l<r;l++)
		{
		      
		 printf("Paso: %i\n",l);     
	 	  for (i=0;i<na*na;i++)  
			{
				*(clusters+i)=0;
				*(per+i)=0;
			
			}
		
		  llenar(red,na,prob);
		  //mostra1(red,na,na,"Matriz de partida");
		  hoshen(red,na);
		  percolacuenta(red,na,per);
		  //mostra1(red,na,na,"esta es la red");
		  //mostra1(per,1,na,"este es per");
		  contarclusters(red,clusters,na);
		  //mostra1(clusters,1,na,"Cant de nodos por etiqueta de cluster");
		  contarclusters(clusters,ns,na);
		  //mostra1(ns,na,na,"Cant de clusters de tamaño s");
		  			
			  
		    
		}
		
		for (i=0;i<na*na;i++)
		{
			//printf("Prob = %i Max=%f\n",i,prom/(na*na));
			if (*(ns+i))  
			{
			printf("\n %f \t %f\n",log(i+1),log((float)*(ns+i)/z));
			fprintf(f,"\n %f \t %f\n",log(i+1),log((float)*(ns+i)/z));
			}
		}    
	
		
		
		//printf("\n %f \t %f",km,k);
		//printf ( "\n%.3i  \t %.4f   \n ",na, prob);
		//fprintf(f,"\n %f \t %f",km,k);
		
	free(ns);
	free(red);
	free(clusters);
	free(per);
	
	//}
	fclose(f);
	return 0;
}




