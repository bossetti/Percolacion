#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "progfinal.h"

#define P     16             // 1/2^P, P=16
#define Z     2700          // iteraciones
#define N     5            // lado de la red simulada

int chequeorapido(int *red,int n)
{
	int i, j,k,ar,ab,iz,de,a;
	a=0;
	for (i=0;i<n*n;i=i+n)
	{
		for (j=0;j<n;j++)
		{
			k=*(red+i+j);
			if ((i-n)>=0) ar=*(red+i+j-n);
			else ar=0;
			if ((i+n)<n*n) ab=*(red+i+j+n);
			else ab=0;
			if ((j-1)>=0) iz=*(red+i+j-1);
			else iz=0;
			if ((j+1)<n) de=*(red+i+j+1);
			else de=0;
			//mostra1(red,n,n,"\nmatriz");
			//printf("\nPosicion %i \t %i",i/n +1,j+1);
			//printf( "\nArriba =%i Izq= %i Abajo=%i Der=%i",ar,iz,ab,de); 
			if (k && de && k!=de) a=1;
			if (k && iz && k!=iz) a=1;
			if (k && ar && k!=ar) a=1;
			if (k && ab && k!=ab) a=1;
			
		}
	}
	
	return a;
}



float promedio(float *pointe,int  na,int opcion,int inicio,int final)

{
	int i,temp,ini, fin;
	ini=0;
	fin=0;
	if (opcion) 
	{
		ini=final;
		fin=final;
	}
	temp=0;
	for(i=ini;i<fin;i++)
	{
		temp+=*(pointe+i)/na;

	}
	return temp;
}

float pcmedio( int na, int za,int div)


{

  int    j,*red,n,z,cantperc;
  float  prob,diff,k;
//div es cantidad de pedazos que quiero partirlo
//diff es el paso diferencial para cada grupo de probabilidades
  n=na;
  z=za;
  
  diff=1.0/div;
  //printf("\ndiff=%f\n",diff);
  
  red=(int *)malloc(n*n*sizeof(int));
 
	//esta es la probabilidad(empiezo alto porque quiero apurar el calculo)
  prob=0.45;
  //esta es la probabilidad donde para
  k=0;
  while(k<0.5)
  {
		//inicio el loop donde voy recorriendo con pasos diff de 0 a 1
		cantperc=0; //este es el contador de percolantes promediados en este diferencial
    //printf("\nEsta es la iteracion :%i",i);
    prob+=diff;
    //printf("%f\n",prob);

	      for(j=0;j<z;j++)
				{
							
					llenar(red,n,prob);
					  	  //mostra1(red,n,n,"Matriz de partida");
					hoshen(red,n);
					//mostra1(red,n,n,"Matriz final");
					cantperc+=percolaofi(red,n);
								//printf("¿percola?=%i\n",percola(red,n));
					//printf("cantperc:%i\n",cantperc);
				
				 
				}
	      //printf("cantper:%i\n",cantperc);
		k=(float)cantperc/z;
		//printf("k=%f\n",k);
		//tal=(float)cantperc/z;
		//if ((cantperc/z)>0.5) break;
		//printf("\n %i",cantperc);
		//printf("\n %f \t %f",prob,tal);
		//printf("\n %f \t %f",prob,*(res+i));
	}
	
    
  //prom=(float)cantperc/(float)z;
 
  
  
  //printf("\n %f",out);
        
  free(red);
 
  
  return prob;
}

void contarclusters(int *red, int *clusters, int n)


{
	int k,l;
	
	//mostramostro(red,clase, n,n,"Estoy corrigiendo");
	for(k=0;k<n*n;k=k+n)
	{
		for(l=0;l<n;l++)
		{	
			if (*(red+k+l)!=0)
			{
				*(clusters+*(red+k+l)-1)+=1;
				
					
				
			}
		}
	}
							
	//mostra1(red,n,n,"Esta es la matriz final");
}


