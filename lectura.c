#include "funciones.h"

#define LECTURA 0
#define ESCRITURA 1

int main(int argc, char** argv){
    //Nombre de la imagen
    char bufferNombre[50];
    strcpy(bufferNombre, argv[1]);
    //recibir las variables y cambiarlas desde char a entero
    int filas = atoi(argv[3]); int columnas = atoi(argv[4]);
    int N = (filas * columnas * 4);
    printf("filas: %d, columnas: %d \n\n", filas, columnas);
    //Creamos un buffer
    float *buffer = (float *)malloc(sizeof(float) * N);
    //Leer la imagen
    leerArchivo(bufferNombre, filas, columnas, buffer, N);
    //printBuffer(filas,columnas,buffer);
    //Creacion pipe
    int *pipe1 = (int*)malloc(sizeof(int) * 2);
    if(pipe(pipe1) == -1){
        printf("Error en syscall PIPE\n");
        exit(-1);
    };
    //Proceso fork crea hijo
    int pid_gray;    
    if((pid_gray = fork()) == -1){
        printf("Error en syscall FORK\n");
        exit(-1);
    };

    


    if(pid_gray == 0){ // Proceso del hijo
        close(pipe1[ESCRITURA]);
        dup2(pipe1[LECTURA], STDIN_FILENO);

        // for (int i = 0; i < img->size; i++){printf("%d",img->data[i]);}

        char buffWidth[10];
        char buffHeight[10];
        char buffChannels[10];
        char buffSize[20];


        char *args[]={"./gray", buffWidth, buffHeight, buffChannels, buffSize, argv[1], argv[2], argv[3], argv[4], argv[5], NULL};     
        execvp(args[0],args);
    }
    else{ // Padre
        close(pipe1[LECTURA]);
        //write(pipe1[ESCRITURA], img->data, img->size);
        close(pipe1[ESCRITURA]);
        wait(NULL);
    }
}