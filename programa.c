#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define P     16             // 1/2^P, P=16
#define Z     27000          // iteraciones
#define N     30             // lado de la red simulada


void  llenar(int *red,int n,float prob); //llena con 1 y ceros con prob p de ser 1. (falta programar)

int   hoshen(int *red,int n);			// ya hecho

int   actualizar(int *red,int *clase,int s,int frag);  //creo q actualiza la red, y devuelve un numero que seria la etiqueta para seguir usando (o la cambia)

void  etiqueta_falsa(int *red,int *clase,int s1,int s2); //no tengo idea, prrrobemossssss

void  corregir_etiqueta(int *red,int *clase,int n); // supongo algo que ver con unión de clusters

int   percola(int *red,int n); //esta si! revisa si el cluster percola o no.

int main(int argc,char *argv[])
{
  int    i,j,*red;
  float  prob,denominador;

  n=N;
  z=Z;

  if (argc==3) 
     {
       sscanf(argv[1],"%d",&n);
       sscanf(argv[2],"%d",&z);
     }
    
  red=(int *)malloc(n*n*sizeof(int));



  for(i=0;i<z;i++)
    {
      prob=0.5;
      denominador=2.0;
 
      srand(time(NULL));

      for(j=0;j<P;j++)
        {
          llenar(red,n,prob);
      
          hoshen(red,n);
        
          denominador=2.0*denominador;

          if (percola(red,n)) 
             prob+=(-1.0/denominador); 
          else prob+=(1.0/denominador);
        }
    }

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

  frag=0;	//inicializa la clase temp en 0, nose por que
  
  clase=(int *)malloc(n*n*sizeof(int));	//reserva el espacio para clase

  for(k=0;k<n*n;k++) *(clase+k)=frag;	//inicializa clase en todos ceros
  
  // primer elemento de la red

  s1=0;	//definimos que el valor a izq de la posicion va a ser cero (no existe, no hay periodicidad)
  frag=2;
  if (*red) frag=actualizar(red,clase,s1,frag); // "si el primer valor de la red es TRUE, es decir 1, entonces hacer que frag, el numero de etiqueta temporal, sea el valor que venia teniendo si red es 1, o diferente es 0, como ingresan el la misma posicion que esta, entonces es el mismo.
  
  // primera fila de la red

  for(i=1;i<n;i++) 
    {
      if (*(red+i)) 
         {
           s1=*(red+i-1);  //etiqueta que vamos a poner despues a este cluster
           frag=actualizar(red+i,clase,s1,frag);//ponerle el numero de clase a la subir a la posicion de red si el de la derecha es 0 subir la clase usada, es decir subir el return en 1
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
         }

      for(j=1;j<n;j++)
	if (*(red+i+j))
	  {
	    s1=*(red+i+j-1); 
            s2=*(red+i+j-n);

	    if (s1*s2>0)
	      {
		etiqueta_falsa(red+i+j,clase,s1,s2);
	      }
	    else 
	      { if (s1!=0) frag=actualizar(red+i+j,clase,s1,frag);
	        else       frag=actualizar(red+i+j,clase,s2,frag);
	      }
	  }
    }


  corregir_etiqueta(red,clase,n);

  free(clase):

  return 0;
}
void actualizar (int *red,int *clase,int s,int frag)

void  llenar(int *red,int n,float prob)//toma la red que le ponen, el lado y la probabilidad que va a usar en las posiciones.
{
	float r
	int  i,j,*red
	for (i=0;i<n;i++){
		for(j=0; j<n; j++){
			r=srand(time(NULL));
			if r<p	{			
				*(red+i+j)=1;
			}
			else{
				*(red+i+j)=0;
			}
		}
	}
}

int actualizar (int *red,int *clase,int s,int frag)
{
	*red=s
	
