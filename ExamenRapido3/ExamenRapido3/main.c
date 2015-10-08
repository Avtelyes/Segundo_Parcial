//
//  main.c
//  ExamenRapido3
//
//  Created by Josué Carlos García Puig on 08/10/15.
//  Copyright © 2015 Avtelyes. All rights reserved.
//

#include <signal.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h> /* shm*  */
#include <time.h>

#define FILEKEY "/bin/cat"
#define KEY 1300
#define MAXBUF 10

void impresionPadre(int);
void contadorCTRLZ(int);
void contadorCTRLC(int);
int z = 0, c=0, segundos = 3;

int *buffGen;

int main(int argc, const char * argv[]) {
    
    int i = 0;
    
    srand((int)time(NULL));
    
    pid_t hijo;
    
    hijo = fork();
    
    /* Se define la llave para crear el identificador IPC con un numero que conozcan ambos procesos */
    int key = ftok(FILEKEY, KEY);
    if (key == -1) {
        fprintf (stderr, "Error con la llave \n");
        return -1;
    }
    
    /* Se crea la memoria compartida */
    int id_zone = shmget (key, sizeof(int)*MAXBUF, 0777 | IPC_CREAT);
    if (id_zone == -1) {
        fprintf (stderr, "Error al crear la zona de memoria \n");
        return -1;
    }
    
    //printf ("ID de la memoria compartida: %i\n", id_zone);
    
    int *buffer; /* buffer compartido */
    /* Se reserva la memoria a compartir */
    buffer = shmat (id_zone, (char *)0, 0);
    if (buffer == NULL) {
        fprintf (stderr, "Error al reservar la memoria compartida \n");
        return -1;
    }
    
    buffGen = buffer;
    
    //printf ("Apuntador a la memoria compartida: %p\n", buffer);
    
    if(hijo < 0)
    {
        perror("Error al crear fork\n");
        exit(1);
    }
    else if (hijo == 0)
    {
        signal(SIGTSTP,SIG_IGN);
        signal(SIGINT, SIG_IGN);
        sleep(10);
        *buffer = getpid();
        kill(getppid(), SIGUSR1);
    }
    else
    {
        if (signal(SIGUSR1,impresionPadre) == SIG_ERR){
            printf("No se pudo establecer el manejador de la visualizacion.....FAIL\n");
        }
        signal(SIGTSTP,SIG_IGN);
        signal(SIGINT, SIG_IGN);
        if (signal(SIGTSTP,contadorCTRLZ) == SIG_ERR){
            printf("No se pudo establecer el manejador de la senal.....FAIL\n");
        }
        if (signal(SIGINT, contadorCTRLC) == SIG_ERR) {
            printf("ERROR: No se pudo establecer el manejador de la señal\n");
        }
        
        /* Liberacion de la memoria compartida */
        shmdt ((char *)buffer);
        shmctl (id_zone, IPC_RMID, (struct shmid_ds *)NULL);
        
        while(1)
        {
            sleep(segundos);
            printf("Aparezco cada %d segundos\n", segundos);
        }
        
        exit(0);
        
        
    }
    
    return 0;
}

void impresionPadre(int ids)
{
    printf("Se ha pulsado %d veces CTRL+C y se ha pulsado %d veces CTRL+Z. Acabando…\n",c,z);
    //kill(*buffGen, SIGKILL);
    //printf("El pid es: %d", *buffGen);
    
}

void contadorCTRLZ(int ids)
{
    z++;
}

void contadorCTRLC(int ids)
{
    c++;
}
