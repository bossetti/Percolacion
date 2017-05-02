#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     0.611             // p_c
#define Z     2700          // iteraciones
#define N     30         // lado de la red simulada


int main()
{
	
	int n,na,i,*red,div,z,l,*per,*clusters,max,c,prom ;
	float  prob;
	z=Z;
	n=N;
	
	
	
	//prob=P;
	
	div=1000;
 	
	srand(time(NULL));

				      
	FILE *f;
	
	
	f = fopen("plot.txt", "w");
	for ( na=2 ; na<n ; na++ )
	{
		prob=pcmedio(na,z,div);
		printf("\nprob:%f\n",prob);
		red=(int *)malloc(na*na*sizeof(int));
  		clusters=(int *)malloc(na*na*sizeof(int));
		per=(int *)malloc(na*na*sizeof(int));
		
		prom=0;						
		c=0;
		for(l=0;l<z;l++)
		{
		     
		      
	 	  for (i=0;i<na*na;i++)  
			{
				*(clusters+i)=0;
				*(per+i)=0;
			}
		  llenar(red,na,prob);
		  //mostra1(red,n,n,"Matriz de partida");
		  hoshen(red,na);
		  c+=percolacuenta(red,na,per);
		  
		  //mostra1(red,na,na,"esta es la red");
		  //mostra1(per,na,na,"este es per");
		  contarclusters(red,clusters,na);
		  //mostra1(clusters,na,na,"Cant de nodos por cluster");
		  max=0;
		  for (i=0;i<na*na;i++)
		  {
			if ((*(clusters+i) && *(per+i)) && *(clusters+i)>max) 
			{
			max=*(clusters+i);
			//printf("max %i\n",max);
			}
		  }   
			
			prom+=max;
			//printf("Este es paso %i con promedio %i\n",l,max);	  
		    
		}
		//printf("Lado = %i M=%f\n",na,prom/(na*na));
		//fprintf(f,"\n %f \t %f",log(na),log(prom/(na*na)));
		printf("\nEste es prom: %f\n",(float)max/(c*na*na));
		//printf("\nEste es c: %i\n",c);
		printf("Lado = %i M=%f Mbestia=%f",na,log((float)prom/(c*na*na)),log((float)prom/(z*na*na)));
		fprintf(f,"\n %f \t %f\t %f",log(na),log((float)prom/(z*na*na)),log((float)prom/(z*na*na))); 
	
		
		
		//printf("\n %f \t %f",km,k);
		//printf ( "\n%.3i  \t %.4f   \n ",na, prob);
		//fprintf(f,"\n %f \t %f",km,k);
		
		
		free(red);
		free(clusters);
		free(per);
	}
	fclose(f);
	return 0;
}
