# Flags that are sent to the compiler
CFLAGS = -Wall -std=c99 -pedantic -g

a3: a3.c listio.c listio.h
	gcc $(CFLAGS) -c listio.c
	ar cr liblistio.a listio.o
	gcc a3.c liblistio.a -o a3
	
library: listio.c listio.h
	gcc $(CFLAGS) -c listio.c -o listio.o
	ar cr liblistio.a listio.o

#just makes listio.o
listio.o: listio.c listio.h
	gcc -c listio.c
	
#just makes liblistio.a
liblistio.a: listio.o
	ar cr liblistio.a listio.o

clobber:
	rm *.o a3 liblistio.a