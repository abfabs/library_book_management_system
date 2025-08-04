#include "book.h"
#include <stdio.h>

/**
 * main - Entry point for the Library Book Management System
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    Book *library = NULL;
    int choice;
    int result;

    printf("Loading books from file...\n");
    result = load_books("books.txt", &library);
    if (result != 0)
    {
        printf("Error: Failed to load books from file.\n");
        return 1;
    }

    while (1)
    {
        printf("\nLibrary Menu:\n");
        printf("1. Display All Books\n");
        printf("2. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
        {
            printf("Invalid choice. Please enter 1 or 2.\n");
            while (getchar() != '\n')  // clear input buffer
                ;
            continue;
        }

        switch (choice)
        {
            case 1:
                display_books(library);
                break;
            case 2:
                printf("Exiting program.\n");
                free_books(library);
                return 0;
        }
    }

    return 0;
}
