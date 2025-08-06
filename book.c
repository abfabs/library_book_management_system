#include "book.h"

/**
 * add_book - Adds a new book node at the start of the linked list
 * @head: Pointer to the head pointer of the list
 * @title: Book title string
 * @author: Book author string
 * @isbn: Book ISBN string
 * @total_copies: Total number of copies available in the library
 * @available_copies: Number of currently available (not borrowed) copies
 *
 * Return: 1 on success, 0 on failure (malloc failure)
 */
int add_book(Book **head, char *title, char *author, char *isbn,
             int total_copies, int available_copies)
{
    Book *new_book = malloc(sizeof(Book));
    if (new_book == NULL)
        return (0);

    strcpy(new_book->title, title);
    strcpy(new_book->author, author);
    strcpy(new_book->isbn, isbn);
    new_book->total_copies = total_copies;
    new_book->available_copies = available_copies;
    new_book->next = *head;
    *head = new_book;

    return (1);
}

/**
 * display_books - Prints all books from the linked list
 * @head: Pointer to the head of the list
 */
void display_books(Book *head)
{
    Book *ptr = head;

    if (ptr == NULL)
    {
        printf("No books available.\n");
        return;
    }

    while (ptr != NULL)
    {
        printf("Title: %s\n", ptr->title);
        printf("Author: %s\n", ptr->author);
        printf("ISBN: %s\n", ptr->isbn);
        printf("Total Copies: %d\n", ptr->total_copies);
        printf("Available Copies: %d\n", ptr->available_copies);
        printf("Status: %s\n\n",
               ptr->available_copies > 0 ? "Available" : "All Copies Borrowed");
        ptr = ptr->next;
    }
}

/**
 * free_books - Frees all nodes in the linked list to avoid memory leaks
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
