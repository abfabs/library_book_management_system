#include "book.h"

/**
 * add_book - adds a new book node at the start of the linked list
 * @head: pointer to the head pointer of the list
 * @title: book title string
 * @author: book author string
 * @isbn: book ISBN string
 * @available: availability status (1 for available, 0 for borrowed)
 *
 * Return: 1 on success, 0 on failure (malloc failure)
 */
int add_book(Book **head, char *title, char *author, char *isbn, int available)
{
    Book *new_book = malloc(sizeof(Book));

    if (!new_book)
        return 0;

    strcpy(new_book->title, title);
    strcpy(new_book->author, author);
    strcpy(new_book->isbn, isbn);
    new_book->available = available;
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
    Book *current = head;

    if (!current)
    {
        printf("No books available.\n");
        return;
    }

    while (current)
    {
        printf("Title: %s\n", current->title);
        printf("Author: %s\n", current->author);
        printf("ISBN: %s\n", current->isbn);
        printf("Status: %s\n\n", current->available ? "Available" : "Borrowed");
        current = current->next;
    }
}

/**
 * load_books - loads book data from a file into a linked list
 * @filename: name of the file to read from
 * @head: pointer to the head pointer of the list
 *
 * Return: 0 on success, 1 on failure (file open or malloc failure)
 */
int load_books(const char *filename, Book **head)
{
    FILE *file = fopen(filename, "r");
    char line[256], title[100], author[100], isbn[20];
    int available;

    if (file == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%d", title, author, isbn, &available) == 4)
        {
            if (!add_book(head, title, author, isbn, available))
            {
                printf("Failed to add book: %s\n", title);
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
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
