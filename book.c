#include "book.h"
#include <stdlib.h> 
#include <string.h> 
#include <stddef.h> 
#include <stdio.h>

/**
 * add_book - Adds a new book to the linked list
 * @head: Double pointer to the head of the list
 * @title: Title of the book
 * @author: Author of the book
 * @isbn: ISBN of the book
 * @total_copies: Total copies of the book
 * @available_copies: Available copies
 *
 * Return: 1 if successful, 0 if failed
 */
int add_book(Book **head, const char *title, const char *author, const char *isbn,
             int total_copies, int available_copies)
{
    Book *new_book = malloc(sizeof(Book));
    if (new_book == NULL)
        return 0;

    strncpy(new_book->title, title, sizeof(new_book->title) - 1);
    new_book->title[sizeof(new_book->title) - 1] = '\0';

    strncpy(new_book->author, author, sizeof(new_book->author) - 1);
    new_book->author[sizeof(new_book->author) - 1] = '\0';

    strncpy(new_book->isbn, isbn, sizeof(new_book->isbn) - 1);
    new_book->isbn[sizeof(new_book->isbn) - 1] = '\0';

    new_book->total_copies = total_copies;
    new_book->available_copies = available_copies;
    new_book->next = *head;
    *head = new_book;

    return 1;
}

/**
 * display_book - Displays the details of a single book
 * @book: Pointer to the book to display
 */
void display_book(const Book *book)
{
    if (book == NULL)
        return;

    printf("\nTitle: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("ISBN: %s\n", book->isbn);
    printf("Total Copies: %d\n", book->total_copies);
    printf("Available Copies: %d\n", book->available_copies);
}

/**
 * display_all_books - Displays all books in the linked list
 * @head: Pointer to the head of the list
 */
void display_all_books(const Book *head)
{
    if (head == NULL)
    {
        printf("No books available in the library.\n");
        return;
    }

    const Book *current = head;
    while (current != NULL)
    {
        display_book(current);
        current = current->next;
    }
}

/**
 * free_books - Frees the memory allocated for the book list
 * @head: Pointer to the head of the list
 */
void free_books(Book *head)
{
    Book *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
