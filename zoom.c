#include "funciones.h"

#define LECTURA 0
#define ESCRITURA 1

int main(int argc, char** argv){
    //Creamos el pipe para comunicarnos con el padre

    printf("ZOOM OPA \n");
    int *fd = (int*)malloc(sizeof(int) * 2);
    if(pipe(fd) == -1){
        printf("Error en syscall PIPE\n");
        exit(-1);
    };
    //recibir las variables y cambiarlas desde char a entero
    int filas = atoi(argv[3]); int columnas = atoi(argv[4]);
    int N = (filas * columnas * 4);
    printf("filas: %d, columnas: %d \n\n", filas, columnas);
    //Creamos un buffer
    float *buffer = (float *)malloc(sizeof(float) * N);
    //Leer la imagen que nos ha escrito el padre mediante el pipe
    float rBuff[1];
    int x = 0;
    printf("Wa a leer el buffer\n");
    read(fd[0],buffer,sizeof(buffer));
    close(fd[0]);
    printf("Buffer leído \n");
    //printBuffer(filas,columnas,buffer);

    //Proceso fork crea hijo
    int pid_suavizado;    
    if((pid_suavizado = fork()) == -1){
        printf("Error en syscall FORK\n");
        exit(-1);
    };

    if(pid_suavizado == 0){ // Proceso del hijo
        //Cerramos el modo escritura y abrimos el modo lectura del fd
        //Para comunicarnos con el siguiente proceso
        close(fd[ESCRITURA]);
        dup2(fd[LECTURA], STDIN_FILENO);    

        char *args[8]={"./zoom",argv[2], argv[3], argv[4], argv[5],argv[6],argv[7] , NULL};     
        //Cambiamos la imagen de ejecución con excevp
        //execvp(args[0],args);
    }
    else{ // Padre
        //El padre escribe el buffer de la imagen mediante write
        close(fd[LECTURA]);
        write(fd[ESCRITURA], buffer, N);
        close(fd[ESCRITURA]);
        wait(NULL);
    }
}