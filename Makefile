CC=gcc
CFLAGS=-lm
all : lab2.o lectura.o zoom.o suavizado.o rotacion.o 

lab2: lab2.c funciones.c funciones.h
	$(CC) funciones.c lab2.c -o lab2 $(CFLAGS)

lectura: lectura.c funciones.c funciones.h
	$(CC) funciones.c lectura.c -o lectura $(CFLAGS)

zoom: zoom.c funciones.c funciones.h
	$(CC) funciones.c zoom.c -o zoom $(CFLAGS)

suavizado: suavizado.c funciones.c funciones.h
	$(CC) funciones.c suavizado.c -o suavizado $(CFLAGS)

rotacion: rotacion.c funciones.c funciones.h
	$(CC) funciones.c rotacion.c -o rotacion $(CFLAGS)

clean:
	rm -f *.o all
.PHONY : clean