# Flags that are sent to the compiler
CFLAGS      = -Wall -std=c99 -pedantic -g

library:
	gcc $(CFLAGS) -c listio.c -o listio.o
	ar cr liblistio.a listio.o
