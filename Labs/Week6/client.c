#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>
#include <unistd.h> // for close

#define PORT 8888

int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char *message = malloc(sizeof(100)); 
    char server_reply[2000];
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
         
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
 
    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
     
    puts("Connected\n");
     
    //Send some data
    
    while (1){
       printf("Message: ");
       fgets(message, 100, stdin);
       size_t len = strlen(message);
       if (len > 0 && message[len-1] == '\n') {
           message[--len] = '\0';
       }

       //printf("%s\n", message);
       //printf("strcmp value: %d\n", strcmp(message, "Q"));
       // Client exits
       if (strcmp(message, "Q") == 0){
            printf("Client exiting successful.\n");
            send(socket_desc , message , strlen(message) , 0);
            close(socket_desc);
            free(message);
            exit(0);
            return 0;
       }
       // Send data to server. It fails if send returns < 0
       else if( send(socket_desc , message , strlen(message) , 0) < 0)
       {
           puts("Send failed");
           free(message);
           close(socket_desc);
           return 1;
       }
       puts("Data sent to Server for displaying.\n");
    }
    //Receive a reply from the server
    if( recv(socket_desc, server_reply , 2000 , 0) < 0)
    {
        puts("recv failed");
    }
    puts("Reply received\n");
    puts(server_reply);
    free(message);
    close(socket_desc);
    return 0;
}

