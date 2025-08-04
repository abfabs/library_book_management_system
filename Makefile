CC = gcc
CFLAGS = -Wall -Werror -Wextra
OBJ = main.o book.o
EXEC = library

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

main.o: main.c book.h
	$(CC) $(CFLAGS) -c main.c

book.o: book.c book.h
	$(CC) $(CFLAGS) -c book.c

clean:
	rm -f $(OBJ) $(EXEC)
