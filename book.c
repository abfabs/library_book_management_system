#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * add_book - adds a new book node at the start of the linked list
 * @head: pointer to the head pointer of the list
 * @title: book title string
 * @author: book author string
 * @isbn: book ISBN string
 * @total_copies: total copies count
 * @available_copies: available copies count
 *
 * Return: 1 on success, 0 on failure (malloc failure)
 */
int add_book(Book **head, char *title, char *author, char *isbn,
             int total_copies, int available_copies)
{
    Book *new_book = malloc(sizeof(Book));
    if (!new_book)
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
 * display_books - prints all books from the linked list
 * @head: pointer to the head of the list
 */
void display_books(Book *head)
{
    if (head == NULL)
    {
        printf("No books available.\n");
        return;
    }

    Book *ptr = head;
    while (ptr)
    {
        printf("Title: %s\n", ptr->title);
        printf("Author: %s\n", ptr->author);
        printf("ISBN: %s\n", ptr->isbn);
        printf("Total Copies: %d\n", ptr->total_copies);
        printf("Available Copies: %d\n", ptr->available_copies);
        printf("Status: %s\n\n", ptr->available_copies > 0 ? "Available" : "All Copies Borrowed");
        ptr = ptr->next;
    }
}

/**
 * free_books - frees all nodes in the linked list to avoid memory leaks
 * @head: pointer to the head of the list
 */
void free_books(Book *head)
{
    Book *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
