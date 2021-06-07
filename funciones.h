//En  este archivo van las cabeceras de las funciones.
#ifndef funciones_h_
#define funciones_h_

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

//Cabeceras
int leerArchivo(char * pathname , int filas, int columnas,float * buffer,int N);
void zoomIN(int filas, int columnas,float * buffer , float ** zoom, int factor, int N);
void suavizado(int filas, int columnas,float * buffer , float ** suavizados, int N);
void printBuffer(int filas, int columnas, float * buffer);
int escribirImagen(char * salidaName , int filas, int columnas,float * buffer,int N);

//fin de directivas
#endif // funciones_h_