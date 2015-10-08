//
//  main.c
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
#define MAX_TEXT 512

/*define a message structure*/
struct my_msg{
    long msgtype;
    char message[MAX_TEXT];
};

int main(int argc, const char * argv[]) {
    
    /*key to be passed to msgget()*/
    key_t key;
    /*msgflg to be passed to msgget()*/
    int msgflg;
    /*return value from msgget()*/
    int msgid;
    /*declare an instance of structure of msg*/
    struct my_msg sometext;
    /* declare a buffer for text msg*/
    char buffer[BUFSIZ];
    /*initialize the key*/
    key = 1234;
    /* read and write permission for owner,
     and create a message queue if not exists*/
    msgflg = 0666 | IPC_CREAT;
    
    /*creat a message queue */
    if((msgid = msgget(key, msgflg))== 1){
        perror("msgget: msgget failed");
        exit(1);
    }
    printf("msgget succeeded\n");
    while(1){
        /*read user input from the keyboard */
        printf("Please ener some text:\n");
        //fgets(buffer, BUFSIZ, stdin);
        scanf(" %[^\n]s", buffer);
        printf("Introdujiste: %s\n", buffer);
        /*set the msgtype */
        sometext.msgtype = 1;
        /*copy from buffer to message*/
        strcpy(sometext.message, buffer);
        /*send the message */
        if (msgsnd(msgid, &sometext, MAX_TEXT, 0) == -1){
            perror("msgsnd: msgsnd failed\n");
            exit(1);
        }
        if(strncmp(buffer, "end", 3)== 0){
            printf("message ends.\n");
            exit(0);
        }
    }
    
    return 0;
}
    
    
    
    
    
    
