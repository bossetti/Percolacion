#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     2700          // iteraciones
#define N     128           // lado de la red simulada


int main()
{
	
	int n,na,i,j,div,*red,z,l,*per,*clusters,max,c ;
	float  prob,prom,diff;
	z=Z;
	n=N;

	div=1000;
	diff=1.0/div;
 	
	srand(time(NULL));

				      
	FILE *f;
	
	
	f = fopen("plot2.txt", "w");
	//for ( na=2 ; na<n+1 ; na=na*2 )
	//{
	na=n;
		red=(int *)malloc(na*na*sizeof(int));
  		clusters=(int *)malloc(na*na*sizeof(int));
		per=(int *)malloc(na*na*sizeof(int));
		
		prob=0;
		
		for	(j=0;j<div;j++)
		{
			prob=prob+diff;
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
					if ((*(clusters+i) && *(per+i)) && *(clusters+i)>max) max=*(clusters+i);
			  }   
				
				prom+=(float)max;
				  
			    
			}
			printf("Prob = %f Max=%f Maxbestia=%f\n",prob,prom/(c*na*na),prom/(z*na*na));
			fprintf(f,"\n %f \t %f\t %f",prob,prom/(c*na*na),prom/(z*na*na));
			 
		}
			
			
			//printf("\n %f \t %f",km,k);
			//printf ( "\n%.3i  \t %.4f   \n ",na, prob);
			//fprintf(f,"\n %f \t %f",km,k);
			
		
		free(red);
		free(clusters);
		free(per);
	//}
	fclose(f);
	return 0;
}




  
  

 

