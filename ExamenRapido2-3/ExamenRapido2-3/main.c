//
//  main.c
//  ExamenRapido2-3
//
//  Created by Josué Carlos García Puig on 15/10/15.
//  Copyright © 2015 Avtelyes. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>

int main(int argc, const char * argv[]) {
    
    pid_t pid;
    
    pid = fork();
    
    if(pid < 0)
    {
        perror("Error al crear el proceso");
        exit(-1);
    }
    else if (pid == 0)
    {
        
    }
    else
    {
        
    }
    
    return 0;
}
