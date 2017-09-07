CC = gcc
AS = as
LD = $(CC)

# 
CFLAGS = -g 
# -Wall
LDFLAGS = -g -lm
INCLUDES = .

MYSERVER = server
MYCLIENT = client
MYCOBJS = client.o
MYSOBJS = server.o
MYSRC = 26.c server.c

all: 
	gcc -Wall 26356104-socket-client.c -o client
	gcc -Wall 26356104-status-socket-server.c -o server

clean:  
	echo "cleaning up ..."
	rm -f *core
	rm -f $(MYSERVER) $(MYSOBJS) $(MYCLIENT) $(MYCOBJS)
