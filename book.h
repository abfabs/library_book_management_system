#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct Book - Struct representing a book in the library
 * @title: Title of the book
 * @author: Author of the book
 * @isbn: ISBN number
 * @total_copies: Total number of copies the library owns
 * @available_copies: Number of copies currently available
 * @next: Pointer to the next book in the list
 */
typedef struct Book
{
    char title[100];
    char author[100];
    char isbn[20];
    int total_copies;
    int available_copies;
    struct Book *next;
} Book;

/* Function prototypes */
int add_book(Book **head, char *title, char *author, char *isbn, int total_copies, int available_copies);
void display_books(Book *head);
int load_books(const char *filename, Book **head);
void free_books(Book *head);
int add_book_from_input(Book **head);

#endif /* BOOK_H */
