# Flags that are sent to the compiler
CFLAGS      = -Wall -std=c99 -pedantic -g

main:
	gcc $(CFLAGS) -c listio.c -o listio.o
	ar cr liblistio.a listio.o
	gcc -o main a2.c liblistio.a
	
library:
	gcc $(CFLAGS) -c listio.c -o listio.o
	ar cr liblistio.a listio.o