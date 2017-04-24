#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     27000          // iteraciones
#define N     5            // lado de la red simulada


void  llenar(int *red,int n,float prob); //llena con 1 y ceros con prob p de ser 1. (falta programar)

void mostrar(int *red, int n1, int n2); // muestra la matriz en la pantalla

void mostra1(int *red, int n1, int n2, char *k); //muestra solo una matriz con un mensaje adicional

void mostramostro(int *red, int *clase, int n1, int n2, char *k);//Puedo corregir la forma que me muestra los pasos en todo el codigo.

int   hoshen(int *red,int n);			// hace el algoritmo de reemplazar todo por etiquetas de cluster y las repara

int   actualizar(int *red,int *clase,int s,int frag);


void etiqueta_falsa(int *red,int *clase, int s1,int s2);


void  corregir_etiqueta(int *red,int *clase,int n); //recorre la red y va corrigiendo las etiquetas que tienen un menos

int   percola(int *red,int n); //CANCELADA super impractica y no esta funcionando



int main(int argc,char *argv[])
{
  int    i,j,*red,n,z;
  float  prob,denominador,prom;

  n=N;
  z=Z;

  if (argc==3) 
     {
       sscanf(argv[1],"%d",&n);
       sscanf(argv[2],"%d",&z);
     }
    
  red=(int *)malloc(n*n*sizeof(int));
  
  prom=0;//defino un promedio que voy a usar

  for(i=0;i<z;i++)
    {
      printf("\nEsta es la iteracion :%i",i);
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
	  //mostra1(red,n,n,"Matriz de partida");
	 
        }
	prom=prom+prob;
    }
  
  
	
  printf ( "%.3f \t %.3f \n", prob, prom/z );
  free(red);

  return 0;
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
	srand(time(NULL));
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



void etiqueta_falsa(int *red,int *clase,int s1,int s2)
{	
	//en el caso donde hay un vertice donde se encuentran dos clusters, recorre aburridamente toda la matriz hasta encontrar el cluster a corregir
	
	
	//Como precaución para no correr codigo al pedo si en realidad es el mismo cluster, la solucion es trivial
if (s1>s2) 
	{	
		*red=s2;
		
			
		*(clase+s1)=(-1)*s2;
	
	}
	if (s1<s2)
	{
		*red=s1;
		
		*(clase+s2)=(-1)*s1;
		
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
							
	mostra1(red,n,n,"Esta es la matriz final");
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
	for(i=0;i<n*n;i++) 
	{	
		*(primer+i)=0;
		*(segundo+i)=0;
	}
//inicializo en cero
	for(i=0;i<n;i++)
	{	
		if (*(red+i))
		{
			*(primer+*(red+i)-1)=1;
		
			
		}
		if (*(red+k+i))
		{
			*(segundo+*(red+k+i)-1)=1;
		}
		
		if ((*(red+i))>max) max=*(red+i);
		if ((*(red+k+i))>max) max=*(red+k+i);
		//printf("\n%i",max);
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
				//printf("PERCOLAPERCOLAPERCOLA");
			}
		i=i+1;
	}
	
	if (a==0)
	{
		for(i=0;i<max;i++) 
		{	
			*(primer+i)=0;
			*(segundo+i)=0;
		}
		for(i=0;i<n*n;i=i+n)
		{	
			if (*(red+i))
			{
				*(primer+*(red+i)-1)=1;
		
			
			}
			if (*(red+i+n))
			{
				*(segundo+*(red+n-1+i)-1)=1;
			}
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
					//printf("PERCOLAPERCOLAPERCOLA");
				}
			i=i+1;
		}
	}
		
	//printf("¿Esto percolo? %i",a);
	
	return a;
}
		
	 
	
	 
	