float diferenciare(int arc, int na, int za,float *res, int div)
{
//ESTA FUNCION TIENE UN ERROR, CORREGIR SI VA A SER UTILIZADA
  int    i,j,*red,n,z,cantperc;
  float  prob,diff,k;
//div es cantidad de pedazos que quiero partirlo
//diff es el paso diferencial para cada grupo de probabilidades
  n=N;
  z=Z;
  
  diff=1.0/div;
  //printf("\ndiff=%f\n",diff);
  if (arc==3) 
     {
       
  	n=na;
  	z=za;

     }
  red=(int *)malloc(n*n*sizeof(int));
 

  prob=0;
  *res=0;
  k=0;
  for(i=0;i<div;i++)
    {
	//inicio el loop donde voy recorriendo con pasos diff de 0 a 1
	cantperc=0; //este es el contador de percolantes promediados en este diferencial
      //printf("\nEsta es la iteracion :%i",i);
      prob=prob+diff;
      
 
      srand(time(NULL));

      for(j=0;j<z;j++)
        {
	  
          llenar(red,n,prob);
      	  //mostra1(red,n,n,"Matriz de partida");
          hoshen(red,n);
          //mostra1(red,n,n,"Matriz final");
          cantperc+=percola(red,n);
	  //printf("¿percola?=%i\n",percola(red,n));
          
          
	 
        }
	*(res+i)=(float)cantperc/z;
	k=k+(*(res+i))*diff;
	//tal=(float)cantperc/z;
	//if ((cantperc/z)>0.5) break;
	//printf("\n %i",cantperc);
	//printf("\n %f \t %f",prob,tal);
	//printf("\n %f \t %f",prob,*(res+i));
	
	
    }
  //prom=(float)cantperc/(float)z;
 
  
  
  //printf("\n %f",out);
        
  free(red);
 
  
  return k;
}





float volare(int arc,int na,int za)
{
  int    i,j,*red,n,z;
  float  prob,denominador,prom;

  n=N;
  z=Z;

  if (arc==3) 
     {
       
  	n=na;
  	z=za;
     }
    
  red=(int *)malloc(n*n*sizeof(int));
  
  prom=0;//defino un promedio que voy a usar

  for(i=0;i<z;i++)
    {
      //printf("\nEsta es la iteracion :%i",i);
      prob=0.5;
      denominador=2.0;
 
      srand(time(NULL));
	

      for(j=0;j<P;j++)
        {
          llenar(red,n,prob);
      	  //mostra1(red,n,n,"Matriz de partida");
          hoshen(red,n);
          
          denominador=2.0*denominador;

          if (percola(red,n)) 
	  {
             prob+=(-1.0/denominador); 
	     //printf("Percola, Obviously");
	  }
          else prob+=(1.0/denominador);
	  //mostra1(red,n,n,"Matriz final");
	 
        }
	prom=prom+prob;
    }
  
  
	
  //printf ( "%.3i \t %.3f ",n, prom/z );
  free(red);
 
  return prom/z;
}




