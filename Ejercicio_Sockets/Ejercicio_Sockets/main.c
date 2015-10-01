//
//  main.c
//  Ejercicio_Sockets
//
//  Created by Josué Carlos García Puig on 28/09/15.
//  Copyright © 2015 Avtelyes. All rights reserved.
//

/* p1.c -- demostrate the mecanism of
 *         shared memory
 * blog   : snatverk.blogspot.com
 * date   : Tue Sep 14 10:54:37 WEST 2010
 * compile: $ gcc p1.c -o p1
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
    int i;
    for (i = 0; i < MAXBUF; i++)
        buffer[i] = i;
    /* The daemon executes until press some character */
    char c;
    c = getchar();
    
    /* Free the shared memory */
    shmdt ((char *)buffer);
    shmctl (id_zone, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
