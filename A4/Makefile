# Flags that are sent to the compiler
CFLAGS = -Wall -std=c99 -pedantic -g

a4: a4.c listio.c listio.h db.c
	gcc $(CFLAGS) -c listio.c
	ar cr liblistio.a listio.o
	gcc a4.c liblistio.a -o a4 -lmysqlclient -L/usr/lib/x86_64-linux-gnu/
	gcc db.c -o db.o -c
	gcc db.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/
	
library: listio.c listio.h
	gcc $(CFLAGS) -c listio.c -o listio.o
	ar cr liblistio.a listio.o

#just makes listio.o
listio.o: listio.c listio.h
	gcc -c listio.c
	
#just makes liblistio.a
liblistio.a: listio.o
	ar cr liblistio.a listio.o

db: db.o
	gcc db.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/

db.o: db.c
	gcc db.c -o db.o -c 

clobber:
	rm *.o a4 liblistio.a db q2 q1
