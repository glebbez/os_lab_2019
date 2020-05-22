CC=gcc
CFLAGS=-I.

parallel_min_max : utils.o find_min_max.o utils.h find_min_max.h parallel_min_max.c
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.c -std=c99 $(CFLAGS)

utils.o : utils.h utils.c
	$(CC) -o utils.o -c utils.c -std=c99 $(CFLAGS)

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c -std=c99 $(CFLAGS)

clean :
	rm utils.o find_min_max.o parallel_min_max psum zombie_creater proc_mem

all : parallel_min_max psum zombie_creater proc_mem
    
reset : clean all
    
zombie : zombie_creater.c
	$(CC) -o zombie_creater zombie_creater.c -std=c99 $(CFLAGS)

proc_mem : process_memory.c
	$(CC) -o proc_mem process_memory.c -std-c99 $(CFLAGS)
	
psum : parallel_sum.c utils.o
	$(CC) -o psum utils.o parallel_sum.c -std=c99 -g -lpthread $(CFLAGS)