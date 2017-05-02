Ignacio Perez Ipiña    425/12
ipina@qi.fcen.uba.ar 
hbossetti@gmail.com

Actualizacion 24/3/2017: Mucho mas avanzado, quedan ajustes y cosas, pero la base la tengo, y pude limpiar todos los errores de memoria, y hacer mas rapido el codigo con hoshenquick para los casos donde las etiquetas del cuerpo no es necesario corregir. Lunes pongo a punto los ajustes, gamma-matching, scaling.

¿Que tal?

Resumen de lo que hay aca

rama master : Lo que espero quede final para el tp
rama oficial: Cambios que trato queden analizables para el tp.
rama desarrollo: La forma como se me canta cambiar al codigo, pensando en hacerlo mas rapido. No analizable para el tp.
rama errorbizarr: en un momento quise liberar la memoria de dos pointers de n*n y me tiro un error extraño que quise grabar.(ya lo resolvi, era un acceso al array fuera de su tamaño, que tiraba error cuando querias liberar el espacio)

Corro siempre desde la rama oficial con:

gcc -Wall -O3 <ejercicio_con_include_progfinal.h> progfinal.c -o ejecuta
./programa>plot.txt
o ./programa

y despues ploteo con gnuplot

programa.c es el codigo basico, esta un poco atrasado en correcciones al momento

