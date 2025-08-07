#include "book.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * to_lower - helper function to convert a string to lowercase
 * @src: original string
 * @dest: buffer to store lowercase string
 */
void to_lower(const char *src, char *dest)
{
    while (*src)
    {
        *dest = tolower((unsigned char)*src);
        src++;
        dest++;
    }
    *dest = '\0';
}

/**
 * search_book_by_title - search for first book matching title substring (case-insensitive)
 * @head: pointer to head of list
 * @title: substring to search for
 *
 * Return: pointer to first matching Book or NULL if none found
 */
Book *search_book_by_title(Book *head, const char *title)
{
    if (head == NULL)
        return NULL;

    char lower_search[100];
    to_lower(title, lower_search);

    Book *ptr = head;
    while (ptr)
    {
        char lower_title[100];
        to_lower(ptr->title, lower_title);
        if (strstr(lower_title, lower_search) != NULL)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

/**
 * search_book_by_isbn - search for book with exact ISBN match
 * @head: pointer to head of list
 * @isbn: ISBN string
 *
 * Return: pointer to matching Book or NULL if none found
 */
Book *search_book_by_isbn(Book *head, const char *isbn)
{
    if (head == NULL)
        return NULL;

    Book *ptr = head;
    while (ptr)
    {
        if (strcmp(ptr->isbn, isbn) == 0)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

/**
 * swap_books_data - helper function to swap book data between two nodes
 * @a: pointer to first book
 * @b: pointer to second book
 */
static void swap_books_data(Book *a, Book *b)
{
    char temp_title[100];
    char temp_author[100];
    char temp_isbn[20];
    int temp_total, temp_available;

    // Swap titles
    strcpy(temp_title, a->title);
    strcpy(a->title, b->title);
    strcpy(b->title, temp_title);

    // Swap authors
    strcpy(temp_author, a->author);
    strcpy(a->author, b->author);
    strcpy(b->author, temp_author);

    // Swap ISBNs
    strcpy(temp_isbn, a->isbn);
    strcpy(a->isbn, b->isbn);
    strcpy(b->isbn, temp_isbn);

    // Swap copies
    temp_total = a->total_copies;
    a->total_copies = b->total_copies;
    b->total_copies = temp_total;

    temp_available = a->available_copies;
    a->available_copies = b->available_copies;
    b->available_copies = temp_available;
}

/**
 * sort_books - sorts the linked list by title or author
 * @head: double pointer to head of the list
 * @sort_by: 1 for title, 2 for author
 */
void sort_books(Book **head, int sort_by)
{
    if (head == NULL || *head == NULL)
        return;

    int swapped;
    Book *ptr;
    Book *lptr = NULL;

    do
    {
        swapped = 0;
        ptr = *head;

        while (ptr->next != lptr)
        {
            int cmp = 0;
            if (sort_by == 1) // sort by title
                cmp = strcmp(ptr->title, ptr->next->title);
            else if (sort_by == 2) // sort by author
                cmp = strcmp(ptr->author, ptr->next->author);

            if (cmp > 0)
            {
                swap_books_data(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
}

/**
 * update_availability - update borrow/return status of a book by ISBN
 * @head: pointer to head of list
 * @isbn: ISBN string to find book
 * @borrow: 1 to borrow (decrement available), 0 to return (increment available)
 *
 * Return: 1 on success, 0 on failure (not found or invalid)
 */
int update_availability(Book *head, const char *isbn, int borrow)
{
    Book *book = search_book_by_isbn(head, isbn);
    if (book == NULL)
        return 0;

    if (borrow)
    {
        if (book->available_copies <= 0)
            return 0; // no copies available to borrow
        book->available_copies--;
    }
    else
    {
        if (book->available_copies >= book->total_copies)
            return 0; // all copies already returned
        book->available_copies++;
    }
    return 1;
}

/**
 * read_line - helper to safely read a line from stdin
 * @buffer: buffer to store input
 * @size: buffer size
 * Return: 1 on success, 0 on failure or EOF
 */
static int read_line(char *buffer, size_t size)
{
    if (fgets(buffer, size, stdin) == NULL)
        return 0;
    buffer[strcspn(buffer, "\n")] = '\0'; // remove newline
    return 1;
}

/**
 * add_book_from_input - prompts user for book info and adds the book
 * @head: pointer to the head pointer of the list
 * Return: 1 on success, 0 on failure
 */
int add_book_from_input(Book **head)
{
    char title[100], author[100], isbn[20];
    char total_str[20], available_str[20];
    int total_copies, available_copies;

    printf("Enter book title: ");
    if (!read_line(title, sizeof(title)))
        return 0;

    printf("Enter book author: ");
    if (!read_line(author, sizeof(author)))
        return 0;

    printf("Enter book ISBN: ");
    if (!read_line(isbn, sizeof(isbn)))
        return 0;

    printf("Enter total copies: ");
    if (!read_line(total_str, sizeof(total_str)))
        return 0;
    total_copies = atoi(total_str);
    if (total_copies <= 0)
    {
        printf("Invalid total copies number.\n");
        return 0;
    }

    printf("Enter available copies: ");
    if (!read_line(available_str, sizeof(available_str)))
        return 0;
    available_copies = atoi(available_str);
    if (available_copies < 0 || available_copies > total_copies)
    {
        printf("Invalid available copies number.\n");
        return 0;
    }

    if (!add_book(head, title, author, isbn, total_copies, available_copies))
    {
        printf("Failed to add book due to memory allocation error.\n");
        return 0;
    }

    printf("Book added successfully.\n");
    return 1;
}
