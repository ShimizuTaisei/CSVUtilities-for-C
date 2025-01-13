CC = gcc
CFLAGS = -g -Wall -Wextra -I. -ISample
LIB = libcsv.a

all: score

csv_reader.o: ../csv_reader.c
	$(CC) $(CFLAGS) -c ../csv_reader.c

csv_list.o: ../csv_list.c
	$(CC) $(CFLAGS) -c ../csv_list.c

csv_writer.o: ../csv_writer.c
	$(CC) $(CFLAGS) -c ../csv_writer.c

$(LIB): csv_reader.o csv_list.o csv_writer.o
	ar rcs $(LIB) csv_reader.o csv_list.o csv_writer.o

score: score.c $(LIB)
	$(CC) $(CFLAGS) -o score student.c score.c -L. -lcsv


clean:
	rm -f *.o $(LIB) score