/*
 * Shared Memory Server Process as per D.A. Curry `Using C on the Unix System'
 * shm-server-test.c
 * Author: C. Kopp
 * (c) 2004, Monash University, SCCSE
 *
 * $Id: shm-server-test.c,v 1.2 2015/08/17 06:53:03 carlo Exp carlo $
 *
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include "segment.h"


int main()
{

	char 
		mychar;
	int 
		shmid;
	key_t 
		mykey;
	void *
    	shmat(int shmid, const void *addr, int flag);
	int 
		shmdt(const void *shmaddr);
	char 
		*shm, *myshm;


	/*
	 * The shared memory segment is identified by SEGMENTID
	 */
	mykey = SEGMENTID;


	/*
	 * here we create the shared memory segment using the `shmget' system call.
     * - for debugging remove the IPC_EXCL flag - `IPC_CREAT | IPC_EXCL | 0666'
	 */

	if( (shmid = shmget( mykey, SHMSZ, IPC_CREAT | 0666)) < 0 )
		{
		perror("shmget: cannot create shared memory segment; exiting now");
		exit(1);
		}

	/*
	 * We must now map the segment into our process address space using the
	 * `shmat' [attach] system call.
	 */

	if( (shm = shmat( shmid, NULL, 0)) == ((char *)-1) )
		{
		perror("shmat: cannot attach shared memory segment; exiting now");
		exit(1);
		}

	/*
	 * Test Code - write into segment
	 */

	myshm = shm;

	for (mychar = 'a'; mychar <= 'z'; mychar++)
		*myshm++ = mychar;
		*myshm = NULL;

	/*
	 * Wait until the client process changes the first character to '*'
	 * and then exit.
	 */
	fprintf(stdout, "Waiting for client\n");

	while ( *shm != '*' )
		sleep(1);

	/*
	 * We must now unmap the segment into our process address space using the
	 * `shmdt' [detach] system call.
	 */

	if( (shmid = shmdt( shm )) == (-1) )
		{
		perror("shmdt: cannot detach shared memory segment; exiting now");
		exit(1);
		}

	fprintf(stdout, "Task completed\n");
	exit(0);
	
}
