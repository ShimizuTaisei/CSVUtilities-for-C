CC = gcc
CFLAGS = -Wall -Wextra -I.
LIB = libcsv.a

all: test

csv.o: csv.c
	$(CC) $(CFLAGS) -c csv.c

$(LIB): csv.o
	ar rcs $(LIB) csv.o

test: test.c $(LIB)
	$(CC) $(CFLAGS) -o test test.c -L. -lcsv

clean:
	rm -f *.o $(LIB) test