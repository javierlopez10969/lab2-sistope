# lab2-sistope
Laboratorio número dos de sistemas opertativos realizado por Javier López y Felipe Sepulveda.
<p align="center"><a target="_blank"><img src="https://upload.wikimedia.org/wikipedia/commons/3/35/The_C_Programming_Language_logo.svg" width="400"></a></p>

## Comandos para ejecutar
Para ejecutar estos scripts, abra una terminal y ejecute el siguiente comando para compilar:

### `make`

Entradas que recibe este laboratorio:
### • -I filename : especifica el nombre de la imagen de entrada
### • -Z filename : especifica el nombre de la imagen resultante del zoom-in
### • -S filaname : especifica el nombre de la imagen resultante del suavizado (a la resultante del zoom-in)
### • -M numero : especifica el número de filas de la imagen
### • -N numero : especifica el número de columnas de la imagen
### • -r factor : factor de replicación para Zoom-in
### • -b: bandera que indica si se entregan resultados por consola. En caso de que se ingrese este flag deberá

Para ejecutar el código sin mostrar nada por pantalla su bandera debe estar en 0, por default es cero, asi que si no ingresa nada quedará en 0.


### `/lab2 -I cameraman_256x256.raw -O imagen_salida.raw -M 256 -N 256 -r 2 -g 90`

Para mostrar las entradas por pantalla ejecute :  

### `/lab2 -I cameraman_256x256.raw -O imagen_salida.raw -M 256 -N 256 -r 2 -g 90 -b`

Si no entrega alguna de las entradas el programa no correrá. Tampoco correrá en caso de tener una cantidad distinta entre filas y columnas.
