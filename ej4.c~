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
	
	int na,i,*red,div,z,l,*per,*nsc,*ns,*clusters,r ;
	float  prob,probc, max,maxc,diff,*permnsc,*permns ;
	z=Z;
	na=N;
	
	
	
	//prob=P;
	
	div=1000;
 	diff=1.0/1000;
	srand(time(NULL));
	probc=0;
	prob=0;			      
	FILE *f;
	//aca necesito 


	
	
	f = fopen("plot.txt", "w");
	
	for ( r=0 ; r<div ; r++ )
	{
		
		
		red=(int *)malloc(na*na*sizeof(int));
  		clusters=(int *)malloc(na*na*sizeof(int));
		ns=(int *)malloc(na*na*sizeof(int));
  		nsc=(int *)malloc(na*na*sizeof(int));
		per=(int *)malloc(na*na*sizeof(int));
		permnsc=(float *)malloc(na*na*sizeof(float));
		permns=(float *)malloc(na*na*sizeof(float));	

		prob=prob+diff;
		printf("prob:%f\n",prob);				
			
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
			  
			  
			  max=0;
			  
		  for (i=0;i<na*na;i++)
		  {
				if (*(clusters+i)) *(ns+*(clusters+i)-1)+=1;
				*(permns+i)+=(float)*(ns+i)/z;
				
		  }   
		  
		//mostra1(ns,na,na,"este es ns");
		
			  
		    
		}
		
		for(l=0;l<z;l++)
		{
		      
		        
			for (i=0;i<na*na;i++)  
				{
					*(clusters+i)=0;
					*(per+i)=0;
					*(nsc+i)=0;
				}
			  probc=pcmedio(na,z,div);
			  llenar(red,na,probc);
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
				if (*(clusters+i)) *(nsc+*(clusters+i)-1)+=1;
				*(permns+i)+=(float)*(ns+i)/z;
				
		  }  
		  max=promedio(permns, na,1,30,40);
		  maxc=promedio(permnsc, na,1,30,40);
		printf("Lado = %i <ns>=%f<ns>=%f\n",na,max,maxc); 
		//mostra1(ns,na,na,"este es ns");
		
			  
		    
		}

		

		printf("Lado = %f <ns>=%f<ns>=%f\n",prob,max,maxc);
		fprintf(f,"\n %f \t %f<ns>=%f\n",prob,max,maxc);
		 
	
		
		
		//printf("\n %f \t %f",km,k);
		//printf ( "\n%.3i  \t %.4f   \n ",na, prob);
		//fprintf(f,"\n %f \t %f",km,k);
		
		
		free(red);
		free(clusters);
		free(per);
		free(permns);
		free(permnsc);
	}
	fclose(f);
	return 0;
}