int hoshen(int *red,int n)
{
  /*
    Esta funcion implementa en algoritmo de Hoshen-Kopelman.
    Recibe el puntero que apunta a la red y asigna etiquetas 
    a cada fragmento de red. 
  */

  int i,j,k,s1,s2,frag; //inicializa todo
  int *clase;		//empieza una etiqueta clase que guarda las etiquetas que va usando para el cluster que está distinguiendo

  frag=0;	//inicializa la clase temp en 0, esta es la izq del primer elemento
  
  
  clase=(int *)malloc(n*n*sizeof(int));	//reserva el espacio para clase

  for(k=0;k<n*n;k++) *(clase+k)=frag;	//inicializa clase en todos ceros
  
  // primer elemento de la red

  s1=0;	//definimos que el valor a izq de la posicion va a ser cero (no existe, no hay periodicidad)
  frag=2;//primera etiqueta de la clase
if (*red) 
{
	*red=frag;
	*(clase+frag)=frag;
}
	 // Si el primer valor de red esta ocupado, entonces asigno la clase automaticamente
//mostra1(red, n,n, "Punto de partida");  
  // primera fila de la red

  for(i=1;i<n;i++) 
    {
      if (*(red+i)) 
         {
           s1=*(red+i-1);  //etiqueta que vamos a poner despues a este cluster
           frag=actualizar(red+i,clase,s1,frag);//ponerle el numero de frag(o del que tiene atras) y asignarle esa etiqueta a la posicion de red, SI el anterior es 0 subir la clase usada, es decir subir el return frag en 1 y ponerle esa clase nueva a la posicion de clase

		//mostra1(red, n,n, "Primera fila"); 
         }
    }


  // el resto de las filas 

  for(i=n;i<n*n;i=i+n)
    {

      // primer elemento de cada fila

      if (*(red+i)) 
         {
           s1=*(red+i-n); 
           frag=actualizar(red+i,clase,s1,frag);
	
		//mostra1(red,n,n, "Cuerpo ppal");
         }
	//aca comienza con el codigo en todas las filas

      for(j=1;j<n;j++)
	if (*(red+i+j))
	  {
	    s1=*(red+i+j-1); 
            s2=*(red+i+j-n);

	    if (s1*s2>0)
	      {
		//mostramostro(red, clase, n,n,"Estoy a punto de resolver colision");
		etiqueta_falsa(red+i+j,clase,s1,s2);
		
		//mostramostro(red, clase, n,n,"Aca hubo colision de clusters");
              }
	    else 
	      { if (s1!=0) frag=actualizar(red+i+j,clase,s1,frag);
	        else       frag=actualizar(red+i+j,clase,s2,frag);
		
		//mostra1(red, n,n, "Cuerpo ppal");
	      }
	  }
    }


  corregir_etiqueta(red,clase,n);
  if (chequeorapido(red,n))
  {
		
		printf("ERRORERRORERRORERRORERRORERRORERROR") ;
		mostramostro(red,clase, n,n,"aca esta la matriz");
	
  }
  free(clase);

  return frag;
}




int actualizar(int *red,int *clase,int s, int frag)
{
	//Esta funcion va a tomar el valor que aparece en s como el valor izquierdo o superior, y si es distinto de cero va a actualizar el valor de la red a la etiqueta usada frag, subiendo el valor de frag en una unidad
	//No toma siempre una etiqueta nueva, si puede, hereda la etiqueta mas cercana.
	if (s!=0)
	{
		*red=s;
		if (*(clase+frag)==0) *(clase+frag)=frag;
	}  
	else
	{
		frag++;	
		if (*(clase+frag)==0) *(clase+frag)=frag;
		*red=frag;
	}
	return frag;
}




void  llenar(int *red,int n,float prob)//toma la red que le ponen, el lado y la probabilidad que va a usar en las posiciones.
{
	float r;
	int  i,j;
	
	for (i=0;i<n;i++){
		for(j=0; j<n; j++){
					
			r=(float)rand()/(float)RAND_MAX;
			//printf("%f\n", r);
			if (r<prob){			
				*(red+i*n+j)=1;
			}
			else{
				*(red+i*n+j)=0;
			}
		}
	}
}

void mostrar(int *print, int n1, int n2)
{
	//basicamente recorre la variable print para imprimirla en forma de matriz
	int  i,j;
	
	for (i=0;i<n1;i++){
		printf("\n");
		for (j=0;j<n2;j++){
			printf("%3i",*(print+i*n1+j));
	
		}
	}
}


void mostra1(int *red, int n1, int n2, char *k)
{
	//imprime de la forma que yo quiera los resultados
	printf("%s\n", k); 
	mostrar(red,n1, n2);
	printf("\n");
	
	
	 
	getchar();  
}

void mostramostro(int *red, int *clase, int n1, int n2, char *k)
{
	//imprime de la forma que yo quiera los resultados
	printf("%s\n", k); 
	mostrar(red,n1, n2);
	printf("\n");
	mostrar(clase,n1, n2);
	printf("\n");
	
	 
	getchar();  
}

void meterneg(int *clase, int pos, int start)

