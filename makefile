
#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -std=c99 -g

#  Sources
SOURCES1 =  lab5a.c
SOURCES2 =  lab5b.c LinkedList.c

#  Objects
OBJECTS1 = lab5a.o
OBJECTS2 = lab5b.o LinkedList.o 

%.o: %.c

lab5a: $(OBJECTS1)
	$(CC) -g -o $@ $(OBJECTS1)

lab5a.o: lab5a.c
	$(CC) -g -c lab5a.c

lab5b: $(OBJECTS2)
	$(CC) -g -o $@ $(OBJECTS2)

lab5b.o: defs.h lab5b.c
	$(CC) -g -c lab5b.c

LinkedList.o: LinkedList.h LinkedList.c
	$(CC) -g -c LinkedList.c

clean::
	rm -f *.o core a.out lab5b lab5a *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
