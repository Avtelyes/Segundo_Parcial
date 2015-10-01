//
//  cliente.c
//  Ejercicio_Sockets
//
//  Created by Josué Carlos García Puig on 29/09/15.
//  Copyright © 2015 Avtelyes. All rights reserved.
//

/* p2.c -- demostrate the mecanism of
 *         shared memory
 * blog   : snatverk.blogspot.com
 * compile: $ gcc p2.c -o p2
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h> /* shm*  */

#define FILEKEY "/bin/cat"
#define KEY 1300
#define MAXBUF 10

int main () {
    /* Key to shared memory */
    int key = ftok(FILEKEY, KEY);
    if (key == -1) {
        fprintf (stderr, "Error with key \n");
        return -1;
    }
    
    /* we create the shared memory */
    int id_zone = shmget (key, sizeof(int)*MAXBUF, 0777 | IPC_CREAT);
    if (id_zone == -1) {
        fprintf (stderr, "Error with id_zone \n");
        return -1;
    }
    
    printf ("ID zone shared memory: %i\n", id_zone);
    
    int *buffer; /* shared buffer */
    /* we declared to zone to share */
    buffer = shmat (id_zone, (char *)0, 0);
    if (buffer == NULL) {
        fprintf (stderr, "Error reserve shared memory \n");
        return -1;
    }
    
    printf ("Pointer buffer shared memory: %p\n", buffer);
    
    /* Write the values of shared memory */
    int i;
    for (i = 0; i < MAXBUF; i++)
        printf ("%i\n", buffer[i]);
    return 0;
}
