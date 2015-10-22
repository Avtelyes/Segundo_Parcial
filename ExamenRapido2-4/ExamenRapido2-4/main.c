//
//  main.c
//  ExamenRapido2-4
//
//  Created by Josué Carlos García Puig on 22/10/15.
//  Copyright © 2015 Josue Garcia. All rights reserved.
//

//
//  main.c
//  ExPthreads5
//
//  Created by Josué Carlos García Puig on 22/10/15.
//  Copyright © 2015 Josue Garcia. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define FUMADORES 3
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_tabaco = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_papel = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_cerillo = PTHREAD_MUTEX_INITIALIZER;



typedef struct{
    int tabaco;
    int papel;
    int cerillo;
} Materiales;

void tomar_ingrediente(int i, Materiales *);
void comer(int i);
void * fumador(void *arg);

int ingredientes[2];

int main(){
    
    srand((int)time(NULL));
    pthread_t * fum = (pthread_t*)malloc(FUMADORES*sizeof(pthread_t));
    //pthread_t * productor = (pthread_t *) malloc(sizeof(pthread_t));
    int i;
    
    for (i =0; i<FUMADORES;++i){
        pthread_create((fum+i),NULL,fumador,i);
    }
    
    for (i=0;i<FUMADORES;++i){
        pthread_join(*(fum+i),NULL);
    }
    
    //Garantizar que se liberen los recursos de los hilos
    pthread_exit(NULL);
    
    return 0;
    
}

void fumar(int i)
{
    int r = rand() %  15;
    printf("Soy %d y Estoy fumando!\n",i);
    sleep(r);
}

void tomar_ingrediente(int i, Materiales * mat)
{
    if(mat->cerillo==0)
    {
        if(ingredientes[0] == 2 || ingredientes[1] == 2 )
        {
            pthread_mutex_trylock(&m_cerillo);
            mat->cerillo = 1;
            pthread_mutex_unlock(&m_cerillo);
        }
        
    }
    else if (mat->tabaco==0)
    {
        if(ingredientes[0] == 0 || ingredientes[1] == 0 )
        {
            pthread_mutex_trylock(&m_tabaco);
            mat->tabaco = 1;
            pthread_mutex_unlock(&m_tabaco);
        }
        
    }
    else if (mat->papel==0)
    {
        if(ingredientes[0] == 1 || ingredientes[1] == 1 )
        {
            pthread_mutex_trylock(&m_papel);
            mat->papel = 1;
            pthread_mutex_unlock(&m_papel);
        }
    }
    else
    {
        fumar(i);
        mat->cerillo=0;
        mat->papel=0;
        mat->tabaco=0;
    }
}

void deja_ingredientes()
{
    int num = rand() % 3;
    int num2 = rand() % 3;
    
    ingredientes[0] = num;
    ingredientes[1] = num2;
}

void * fumador(void *arg){
    int i = (int)arg;
    printf("Soy el fumador %d\n",i);
    Materiales * material = malloc(sizeof(Materiales));
    material->cerillo = 0;
    material->papel = 0;
    material->tabaco = 0;
    while (1){
        deja_ingredientes();
        tomar_ingrediente(i,material);
    }
    //pthread_exit(NULL);
}





