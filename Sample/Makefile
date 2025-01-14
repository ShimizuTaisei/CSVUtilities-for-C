CC = gcc
CFLAGS = -g -Wall -Wextra -I. -ISample


all: score

csv_reader.o: ../csv_reader.c
	$(CC) $(CFLAGS) -c ../csv_reader.c

csv_list.o: ../csv_list.c
	$(CC) $(CFLAGS) -c ../csv_list.c

csv_writer.o: ../csv_writer.c
	$(CC) $(CFLAGS) -c ../csv_writer.c

libcsv.a: csv_reader.o csv_list.o csv_writer.o
	ar rcs libcsv.a csv_reader.o csv_list.o csv_writer.o

score: score.c read_write.c libcsv.a
	$(CC) $(CFLAGS) -o score student.c read_write.c score.c -L. -lcsv


clean:
	rm -f *.o libcsv.a score