CC=gcc
CFLAGS=-g -Wall -Wstrict-prototypes -std=gnu99
LFLAGS=-lm -lpthread

all:	make-2d pth_mat_vect_rand_split_upgraded print-2d

make-2d:	utilities.o make-2d.o
	$(CC) $(LFLAGS) -o make-2d utilities.o make-2d.o

pth_mat_vect_rand_split_upgraded: pth_mat_vect_rand_split_upgraded.o
	$(CC) -o pth_mat_vect_rand_split_upgraded utilities.o pth_mat_vect_rand_split_upgraded.o $(LFLAGS)

print-2d: print-2d.o
	$(CC) -o print-2d utilities.o print-2d.o

pth_mat_vect_rand_split_upgraded.o: pth_mat_vect_rand_split_upgraded.c utilities.h
	$(CC) $(CFLAGS) -c pth_mat_vect_rand_split_upgraded.c

make-2d.o: make-2d.c utilities.h
	$(CC) $(CFLAGS) -c make-2d.c

utilities.o: utilities.c utilities.h
	$(CC) $(CFLAGS) -c utilities.c

print-2d.o: print-2d.c utilities.h
	$(CC) $(CFLAGS) -c print-2d.c

clean:
	rm -f *.o core* make-2d print-2d pth_mat_vect_rand_split_upgraded
