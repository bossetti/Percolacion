#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     2700          // iteraciones
#define N     32           // lado de la red simulada


int main()
{
	
	int n,na,i,j,div,*red,z,r,l,*per,*clusters,max ;
	float  prob,prom,diff;
	z=N;
	n=N;
	
	
	
	

	div=100;
	diff=1.0/div;
 	
	srand(time(NULL));

				      
	FILE *f;
	
	
	f = fopen("plot.txt", "w");
	for ( na=n ; na<33 ; na++ )
	{
		red=(int *)malloc(na*na*sizeof(int));
  	clusters=(int *)malloc(na*na*sizeof(int));
		per=(int *)malloc(na*na*sizeof(int));
		
		prob=0;
		for	(j=0;j<div;j++)
		{
			prob=prob+diff;
			for(r=0;r<div;r++)
			{
							
				
				for(l=0;l<z;l++)
				{
				      
				    prom=0;  
				 	  for (i=0;i<na*na;i++)  
						{
							*(clusters+i)=0;
							*(per+i)=0;
						}
					  llenar(red,na,prob);
					  //mostra1(red,n,n,"Matriz de partida");
					  hoshen(red,na);
					  percolacuenta(red,na,per);
					  //mostra1(red,na,na,"esta es la red");
					  //mostra1(per,na,na,"este es per");
					  contarclusters(red,clusters,na);
					  //mostra1(clusters,na,na,"Cant de nodos por cluster");
					  max=0;
					  for (i=0;i<na*na;i++)
					  {
							if ((*(clusters+i) && *(per+i)) && *(clusters+i)>max) max=*(clusters+i);
					  }   
						
						prom+=(float)max/(na*na);
					  
				    
				  }
				  printf("Prob = %f Max=%f\n",prob,prom);
					fprintf(f,"\n %f \t %f",prob,prom);
				 
			}
			
			
			//printf("\n %f \t %f",km,k);
			//printf ( "\n%.3i  \t %.4f   \n ",na, prob);
			//fprintf(f,"\n %f \t %f",km,k);
			
		}
		free(red);
		free(clusters);
		free(per);
	}
	fclose(f);
	return 0;
}




  
  

 

