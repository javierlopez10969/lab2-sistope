//Autores: Javier López - Felipe Sepulveda
/*
• -I filename : especifica el nombre de la imagen de entrada
• -O filename : especifica el nombre de la imagen final resultante del pipeline.
• -M n´umero : especifica el n´umero de filas de la imagen
• -N n´umero : especifica el n´umero de columnas de la imagen
• -r factor : factor de replicaci´on para Zoom-in
• -g factor : especifica en cuantos grados rotar a la imagen: 0, 90, 180 o 270.
• -b: bandera que indica si se entregan resultados por consola. En caso de que se ingrese este flag deber´a
mostrar: etapas por las que va pasando la imagen, dimensiones de la imagen antes y despu´es de aplicar
zoom-in, ejecuci´on finalizada.

// ./lab2 -I cameraman_256x256.raw -O imagen_salida.raw -M 256 -N 256 -r 2 -g 90
*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "funciones.h"

#define LECTURA 0
#define ESCRITURA 1

int main(int argc, char **argv)
{
    char *nombreImagen = NULL;
    char *imagenSalida = NULL;
    char c;
    int filas, columnas, bandera, factor, grados, opterr;
    filas = 0;
    columnas = 0;
    bandera = 0;
    factor = 0;
    factor = 0;
    opterr = 0;
    opterr += 1;
    //el siguiente ciclo se utiliza para recibir los parametros de entrada usando getopt
    while ((c = getopt(argc, argv, "I:O:M:N:r:g:b:")) != -1)
        switch (c)
        {
        case 'I':
            nombreImagen = optarg;
            break;
        case 'O':
            imagenSalida = optarg;
            break;
        case 'M':
            sscanf(optarg, "%d", &filas);
            break;
        case 'N':
            sscanf(optarg, "%d", &columnas);
            break;
        case 'r':
            sscanf(optarg, "%d", &factor);
            break;
        case 'g':
            sscanf(optarg, "%d", &grados);
            break;
        case 'b':
            bandera = 1;
            break;
        case '?':

            if (optopt == 'c')
            {
                fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
            }

            else if (isprint(optopt))
                fprintf(stderr, "Opcion desconocida `-%c'.\n", optopt);
            else
                fprintf(stderr,
                        "Opcion con caracter desconocido `\\x%x'.\n",
                        optopt);
            return 1;

        default:
            abort();
    }

    if (nombreImagen == NULL || imagenSalida == NULL ||
    filas == 0 || columnas == 0 ||factor == 0){
        printf("Faltan entradas para poder ejecutar el programa \n");
    }
    else if(columnas!= filas){
        printf("Cantidad de filas y columnas es distinto \n");
    }
    //Verificacion de grados
    else if(grados%90 != 0){
        printf("Los grados deben multiplos de 90 \n");
    }
    else{
        if (bandera != 0){
        printf("Nombre imagen de entrada : %s \n Imagen salida : %s \n  filas : %d \n columnas : %d \n factor : %d \n bandera : %d\n",
        nombreImagen, imagenSalida, filas, columnas, factor, bandera);
        }
    }
    //creación de un nuevo proceso
    //definir variables para pipe
    int fd[2];
    pipe(fd);
    //variables para mensajes (entradas y salidas)
    char bufferEntrada[32] = "xd";
    char bufferSalida[32];
    int num = 0;
    //nuevo proceso (proceso hijo escribe, padre lee)

    int pid1= fork();
    //se cumple la condición cuando falla la creación de un nuevo proceso
    if(pid1 < 0){
        if (bandera== 1)printf("fallo la creación de proceso (fork)");
        return 1;
    }
    //se cumple la condición solo para un proceso "padre"
    //debe realizar la espera hasta que el proceso hijo termine.
    else if(pid1 > 0){
        //cerrar el fd de escritura
       
        close(fd[ESCRITURA]);
        num = read(fd[LECTURA], bufferSalida, sizeof(char)*32);
        if (bandera== 1){
            printf("padre lee %d bytes: %s \n", num, bufferSalida);
            printf("soy el padre y leí el mensaje\n");
        }
        
        wait(NULL);
    }
    //Si se cumple la condición solo para un proceso "hijo" (pid == 0)
    //Como soy hijo debo realizar el excev para ir a un nuevo proceso de lectura.
    else{
        //cerrar el fd de lectura
        close(fd[LECTURA]);
        //escritura
        write(fd[ESCRITURA], bufferEntrada, sizeof(char)*32);
        //definir buffers para almacenar los argumentos.
        char buffFilas[10];
        char buffColumnas[10];
        char buffFactor[10];
        char buffGrados[10];
        char buffFlag[10];
        //Traspasamos las variables de entrada
        sprintf(buffFilas, "%d", filas);
        sprintf(buffColumnas, "%d", columnas);
        sprintf(buffFactor, "%d", factor);
        sprintf(buffGrados, "%d", grados);
        sprintf(buffFlag, "%d", bandera);
        if (bandera== 1)printf("soy el hijo y escribi el mensaje\n");
        char *args[9]={"./lectura", nombreImagen, imagenSalida, buffFilas, buffColumnas, buffFactor, buffGrados, buffFlag, NULL};     
        execvp(args[0],args);
    }
    return 0;
}
//EJEMPLO DE USO
// make
// ./lab2 -I cameraman_256x256.raw -Z salida_i_zoom.raw -S imagen_i_suavizado.raw -M 256 -N 256 -r 2
