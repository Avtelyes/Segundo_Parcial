//
//  main.c
//  ExamenRapido2-5
//
//  Created by Josué Carlos García Puig on 29/10/15.
//  Copyright © 2015 Josue Garcia. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define C 2
#define S 4
#define T 5
#define CLIENTES 10
#define ASIENTOS 15

pthread_mutex_t * asientos_t;
pthread_cond_t * sube_t;

int * salas;
int * asientos;

void * procesa_pedido(void *);

int main(int argc, const char * argv[]) {
    
    srand((int)time(NULL));
    
    pthread_t * clientes = (pthread_t *) malloc(sizeof(pthread_t) * CLIENTES);
    asientos_t = (pthread_mutex_t * ) malloc(sizeof(pthread_mutex_t) * S);
    asientos = (int *) malloc(sizeof(int) * S);
    
    int as = 0;
    
    for(; as<S; ++as)
    {
        *(asientos+as) = ASIENTOS;
    }
    
    pthread_t * aux;
    int indice = 0;
    
    for(aux = clientes; aux<(clientes+CLIENTES); ++aux)
    {
        pthread_create(aux, NULL, procesa_pedido, (void *) ++indice);
    }
    
    /* Adjuntar los hilos */
    for (aux = clientes; aux < (clientes+CLIENTES); ++aux) {
        pthread_join(*aux, NULL);
    }
    
    free(clientes);
    free(asientos_t);
    free(asientos);

    return 0;
}

void * procesa_pedido(void * arg)
{
    int id = (int) arg;
    
    int eleccion = rand() % 3;
    int complejo = rand() % C;
    int sala = rand() % S;
    int asiento = rand() % 15;
    
    if(eleccion == 0)
        printf("Soy el cliente %d y mi eleccion es el Sitio Web para el complejo %d\n",id,complejo);
    else if (eleccion == 1)
        printf("Soy el cliente %d y mi eleccion es la App para el complejo %d\n",id,complejo);
    else if (eleccion == 2)
        printf("Soy el cliente %d y mi eleccion es la Taquilla para el complejo %d\n",id,complejo);
    
    int reserva = 1;
    
    while (reserva)
    {
        pthread_mutex_lock((asientos_t+sala));
        int i = 0;
        for(; i<asiento;++i)
        {
            *(asientos+sala) = *(asientos+sala)-1;
            printf("Soy el cliente %d y ya reserve el asiento\n",id);
        }
        reserva = 0;
        pthread_mutex_unlock((asientos_t+sala));
    }
    
    pthread_exit(NULL);
}

