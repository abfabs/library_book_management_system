#include "book.h"

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
int add_book(Book **head, char *title, char *author, char *isbn,
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

#include "book.h"
#include <stdio.h>
#include <string.h>

int add_book_from_input(Book **head)
{
    char title[100], author[100], isbn[20];
    int total_copies, available_copies;

    printf("Enter title: ");
    if (!fgets(title, sizeof(title), stdin))
        return 0;
    title[strcspn(title, "\n")] = '\0';

    printf("Enter author: ");
    if (!fgets(author, sizeof(author), stdin))
        return 0;
    author[strcspn(author, "\n")] = '\0';

    printf("Enter ISBN: ");
    if (!fgets(isbn, sizeof(isbn), stdin))
        return 0;
    isbn[strcspn(isbn, "\n")] = '\0';

    printf("Enter total copies: ");
    if (scanf("%d", &total_copies) != 1 || total_copies < 0)
    {
        while (getchar() != '\n'); // clear stdin
        printf("Invalid number.\n");
        return 0;
    }
    while (getchar() != '\n'); // clear stdin

    printf("Enter available copies: ");
    if (scanf("%d", &available_copies) != 1 || available_copies < 0 || available_copies > total_copies)
    {
        while (getchar() != '\n'); // clear stdin
        printf("Invalid number.\n");
        return 0;
    }
    while (getchar() != '\n'); // clear stdin

    return add_book(head, title, author, isbn, total_copies, available_copies);
}
/**
 * update_availability - Updates the available copies of a book by ISBN
 * @head: Pointer to the head of the book linked list
 * @isbn: ISBN string to find the book
 * @borrow: 1 to borrow (decrease available), 0 to return (increase available)
 *
 * Return: 1 if update successful, 0 if book not found or invalid operation
 */
int update_availability(Book *head, const char *isbn, int borrow)
{
    Book *current = head;

    while (current != NULL)
    {
        if (strcmp(current->isbn, isbn) == 0)
        {
            if (borrow)
            {
                if (current->available_copies > 0)
                {
                    current->available_copies--;
                    printf("Book borrowed successfully.\n");
                    return 1;
                }
                else
                {
                    printf("No copies available to borrow.\n");
                    return 0;
                }
            }
            else // Returning a book
            {
                if (current->available_copies < current->total_copies)
                {
                    current->available_copies++;
                    printf("Book returned successfully.\n");
                    return 1;
                }
                else
                {
                    printf("All copies are already returned.\n");
                    return 0;
                }
            }
        }
        current = current->next;
    }

    printf("Book with ISBN %s not found.\n", isbn);
    return 0;
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