{
	//aca quiero reordenar el vector clase cuando meto los dos negativos ma y mi. Tiene que ser negativo *(clase + pos) 
	//Tiene que cumplirse que el start este a la derecha
	int r,rtemp, ma, mi;
	
		ma=start;
		mi=pos;
	//printf("maximo: %i , minimo :%i\n",ma, mi);
	//printf("ESTAUSANDOLO\n");
	
	r=ma;
	rtemp=0;
	
	while (r<=pos && r<0)
	{
		//printf("Antes este es rtemp :%i y r:%i\n",rtemp,r);
		rtemp=r;
		r=*(clase+abs(r));
		//printf("Este es rtemp :%i y r:%i\n",rtemp,r);
		  
	}	
	if (abs(rtemp)!=abs(mi)) *(clase+abs(rtemp))=mi;
	if (r<0) *(clase+abs(mi))=r;
	
}




void etiqueta_falsa(int *red,int *clase,int s1,int s2)
{	
	//en el caso donde hay un vertice donde se encuentran dos clusters, recorre aburridamente toda la matriz hasta encontrar el cluster a corregir
	
	
	//Como precaución para no correr codigo al pedo si en realidad es el mismo cluster, la solucion es trivial
	if (s1>s2) 
	{	
		*red=s1;
		
			
		if (*(clase+s1)>=0 || (*(clase+s1)==(-1)*s2)) *(clase+s1)=(-1)*s2;
			else
			{ 
				if (*(clase+s1)>(-1)*s2)
				{
					//printf("1");
					meterneg(clase,*(clase+s1),(-1)*s2);
					*(clase+s1)=(-1)*s2;
					
				}
				else
				{
					//printf("2");
					meterneg(clase,(-1)*s2,*(clase+s1));
					
				}
			}
	}
	if (s1<s2)
	{
		*red=s2;
		
		if (*(clase+s2)>=0 || (*(clase+s2)==(-1)*s1)) *(clase+s2)=(-1)*s1;
			else
			{ 
				if (*(clase+s2)>(-1)*s1)
				{
					//printf("3");
					
					meterneg(clase,*(clase+s2),(-1)*s1);
					*(clase+s2)=(-1)*s1;
				}
				else
				{
					//printf("4");
					meterneg(clase,(-1)*s1,*(clase+s2));
					
				}
			}
	}	
	else 
	{	
		*red=s2;
		
		
	}	
	
}


void  corregir_etiqueta(int *red,int *clase,int n)

{
	int k,l,r;
	
	//mostramostro(red,clase, n,n,"Estoy corrigiendo");
	for(k=0;k<n*n;k=k+n)
	{
		for(l=0;l<n;l++)
		{	
			if (*(red+k+l)!=0)
			{
				r=*(clase+*(red+k+l));
				//printf(" chequeando etiqueta : %i\n",r);
				while (r<0)
					{
						//printf(" chequeando colisión : %i\n",r);
						r=*(clase+abs(r));
						
						//printf(" Saltando a : %i\n",r);
						//mostra1(red,n,n,"asi estamos hasta aca");
					}
				*(red+k+l)=r;
			}
		}
	}
							
	//mostra1(red,n,n,"Esta es la matriz final");
}



//int quick_etiqueta(int *red,int *clase,int s1,int s2,int *rel)
//{
	//esta funcion todavia no la perfeccione, su intencion es reemplazar a etiqueta_falsa, y evitar q tenga q recorrer toda la matriz cada vez q se encuentran dos clusters
//	*clase=s1;
//	if (s1!=s2)
//	{
//		
//	}
//}

