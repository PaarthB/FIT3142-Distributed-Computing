/*
 * Shared Memory Client Process as per D.A. Curry `Using C on the Unix System'
 * shm-clinet-test.c
 * Author: C. Kopp
 * (c) 2004, Monash University, SCCSE
 *
 * $Id: MyID-client-template.c,v 1.2 2015/08/17 06:53:03 carlo Exp carlo $
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
		c,
		*mychar = &c;
	int 
		myexit,
		shmid;
	key_t 
		mykey;
	void *
    	shmat(int shmid, const void *addr, int flag);
	int 
		shmdt(const void *shmaddr);
	SEG_DATA
		*shm, *mydata;


	/*
	 * The shared memory segment is identified by SEGMENTID
	 */
	mykey = SEGMENTID;

	/*
	 * here we create the shared memory segment using the `shmget' system call.
	 */


	/*
	 * We must now map the segment into our process address space using the
	 * `shmat' [attach] system call.
	 */


	/*
	 * Test Code - read from segment
	 */


	/*
	 * We must now unmap the segment into our process address space using the
	 * `shmdt' [detach] system call.
	 */


	fprintf(stdout, "Task completed\n");
	exit(0);
	
}
