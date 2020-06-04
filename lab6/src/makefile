CC=gcc
CFLAGS=-I -g -std=c99 

server: server.c MultMod.h
	$(CC) -o srv server.c -lpthread   $(CFLAGS)

client: client.c MultMod.h
	$(CC) client.c -o cln -lpthread $(CFLAGS)

clean:
	rm srv cln 
	