int percola (int *red,int n)
{
//Esta funcion es genial porq no necesita ordenar ni quitar etiquetas repetidas ni nada, solo asigna con un pointer dentro de otro pointer, de manera ordenada, y despues compara, y si un grupo esta tanto de un lado como del otro, devuelve a=1
	int i, *primer, *segundo,k,a,max;
	
	primer=(int *)malloc(n*n*sizeof(int));
	
	segundo=(int *)malloc(n*n*sizeof(int));
	
	
//seran la primer y ultima fila, o columna si no percola en el primer sentido
	k=n*n-n;
//variable auxiliar, poner una multiplicacion dentro de un pointer a veces tira error
	//printf("este es k: %i\n",k);
	a=0;
	max=0;
	//mostra1(red,n,n, "¿Percola esta red de arriba abajo?");
	//mostramostro(primer,segundo, 1,n*n, "garbage antes de corregir\n");
	for(i=0;i<n*n;i++) 
	{	
		*(primer+i)=0;
		*(segundo+i)=0;
	}

	for(i=0;i<n;i++)
	{	
		if (*(red+i))
		{
			*(primer+*(red+i)-1)=1;
			
			
		}
		//printf("\neste es el elemento de la primera fila:%i",1+i);
		if (*(red+k+i))
		{
			*(segundo+*(red+k+i)-1)=1;
			
		}
		//printf("\neste es el elemento de la ultima fila:%i",1+k+i);
		
		if ((*(red+i))>max) max=*(red+i);
		if ((*(red+k+i))>max) max=*(red+k+i);
		//printf("\neste es el max:%i",max);
		//mostra1(red,n,n, "¿Percola esta red de arriba abajo?");
		//mostramostro(primer,segundo, 1,n*n, "Primera y ultima fila\n");
	}
	
	
//esto va asignando un 1 y lo pone en la posicion que coincide con la etiqueta que tiene, de tal manera q la posicion 3 sea 1 solo si aparece la etiqueta 3 en algun momento
	i=0;
	while(i<max && a==0) 
	{	

		
		//printf("paso de chequeo numero : %i\n",i+1);
		if ((*(primer+i))&&(*(segundo+i))) 
			{
				
				a=1;
				//printf("PERCOLA de arriba abajo");
			}
		*(primer+i)=0;
		*(segundo+i)=0;
		i=i+1;
	}
	
	if (a==0)
	{
		
		//mostra1(red,n,n, "¿Percola esta red lado a lado?");
		//mostramostro(primer,segundo, 1,n*n, "garbage antes de corregir\n");
		
		for(i=0;i<n*n;i=i+n)
		{	
			if (*(red+i))
			{
				*(primer+*(red+i)-1)=1;
		
			
			}
			//printf("\neste es el elemento de la primera col:%i",1+i);
			if (*(red+i+n-1))
			{
				*(segundo+*(red+n-1+i)-1)=1;
			}
			//printf("\neste es el elemento de la ultima col:%i",1+n-1+i);
			if ((*(red+i))>max) max=(*(red+i));
			if ((*(red+n+i-1))>max) max=*(red+n+i-1);
			//printf("\n%i",max);
			//mostra1(red,n,n, "¿Percola esta red lado a lado?");
			//mostramostro(primer,segundo, 1,n*n, "Primera y ultima columna\n");
		}
		i=0;
		while(i<max && a==0) 
		{
			//printf("paso de chequeo numero : %i\n",i+1);
			if ((*(primer+i))&&(*(segundo+i))) 
				{
					a=1;
					//printf("PERCOLA de izq a der");
				}
			i=i+1;
		}
	
	}
	free(primer);
	free(segundo);
	//printf("¿Esto percolo? %i",a);
	
	return a;
}
		
int percolaofi(int *red,int n)
{
	int i,j,a,tam;
	a=0;
	tam=n*n;
	//mostra1(red,n,n,"\nesta es la matriz");
	for (i=0;i<n;i++)
	{
		//printf("\n%i \t",*(red+i));
		for (j=0;j<n;j++)
		{
			//printf("%i \t %i",i+1,tam-j);
			if ((*(red+i)==*(red+tam-j-1))&& *(red+i)!=0 && *(red+tam-j-1)!=0) a=1;
			//printf("  %i\n",*(red+tam-j-1));
			
		}
	}
	if(a==0)
	{
		for (i=0;i<n*n;i+=n)
		{
			//printf("\n%i \t",*(red+i));
			for (j=0;j<n*n;j+=n)
			{
				//printf("%i \t %i",i+1,tam-j);
				if ((*(red+i)==*(red+tam-j-1)) && *(red+i)!=0 && *(red+tam-j-1)!=0) a=1;
				//printf("  %i\n",*(red+tam-j-1));
				
			}
		}
	}
	//if (a) printf("PERCOLA");
	//getchar();
	return a;
}

