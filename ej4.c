#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     0.611             // p_c
#define Z     2700          // iteraciones
#define N     64          // lado de la red simulada
#define T     64          // lado de la red simulada


int main()
{
	
	int n,na,i,*red,div,z,s,l,*per,*clusters,*ns,max ;
	float  prob,prom, serie ;
	z=Z;
	na=N;
	tao=T;
	
	
	//prob=P;
	
	div=1000;
 	
	srand(time(NULL));

				      
	FILE *f;
	//aca necesito calcular el s0(o sea, el numero de clusters que hay cuando esta cerca de percolar, creo s_0=pc_L/sum(s^1-tao) (no percolantes o percolantes?)


	
	
	f = fopen("plot.txt", "w");

	for ( s=1 ; s<40 ; na++ )
	{
		prob=pcmedio(na,z,div);
		printf("prob:%f\n",prob);
		red=(int *)malloc(na*na*sizeof(int));
  		clusters=(int *)malloc(na*na*sizeof(int));
  	ns=(int *)malloc(na*na*sizeof(int));
		per=(int *)malloc(na*na*sizeof(int));
		
		prom=0;
						
			
		for(l=0;l<z;l++)
		{
		      
		      
			for (i=0;i<na*na;i++)  
				{
					*(clusters+i)=0;
					*(per+i)=0;
					*(ns+i)=0;
				}
		  llenar(red,na,prob);
		  //mostra1(red,n,n,"Matriz de partida");
		  hoshen(red,na);
		  percolacuenta(red,na,per);
		  //mostra1(red,na,na,"esta es la red");
		  //mostra1(per,na,na,"este es per");
		  contarclusters(red,clusters,na);
		  //mostra1(clusters,na,na,"Cant de nodos por cluster");
		  prob=pcmedio(na,z,div);
		  
		  max=0;
		  serie=0;
		  for (i=0;i<na*na;i++)
		  {
				if (*(clusters+i)) *(ns+*(clusters+i)-1)+=1;
				serie+=*(cluster+i)**(1-tao)
		  }   
			//mostra1(ns,na,na,"este es ns");
		prom+=(float)ns/z;
			  
		    
		}
		
		

		printf("Lado = %i M=%f\n",na,prom/(na*na));
		fprintf(f,"\n %f \t %f",log(na),log(prom/(na*na)));
		 
	
		
		
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
