#
# Makefile for Prac 2
# (c) 2004, Carlo Kopp, Monash University, SCSSE
#
# $Id: Makefile,v 1.6 2004/03/21 17:45:56 carlo Exp $
#

CC = gcc
AS = as
LD = $(CC)

# 
CFLAGS = -g 
# -Wall
LDFLAGS = -g -lm
INCLUDES = .

#rules
.c.s:
	$(CC) -c $(CFLAGS) -I $(INCLUDES) $<

.c.o:
	$(CC) -c $(CFLAGS) -I $(INCLUDES) $<


#
# Student files
#
MYSERVER = status-server
MYCLIENT = 26356104-client
MYCOBJS = 26356104-shm-client.o
MYSOBJS = status-shm-server.o
MYSRC = 26356104-shm-client.c       status-shm-server.c
#
# Test files
#
SERVER = shm-server
CLIENT = shm-client
COBJS = shm-client-test.o
SOBJS = shm-server-test.o
SRC = shm-client-test.c shm-server-test.c

all: $(MYSOBJS) $(MYCOBJS)
	$(LD) $(LDFLAGS) -o $(MYSERVER) $(MYSOBJS)
	$(LD) $(LDFLAGS) -o $(MYCLIENT) $(MYCOBJS)

test: $(SOBJS) $(COBJS)
	$(LD) $(LDFLAGS) -o $(SERVER) $(SOBJS)
	$(LD) $(LDFLAGS) -o $(CLIENT) $(COBJS)

client: $(COBJS)
	$(LD) $(LDFLAGS) -o $(CLIENT) $(COBJS)

server: $(SOBJS)
	$(LD) $(LDFLAGS) -o $(SERVER) $(SOBJS)

myserver: $(MYSOBJS)
	$(LD) $(LDFLAGS) -o $(MYSERVER) $(MYSOBJS)

MyID-shm-client.o:  26356104-shm-client.c       
status-shm-server.o:	status-shm-server.c

shm-client-test.o:	shm-client-test.c
shm-server-test.o:	shm-server-test.c


checkin:
	echo "check in files ..."
	ci -l  \
	$(SRC) $(MYSRC) $(INCS) Makefile

clean:
	echo "cleaning up ..."
	rm -f *core
	rm -f $(SERVER) $(SOBJS) $(CLIENT) $(COBJS)
	rm -f $(MYSERVER) $(MYSOBJS) $(MYCLIENT) $(MYCOBJS)
