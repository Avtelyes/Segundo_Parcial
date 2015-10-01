//
//  receiver.c
//  EjemploColas
//
//  Created by Josué Carlos García Puig on 01/10/15.
//  Copyright © 2015 Avtelyes. All rights reserved.
//

#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*define a message structure*/
struct my_msg{
    long msgtype;
    char message[BUFSIZ];
};

int main()
{
    /*key to be passed to msgget()*/
    key_t key;
    /*msgflg to be passed to msgget()*/
    int msgflg;
    /*return value from msgget()*/
    int msgid;
    /*declare an instance of structure of msg*/
    struct my_msg sometext;
    /*initialize the key*/
    key = 1234;
    /* read and write permission for owner,*/
    /*and create a message queue if not exists*/
    msgflg = 0666 | IPC_CREAT;
    
    /*initialize the priority of message*/
    long int msgpriori = 0;
    /*creat a message queue */
    if((msgid = msgget(key, msgflg))== 1){
        perror("msgget: msgget failed");
        exit(1);
    }
    printf("msgget succeeded\n");
    while(1){
        /*receive the message */
        if (msgrcv(msgid, &sometext, BUFSIZ, msgpriori, 0) == -1){
            perror("msgrcv: msgrcv failed\n");
            exit(1);
        }
        printf("You wrote: %s", sometext.message);
        if(strncmp(sometext.message,"end",3)==0){
            printf("message ends.\n");
            /*delete the message queue */
            if(msgctl(msgid, IPC_RMID, 0) == -1){
                perror("msgctl: msgctl failed");
                exit(1);
            }
            printf("program succeeded\n");
            exit(0);
        }
    }
}
