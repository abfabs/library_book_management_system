CC = gcc
CFLAGS = -Wall -Werror -Wextra
OBJ = main.o book.o file_ops.o   # add file_ops.o here
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

clean:
	rm -f $(OBJ) $(EXEC)
