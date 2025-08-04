#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book 
{
    char title[100];
    char author[100];
    char isbn[20];
    int available; /* 1 = available, 0 = borrowed */
    struct Book *next;
} Book;

int add_book(Book **head, char *title, char *author, char *isbn, int available);
void display_books(Book *head);
int load_books(const char *filename, Book **head);
void free_books(Book *head);

#endif
