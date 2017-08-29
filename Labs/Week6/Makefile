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
MYSRC = client.c server.c

all: 
	gcc -Wall client.c -o client
	gcc -Wall server.c -o server

clean:  
	echo "cleaning up ..."
	rm -f *core
	rm -f $(MYSERVER) $(MYSOBJS) $(MYCLIENT) $(MYCOBJS)

