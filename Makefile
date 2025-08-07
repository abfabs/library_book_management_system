CC = gcc
CFLAGS = -Wall -Werror -Wextra
OBJ = main.o book.o file_ops.o utility.o
EXEC = library

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

main.o: main.c book.h
	$(CC) $(CFLAGS) -c main.c

book.o: book.c book.h
	$(CC) $(CFLAGS) -c book.c

file_ops.o: file_ops.c book.h
	$(CC) $(CFLAGS) -c file_ops.c

utility.o: utility.c book.h
	$(CC) $(CFLAGS) -c utility.c

clean:
	rm -f $(OBJ) $(EXEC)
