#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>
#include <unistd.h> // for close
#include "segment.h"

#define PORT 8892

void update(SEG_DATA *mydata, SEG_DATA *shm, int up);

int main(int argc, char const *argv[])
{       
	int up = 0, shmid, c;
	key_t mykey;
	void* shmat(int shmid, const void *addr, int flag);
	int shmdt(const void *shmaddr);
	SEG_DATA *shm, *mydata;
        struct sockaddr_in server, client;
    	int socket_desc, new_socket, select_no;
    	char *sendBuff = malloc(sizeof(100));;
    	char *clientReq = malloc(sizeof(100));;
        //char *message = malloc(sizeof(100));
     

        //fprintf(stdout, "Task completed\n");
	/*
	 * The shared memory segment is identified by SEGMENTID
	 */
	mykey = SEGMENTID;

        struct timeval tv;
        fd_set readfds;
        //FD_ZERO(&readfds);
        

        /* Wait up to ten seconds. */
        tv.tv_sec = 10;
        tv.tv_usec = 0;
	/*
	 * here we create the shared memory segment using the `shmget' system call.
         * - for debugging remove the IPC_EXCL flag - `IPC_CREAT | IPC_EXCL | 0666'
	 */

	if( (shmid = shmget( mykey, sizeof(SEG_DATA), IPC_CREAT | 0666)) < 0 )
	{
		perror("shmget: cannot create shared memory segment; exiting now");
		exit(1);
	}

	/*
	 * We must now map the segment into our process address space using the
	 * `shmat' [attach] system call.
	 */

	if( (shm = (SEG_DATA *)shmat( shmid, NULL, 0)) == ((SEG_DATA *)-1) )
	{
		perror("shmat: cannot attach shared memory segment; exiting now");
		exit(1);
	}

	/*
	 * Test Code - write into segment
	 */

	mydata = (SEG_DATA *)shm;

	/*
	 * Initialise values in segment
	 */
	mydata->exit = 0;
	mydata->rpm = 3500;
	mydata->crankangle = 0;
	mydata->throttle = 70;
	mydata->fuelflow = 50;
	mydata->temp = 80;
	mydata->fanspeed = 30;
	mydata->oilpres = 70;

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    	if (socket_desc == -1)
        {	
        	printf("Could not create socket");
    	}

    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = INADDR_ANY;
    	server.sin_port = htons(PORT); 

    	fprintf(stdout, "ABCD\n");
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
        /*if(new_socket > socket_desc) 
	    new_socket = socket_desc;*/

        /**while(1){
           int a = recv(new_socket, clientReq, 100, 0);
	   clientReq[a] = '\0';
           printf("Incoming Client Message: %s\n", clientReq);
	} **/    
    	while (1)
    	{   
        	//fprintf(stdout, "While loop\n");
        	
                FD_ZERO(&readfds); /* clear the set */
    		FD_SET(new_socket, &readfds); /* add our file descriptor to the set */
		FD_SET(STDIN_FILENO, &readfds);

        	select_no = select(new_socket+1, &readfds, NULL, NULL, &tv);
        	fprintf(stdout, "\nselect: %d\n", select_no);
                bool x = FD_ISSET(new_socket, &readfds);
                fprintf(stdout, "\n%s\n", x ? "true" : "false");
                
                
                if(select_no > 0 && FD_ISSET(new_socket, &readfds)){
                	//FD_SET(new_socket, &readfds);
                        FD_CLR(new_socket, &readfds);
                        fprintf(stdout, "While meyeyevebd\n");
           		//new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
           		int a = recv(new_socket, clientReq, 100, 0);
	                clientReq[a] = '\0';
           		printf("ABCD%s\n", clientReq);
                        
                        if(strcmp(clientReq, "0") == 0)
           		{
                             //printf("ABCD%d\n", strcmp(clientReq, "0"));
               		     sendBuff[0] = mydata->rpm;
               		     sendBuff[1] = mydata->crankangle;
		       	     sendBuff[2] = mydata->throttle;
		       	     sendBuff[3] = mydata->fuelflow;
		       	     sendBuff[4] = mydata->temp;
		       	     sendBuff[5] = mydata->fanspeed;
		       	     sendBuff[6] = mydata->oilpres;
                             //printf("ABCD!\n Client has exited.");
		       	     send(new_socket , sendBuff , strlen(sendBuff) , 0);
                             //printf("ABCD!\n Client has exited.");
           	         }

		   	else if(strcmp(clientReq, "1") == 0)
		   	{
			     mydata->exit = 1;
			     printf("\n Client has exited.");
			     free(clientReq);
			     free(sendBuff);
			     close(socket_desc);
			     exit(0);
		   	}
                }
                if(FD_ISSET(STDIN_FILENO, &readfds))
            	     printf("abcds");
           	update(mydata, shm, up);
                //FD_CLR(socket_desc, &readfds);
        }
     
   /*
    * We must now unmap the segment into our process address space using the
    * `shmdt' [detach] system call.
   */

    if( (shmid = shmdt( shm )) == (-1) )
	{
		perror("shmdt: cannot detach shared memory segment; exiting now");
		exit(1);
	}
    return 0;
}

void update(SEG_DATA *mydata, SEG_DATA *shm, int up)
{
	if( mydata->exit != 1 ){
		if ( up == 1 && mydata->rpm > 6500 ) up = 0; /* cycle values */
		if ( up == 0 && mydata->rpm < 500 ) up = 1;  
		if ( up == 1 ){
		mydata->rpm += 100;
		mydata->crankangle += 1;
		mydata->crankangle %= 360;
		mydata->throttle += 1;
		mydata->throttle %= 100;
		mydata->fuelflow += 1;
		mydata->fuelflow %= 100;
		mydata->temp += 1;
		mydata->temp %= 100;
		mydata->fanspeed += 1;
		mydata->fanspeed %= 100;
		mydata->oilpres += 1;
		mydata->oilpres %= 100;
		} else {
		mydata->rpm -= 100;
		mydata->crankangle -= 1;
		mydata->crankangle %= 360;
		mydata->throttle -= 1;
		mydata->throttle %= 100;
		mydata->fuelflow -= 1;
		mydata->fuelflow %= 100;
		mydata->temp -= 1;
		mydata->temp %= 100;
		mydata->fanspeed -= 1;
		mydata->fanspeed %= 100;
		mydata->oilpres -= 1;
		mydata->oilpres %= 100;
		}
		sleep(1);
		fprintf(stdout, "\nSTATUS DUMP\n");
		fprintf(stdout, "UP Status        = %d\n", up );
		fprintf(stdout, "Exit Status      = %d\n", mydata->exit );
		fprintf(stdout, "RPM              = %d\n", mydata->rpm );
		fprintf(stdout, "Crank Angle      = %d\n", mydata->crankangle );
		fprintf(stdout, "Throttle Setting = %d\n", mydata->throttle );
		fprintf(stdout, "Fuel Flow        = %d\n", mydata->fuelflow );
		fprintf(stdout, "Engine Temp      = %d\n", mydata->temp );
		fprintf(stdout, "Fan Speed        = %d\n", mydata->fanspeed );
		fprintf(stdout, "Oil Pressure     = %d\n", mydata->oilpres );
		fprintf(stdout, "Waiting for client\n");
	}

	return;

}