int percolacuenta (int *red,int n, int *per)
{
//Esta funcion es genial porq no necesita ordenar ni quitar etiquetas repetidas ni nada, solo asigna con un pointer dentro de otro pointer, de manera ordenada, y despues compara, y si un grupo esta tanto de un lado como del otro, devuelve a=1
	int i, *primer, *segundo,k,a,max;
	
	primer=(int *)malloc(n*n*sizeof(int));
	
	segundo=(int *)malloc(n*n*sizeof(int));
	
	
//seran la primer y ultima fila, o columna si no percola en el primer sentido
	k=n*n-n;
//variable auxiliar, poner una multiplicacion dentro de un pointer a veces tira error
	//printf("este es k: %i\n",k);
	a=0;
	max=0;
	//mostra1(red,n,n, "¿Percola esta red de arriba abajo?");
	//mostramostro(primer,segundo, 1,n*n, "garbage antes de corregir\n");
	for(i=0;i<n*n;i++) 
	{	
		*(primer+i)=0;
		*(segundo+i)=0;
	}

	for(i=0;i<n;i++)
	{	
		if (*(red+i))
		{
			*(primer+*(red+i)-1)=1;
			
			
		}
		//printf("\neste es el elemento de la primera fila:%i",1+i);
		if (*(red+k+i))
		{
			*(segundo+*(red+k+i)-1)=1;
			
		}
		//printf("\neste es el elemento de la ultima fila:%i",1+k+i);
		
		if ((*(red+i))>max) max=*(red+i);
		if ((*(red+k+i))>max) max=*(red+k+i);
		//printf("\neste es el max:%i",max);
		//mostra1(red,n,n, "¿Percola esta red de arriba abajo?");
		//mostramostro(primer,segundo, 1,n*n, "Primera y ultima fila\n");
	}
	
	
//esto va asignando un 1 y lo pone en la posicion que coincide con la etiqueta que tiene, de tal manera q la posicion 3 sea 1 solo si aparece la etiqueta 3 en algun momento
	i=0;
	while(i<max) 
	{	

		
		//printf("paso de chequeo numero : %i\n",i+1);
		if ((*(primer+i))&&(*(segundo+i))) 
			{
				*(per+i)=1;
				a=i+1;
				//printf("PERCOLA de arriba abajo");
			}
		*(primer+i)=0;
		*(segundo+i)=0;
		i=i+1;
	}
	
	if (a==0)
	{
		
		//mostra1(red,n,n, "¿Percola esta red lado a lado?");
		//mostramostro(primer,segundo, 1,n*n, "garbage antes de corregir\n");
		
		for(i=0;i<n*n;i=i+n)
		{	
			if (*(red+i))
			{
				*(primer+*(red+i)-1)=1;
		
			
			}
			//printf("\neste es el elemento de la primera col:%i",1+i);
			if (*(red+i+n-1))
			{
				*(segundo+*(red+n-1+i)-1)=1;
			}
			//printf("\neste es el elemento de la ultima col:%i",1+n-1+i);
			if ((*(red+i))>max) max=(*(red+i));
			if ((*(red+n+i-1))>max) max=*(red+n+i-1);
			//printf("\n%i",max);
			//mostra1(red,n,n, "¿Percola esta red lado a lado?");
			//mostramostro(primer,segundo, 1,n*n, "Primera y ultima columna\n");
		}
		i=0;
		while(i<max ) 
		{
			//printf("paso de chequeo numero : %i\n",i+1);
			if ((*(primer+i))&&(*(segundo+i))) 
				{
					*(per+i)=1;
					a=i+1;
					//printf("PERCOLA de izq a der");
				}
			i=i+1;
			
		}
	
	}
	free(primer);
	free(segundo);
	//printf("¿Esto percolo? %i",a);
	
	return a;
}
			 
	
	 

