#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>

#define PORT 8888

int main(int argc , char *argv[])
{
    int socket_desc , new_socket , c, n;
    struct sockaddr_in server , client;
    char *message = malloc(sizeof(100));
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);

    if (new_socket >= 0)
        puts("Connection accepted");

    else if (new_socket<0)
    {
        perror("accept failed");
        return 1;
    }
    while(1)
    {
        n=recv(new_socket, message, 100, 0);
        //Reply to the client
        
        message[n] = '\0';
        if (strcmp(message, "Q") == 0){
             printf("Client has exited\n\n");
             free(message);
             exit(0);
        }
        printf("Incoming Client Message: %s\n", message);
    }
     
    
    free(message);
    return 0;
}

