#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     27000          // iteraciones
#define N     5            // lado de la red simulada


void  llenar(int *red,int n,float prob); //llena con 1 y ceros con prob p de ser 1. (falta programar)

void mostrar(int *red, int n); // muestra la matriz en la pantalla

void mostramostro(int *red, int *clase, int n, char *k);//Puedo corregir la forma que me muestra los pasos en todo el codigo.

int   hoshen(int *red,int n);			// hace el algoritmo de reemplazar todo por etiquetas de cluster y las repara

int   actualizar(int *red,int *reclase,int s,int frag);  //actualiza clase y la va construyendo para que tenga clusters de etiquetas

int  etiqueta_falsa(int *red,int *clase,int s1,int s2, int i, int n); //Voy a usarla para corregir todo el grupo superior que estaría conectado a este cluster que se une

//void  corregir_etiqueta(int *red,int *clase,int n); // no la voy a usar

//int   percola(int *red,int n); //esta si! revisa si el cluster percola o no.

int main(int argc,char *argv[])
{
  int    i,j,*red,n,z;
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
	 //if (percola(red,n)) 
            
       // prob+=(-1.0/denominador); 
       // else prob+=(1.0/denominador);
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

  int i,j,k,s1,s2,frag,l,s; //inicializa todo
  int *clase;		//empieza una etiqueta clase que guarda las etiquetas que va usando para el cluster que está distinguiendo

  frag=0;	//inicializa la clase temp en 0, esta es la izq del primer elemento
  l=0;
  
  clase=(int *)malloc(n*n*sizeof(int));	//reserva el espacio para clase

  for(k=0;k<n*n;k++) *(clase+k)=frag;	//inicializa clase en todos ceros
  
  // primer elemento de la red

  s1=0;	//definimos que el valor a izq de la posicion va a ser cero (no existe, no hay periodicidad)
  frag=2;//primera etiqueta de la clase
if (*red) *clase=frag;

	 // mete la posición red, es decir la posicion primera, NO su valor y asi sé qué posición estoy asignando, asi como la clase, el valor de la posicion en la izquierda y frag, la etiqueta que voy actualizando
mostramostro(red, clase, n, "Primer elemento");  
  // primera fila de la red

  for(i=1;i<n;i++) 
    {
      if (*(red+i)) 
         {
           s1=*(clase+i-1);  //etiqueta que vamos a poner despues a este cluster
           frag=actualizar(red+i,clase+i,s1,frag);//ponerle el numero de frag(o del que tiene atras) y asignarle esa etiqueta a la posicion de clase si el anterior es 0 subir la clase usada, es decir subir el return en y ponerle esa clase nueva a la posicion de clase

		mostramostro(red, clase, n, "Primera fila"); 
         }
    }


  // el resto de las filas 

  for(i=n;i<n*n;i=i+n)
    {

      // primer elemento de cada fila

      if (*(red+i)) 
         {
           s1=*(clase+i-n); 
           frag=actualizar(red+i,clase+i,s1,frag);
	
		mostramostro(red,clase,n, "Cuerpo ppal");
         }
	//aca comienza con el codigo en todas las filas

      for(j=1;j<n;j++)
	if (*(red+i+j))
	  {
	    s1=*(clase+i+j-1); 
            s2=*(clase+i+j-n);

	    if (s1*s2>0)
	      {
		s=etiqueta_falsa(red,clase,s1,s2,i,n);
		*(clase+i+j)=s;
	      }
	    else 
	      { if (s1!=0) frag=actualizar(red+i+j,clase+i+j,s1,frag);
	        else       frag=actualizar(red+i+j,clase+i+j,s2,frag);
		
		mostramostro(red, clase, n, "Cuerpo ppal");
	      }
	  }
    }


  //corregir_etiqueta(red,clase,n);

  free(clase);

  return 0;
}
int actualizar (int *logo,int *reclase,int s, int frag)
	{
	//Esta funcion va a tomar el valor que aparece en s como el valor izquierdo o superior, y si es distinto de cero va a actualizar el valor de la red a la etiqueta usada frag, si no va a subir el valor de frag en una unidad
		if (s!=0)
		{
			*reclase=s;
		}  
		else
		{
			frag++;	
			
			*reclase=frag;
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

void mostrar(int *print, int n)
{
	int  i,j;
	for (i=0;i<n;i++){
		printf("\n");
		for (j=0;j<n;j++){
			printf("%3i",*(print+i*n+j));
		}
	}
}

void mostramostro(int *red, int *clase, int n, char *k)
{
	printf("%s\n", k); 
	//mostrar(red,n);
	printf("\n");
	mostrar(clase,n);
	printf("\n");
	
	 
	getchar();  
}

int etiqueta_falsa(int *red,int *clase,int s1,int s2,int i, int n)
{	
	int s,sp, k,l;
	
	if (s1!=s2){
		if (s1>s2) 
		{	
			s=s1;
			sp=s2;	
		
		}	
		else 
		{	
			s=s2;
			sp=s1;
			
		}	
		printf("s=%i\n",s);
		printf("sp=%i\n",sp);
		for(k=0;k<(i/n)+1;k++){
			for(l=0;l<n;l++){
				printf("valor anterior=%i\n",*(clase+k*n+l));
				printf("fila analizada=%i\n",k+1);
				printf("col analizada=%i\n",l+1);
				if ((*(clase+k*n+l))==sp){ 
				
					*(clase+k*n+l)=s;
				
					
				}
				mostramostro(red, clase,n, "Unión de clusters");
			}
		}
	}	
	else{
		s=s1;
	}
	return s;	
	
}

	
	 
	
