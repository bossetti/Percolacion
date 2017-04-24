#include "progfinal.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     27000          // iteraciones
#define N     5            // lado de la red simulada


int main()
{
	int na,za;
	na=N;
	za=Z;
	volare(3,na,za);
	printf("fin de 1a");
  	diferenciare(3,na,za);

}

