//
//  main.c
//  ExamenRapido2
//
//  Created by Josué Carlos García Puig on 01/10/15.
//  Copyright © 2015 Avtelyes. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TCP_PORT 8000

int main(int argc, const char * argv[]) {
    
    struct sockaddr_in direccion;
    char buffer[1000];
    int numeros[10];
    
    int servidor, cliente;
    
    int leidos, escritos, numero1, numero2;
    
    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }
    
    //Crear el socket
    servidor = socket(PF_INET, SOCK_STREAM, 0);
    
    // Enlace con el socket
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);
    
    bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Escuchar a los clientes
    listen(servidor, 10);
    
    // Comunicación
    socklen_t tamano = sizeof(direccion);
    
    cliente = accept(servidor, (struct sockaddr *) &direccion, &tamano);
    
    if (cliente >= 0) {
        printf("Aceptando conexiones en %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        
        // Leer de socket y escribir en pantalla
        while (leidos = read(cliente, &buffer, sizeof(buffer))) {
            write(fileno(stdout), &buffer, leidos);
            numero1 = atoi(buffer);
            char * inicio = buffer;
            char * final = (inicio+1000);
            int factorial = 1, c = 0;
            for (; inicio<final; ++inicio)
                factorial = factorial * c;
            sprintf(buffer, "%s%d%s", "La temperatura es: ", numero1, "\n");
            //strcpy(buffer, &"El numero es: "[numero1]);
            int bytes = strlen(buffer);
            //leidos = read(fileno(stdin), &buffer, sizeof(buffer));
            write(cliente, &buffer, bytes);
        }
        
        
    }
    
    // Cerrar el socket
    
    close(servidor);
    close(cliente);
    
    return 0;
}
