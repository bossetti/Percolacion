
void  llenar(int *red,int n,float prob); //llena con 1 y ceros con prob p de ser 1. (falta programar)

void mostrar(int *red, int n1, int n2); // muestra la matriz en la pantalla

void mostra1(int *red, int n1, int n2, char *k); //muestra solo una matriz con un mensaje adicional

void mostramostro(int *red, int *clase, int n1, int n2, char *k);//Puedo corregir la forma que me muestra los pasos en todo el codigo.

int   hoshen(int *red,int n);			// hace el algoritmo de reemplazar todo por etiquetas de cluster y las repara

int   hoshenquick(int *red,int n);			// hace el algoritmo de reemplazar todo por etiquetas de cluster y las repara


int   actualizar(int *red,int *clase,int s,int frag);


void etiqueta_falsa(int *red,int *clase, int s1,int s2);


void  corregir_etiqueta(int *red,int *clase,int n); //recorre la red y va corrigiendo las etiquetas que tienen un menos

void  corregir_etiquetaquick(int *red,int *clase,int n); //recorre la red y va corrigiendo las etiquetas que tienen un menos


int   percola(int *red,int n); //CANCELADA super impractica y no esta funcionando

float volare(int argc,int  na,int za);//funcion que hace el 1a

float  diferenciare(int arc, int na, int za,float *res, int div);

int percolacuenta(int *red,int n, int *per);

void contarclusters(int *red, int *clusters,int n);

float pcmedio( int na, int za,int div);

void meterneg(int *clase, int start, int pos);

float promedio(float *pointe,int  na,int opcion,int inicio,int final);

