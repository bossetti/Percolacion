Ignacio Perez Ipiña    425/12
ipina@qi.fcen.uba.ar 
hbossetti@gmail.com

Actualizacion 2/4/2017: Corregi todos los errores serios, tengo resultados razonables, hasta el 3, casi 4. El resto de los ejercicios los terminare.

¿Que tal?

Resumen de lo que hay aca

rama master : Lo que espero quede final para el tp
rama oficial: Cambios que trato queden analizables para el tp.
rama desarrollo: La forma como se me canta cambiar al codigo, pensando en hacerlo mas rapido. No analizable para el tp.
rama errorbizarr: en un momento quise liberar la memoria de dos pointers de n*n y me tiro un error extraño que quise grabar.(ya lo resolvi, era un acceso al array fuera de su tamaño, que tiraba error cuando querias liberar el espacio)

Corro siempre desde la rama oficial con:

gcc -Wall -O3 <ejercicio_con_include_progfinal.h> progfinal.c -o ejecuta -lm

./programa

y despues ploteo con gnuplot
o ajusto con QtiPlot

programa.c es el codigo basico, esta un poco atrasado en correcciones al momento
pero 
ej1a.c
ej1b.c
ej1c.c
ej1d.c
ej1dalt.c
ej2.c
ej3.c

Corren bien

