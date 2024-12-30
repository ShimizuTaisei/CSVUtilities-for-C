CC = gcc
CFLAGS = -g -Wall -Wextra -I.
LIB = libcsv.a

all: test

csv_reader.o: csv_reader.c
	$(CC) $(CFLAGS) -c csv_reader.c

csv_list.o: csv_list.c
	$(CC) $(CFLAGS) -c csv_list.c

$(LIB): csv_reader.o csv_list.o
	ar rcs $(LIB) csv_reader.o csv_list.o

test: test.c $(LIB)
	$(CC) $(CFLAGS) -o test test.c -L. -lcsv

clean:
	rm -f *.o $(LIB) test