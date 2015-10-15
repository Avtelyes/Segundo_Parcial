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

int main(int argc, const char * argv[])
{
    
    sigset_t ninguna, todas;
    
    sigfillset(&todas);
    
    sigdelset(&todas, SIGALRM);
    
    struct dirent *dir;
    DIR *pDir;
    
    pDir = opendir ("datos");
    if (pDir == NULL) {
        printf ("Creando directorio'%s'\n","datos");
        system("mkdir datos");
        system("cd datos");
    }
    
    int i;
    char * dst= "touch a";
    
    for(i=0; i<5; ++i)
    {
        itoa(i, dst+7, i);
        system(dst);
    }
    
    
    
    closedir (pDir);
    
    
    return 0;
}
