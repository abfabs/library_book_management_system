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

/* Core library functions */
int add_book(Book **head, char *title, char *author, char *isbn, int total_copies, int available_copies);
void display_book(const Book *book);
void display_all_books(const Book *head);
int load_books(const char *filename, Book **head);
int save_books(const char *filename, const Book *head);
void free_books(Book *head);
int add_book_from_input(Book **head);

/* Utility functions */
Book *search_book_by_title(Book *head, const char *title);
Book *search_book_by_isbn(Book *head, const char *isbn);
int update_availability(Book *head, const char *isbn, int borrow);

#endif /* BOOK_H */