int hoshenquick(int *red,int n)
{
  /*
    Esta funcion implementa en algoritmo de Hoshen-Kopelman.
    Recibe el puntero que apunta a la red y asigna etiquetas 
    a cada fragmento de red. 
  */

  int i,j,k,s1,s2,frag; //inicializa todo
  int *clase;		//empieza una etiqueta clase que guarda las etiquetas que va usando para el cluster que está distinguiendo

  frag=0;	//inicializa la clase temp en 0, esta es la izq del primer elemento
  
  
  clase=(int *)malloc(n*n*sizeof(int));	//reserva el espacio para clase

  for(k=0;k<n*n;k++) *(clase+k)=frag;	//inicializa clase en todos ceros
  
  // primer elemento de la red

  s1=0;	//definimos que el valor a izq de la posicion va a ser cero (no existe, no hay periodicidad)
  frag=2;//primera etiqueta de la clase
if (*red) 
{
	*red=frag;
	*(clase+frag)=frag;
}
	 // Si el primer valor de red esta ocupado, entonces asigno la clase automaticamente
//mostra1(red, n,n, "Punto de partida");  
  // primera fila de la red

  for(i=1;i<n;i++) 
    {
      if (*(red+i)) 
         {
           s1=*(red+i-1);  //etiqueta que vamos a poner despues a este cluster
           frag=actualizar(red+i,clase,s1,frag);//ponerle el numero de frag(o del que tiene atras) y asignarle esa etiqueta a la posicion de red, SI el anterior es 0 subir la clase usada, es decir subir el return frag en 1 y ponerle esa clase nueva a la posicion de clase

		//mostra1(red, n,n, "Primera fila"); 
         }
    }


  // el resto de las filas 

  for(i=n;i<n*n;i=i+n)
    {

      // primer elemento de cada fila

      if (*(red+i)) 
         {
           s1=*(red+i-n); 
           frag=actualizar(red+i,clase,s1,frag);
	
		//mostra1(red,n,n, "Cuerpo ppal");
         }
	//aca comienza con el codigo en todas las filas

      for(j=1;j<n;j++)
	if (*(red+i+j))
	  {
	    s1=*(red+i+j-1); 
            s2=*(red+i+j-n);

	    if (s1*s2>0)
	      {
		etiqueta_falsa(red+i+j,clase,s1,s2);
		//mostramostro(red, clase, n,n,"Aca hubo colision de clusters");
              }
	    else 
	      { if (s1!=0) frag=actualizar(red+i+j,clase,s1,frag);
	        else       frag=actualizar(red+i+j,clase,s2,frag);
		
		//mostra1(red, n,n, "Cuerpo ppal");
	      }
	  }
    }


  corregir_etiquetaquick(red,clase,n);

  free(clase);

  return frag;
}


void  corregir_etiquetaquick(int *red,int *clase,int n)

{
	//esta funcion solo recorre el perimetro, para chequear si percola o no rapidamente
	int k,l,r;
	k=n*n-n;
	//mostramostro(red,clase, n,n,"Estoy corrigiendo");
	for(k=0;k<n+1;k=k+n-1)
	{
		for(l=0;l<n*n;l=l+n)
		{	
			//printf(" chequeando etiqueta : %i\n",k+l+1);
			if (*(red+k+l)!=0)
			{
				r=*(clase+*(red+k+l));
				
				while (r<0)
					{
						//printf(" chequeando colisión : %i\n",r);
						r=*(clase+abs(r));
						
						//printf(" Saltando a : %i\n",r);
						//mostra1(red,n,n,"asi estamos hasta aca");
					}
				*(red+k+l)=r;
			}
		}
	}


	for(k=0;k<n*n;k=k+n*n-n)
	{
		for(l=1;l<(n-1);l=l+1)
		{	
			//printf(" chequeando etiqueta : %i\n",k+l+1);
			if (*(red+k+l)!=0)
			{
				r=*(clase+*(red+k+l));
				
				while (r<0)
					{
						//printf(" chequeando colisión : %i\n",r);
						r=*(clase+abs(r));
						
						//printf(" Saltando a : %i\n",r);
						//mostra1(red,n,n,"asi estamos hasta aca");
					}
				*(red+k+l)=r;
			}
		}
	}
							
	//mostra1(red,n,n,"Esta es la matriz final");
}

	
