OBJS	= Bruteforce.c
OUT	= Bruteforce

OBJS0	= Bruteforce.o
SOURCE0	= Bruteforce.c
HEADER0	= 
OUT0	= Bruteforce

CC	 = gcc
FLAGS	 = -g -c -Wall -lcrypt
LFLAGS	 = 

all: Bruteforce

Server: $(OBJS0) $(LFLAGS)
	$(CC) -g $(OBJS0) -o $(OUT0)

Server.o: Server.c
	$(CC) $(FLAGS) Server.c 

clean:
	rm -f $(OBJS) $(OUT)