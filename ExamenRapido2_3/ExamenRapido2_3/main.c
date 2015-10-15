//
//  main.c
//  ExamenRapido2_3
//
//  Created by Josué Carlos García Puig on 15/10/15.
//  Copyright © 2015 Avtelyes. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void gestor_alarm(int);
int grabar = 1;

int main(int argc, const char * argv[])
{
    
    sigset_t ninguna, todas;
    
    sigfillset(&todas);
    
    sigdelset(&todas, SIGALRM);
    
    int err;
    
    signal(SIGALRM, gestor_alarm );
    
    struct dirent *dir;
    DIR *pDir;
    
    pDir = opendir ("datos");
    if (pDir == NULL) {
        printf ("Creando directorio'%s'\n","datos");
        system("mkdir datos");
    }
    
    system("cd datos/");
    system("touch a");
    
    int i;
    char * dst= "touch a";
    char * temp;
    
    for(i=0; i<5; ++i)
    {
        /*sprintf(temp, ", val%d", i);
        strcat(dst, temp);
        printf(dst);
        system(dst);*/
        system("touch a");
    }
    
    alarm(3);
    
    while (grabar == 1) {
        system("echo 'x' >> a");
    }
    
    
    closedir (pDir);
    
    system("cd ..");
    system("ls -la datos/");
    
    
    return 0;
}

void gestor_alarm(int senial)
{
    grabar = 0;
}



