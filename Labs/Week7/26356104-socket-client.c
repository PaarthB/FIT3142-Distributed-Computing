#define PORT 8892
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>
#include <sys/select.h>
#include "segment.h"
#include <unistd.h> // for close

int main(int argc, char const *argv[])
{
    int up = 0;
    //Create socket
    int socket_desc = 0;
    char *message = malloc(sizeof(100));
    struct sockaddr_in server;
    char *recvBuff = malloc(sizeof(500));
    //fd_set readfds;

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT); 
    
    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected\n");

    while (up != 1){
            fprintf(stdout, "Enter Command (1 to exit, 0 to get current values): ");
            fgets(message, 100, stdin);

            size_t len = strlen(message);
            if (len > 0 && message[len-1] == '\n') {
                message[--len] = '\0';
            }
            if( send(socket_desc , message , strlen(message) , 0) < 0)
       	    {
                puts("Send failed");
                free(message);
                close(socket_desc);
                return 1;
            }
            fprintf(stdout, "Message sent\n%s", message);

            
            //fprintf(stdout, "%s\n", message);
            
            if(strcmp(message, "0") == 0){
                int n = recv(socket_desc, recvBuff, 100, 0);
                //printf("Hey mate! %d\n", n);
                if (n > 0){
                fprintf(stdout, "\nRPM              = %d\n", recvBuff[0] );
                fprintf(stdout, "Crank Angle      = %d\n", recvBuff[1] );
	        fprintf(stdout, "Throttle Setting = %d\n", recvBuff[2] );
                fprintf(stdout, "Fuel Flow        = %d\n", recvBuff[3] );
	        fprintf(stdout, "Engine Temp      = %d\n", recvBuff[4] );
	        fprintf(stdout, "Fan Speed        = %d\n", recvBuff[5] );
	        fprintf(stdout, "Oil Pressure     = %d\n", recvBuff[6] );
                up = 0;  }
            }
            else { up = 1;}      
    }
    //Send some data
    fprintf(stdout, "Task completed\n");
    free(message);
    close(socket_desc);
    exit(0);

    return 0;

}



