#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     0.611             // p_c
#define Z     2700          // iteraciones
#define N     10         // lado de la red simulada
#define T     64          // lado de la red simulada


int main()
{
	
	int na,i,*red,div,z,l,*per,*nsc,*ns,*clusters,r ;
	float  prob, max,maxc,diff;
	z=Z;
	na=N;
	
	
	
	//prob=P;
	
	div=1000;
 	diff=1.0/1000;
	srand(time(NULL));
	
	prob=0;			      
	FILE *f;
	//aca necesito 


	
	
	f = fopen("plot4.txt", "w");
	
	for ( r=0 ; r<div ; r++ )
	{
		
		
		red=(int *)malloc(na*na*sizeof(int));
  		clusters=(int *)malloc(na*na*sizeof(int));
		ns=(int *)malloc(na*na*sizeof(int));
  		nsc=(int *)malloc(na*na*sizeof(i));
		per=(int *)malloc(na*na*sizeof(int));
			

		prob=prob+diff;
		printf("prob:%f\n",prob);				
		
		
		for (i=0;i<na*na;i++)  
		{
			*(nsc+i)=0;
			*(ns+i)=0;
		}
		for(l=0;l<z;l++)
		{
		      
		        
			for (i=0;i<na*na;i++)  
				{
					*(clusters+i)=0;
					*(per+i)=0;
					
				}
			  llenar(red,na,prob);
			  //mostra1(red,na,na,"Matriz de partida");
			  hoshen(red,na);
			  percola(red,na);
			  //mostra1(red,na,na,"esta es la red");
			  //mostra1(per,1,na,"este es per");
			  contarclusters(red,clusters,na);
			  //mostra1(clusters,1,na,"Cant de nodos por etiqueta de cluster");
			  contarclusters(clusters,ns,na);
			  //mostra1(ns,na,na,"Cant de clusters de tamaño s");
		  	
			  
			  
			  
			  
		  
		  
		//mostra1(ns,na,na,"este es ns");
		
			  
		    
		}
		
		for(l=0;l<z;l++)
		{
		    prob=pcmedio(na,z,div);  
		        
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
			  contarclusters(clusters,nsc,na);
			  //mostra1(ns,na,na,"Cant de clusters de tamaño s");
		  	
			  
			  
		  
		
		
			  
		    
		}

		max=promedioi(ns,na*na,1,3,20);
		
		maxc=promedioi(nsc,na*na,1,3,20);
		printf("Lado = %i <ns>=%f<nsc>=%f\n",na,max,maxc); 
		//mostra1(ns,na,na,"este es ns");

		
		
		printf("\n %f \t %f\n",prob,(float)max/maxc);
		fprintf(f,"\n %f \t %f\n",prob,(float)max/maxc);
		
		
		//printf("\n %f \t %f",km,k);
		//printf ( "\n%.3i  \t %.4f   \n ",na, prob);
		//fprintf(f,"\n %f \t %f",km,k);
		
		
		free(red);
		free(clusters);
		free(per);
		free(ns);
		free(nsc);
	}
	fclose(f);
	return 0;
}


