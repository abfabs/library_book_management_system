#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - Entry point for the Library Book Management System
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    Book *library = NULL;
    int result;
    int choice;
    char input[100];

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
        printf("1. Add a New Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by Title\n");
        printf("4. Search Book by ISBN\n");
        printf("5. Update Availability (Borrow/Return)\n");
        printf("6. Sort Books\n");
        printf("7. Save to File\n");
        printf("8. Load from File\n");
        printf("9. Exit\n");
        printf("Enter choice: ");

        if (!fgets(input, sizeof(input), stdin))
        {
            printf("Error reading input. Please try again.\n");
            continue;
        }

        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        // Validate input: must be integer between 1 and 9 only
        int valid = 1;
        for (size_t i = 0; input[i] != '\0'; i++)
        {
            if (input[i] < '0' || input[i] > '9')
            {
                valid = 0;
                break;
            }
        }

        if (!valid || sscanf(input, "%d", &choice) != 1 || choice < 1 || choice > 9)
        {
            printf("Invalid choice. Please enter a number between 1 and 9.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            if (!add_book_from_input(&library))
                printf("Failed to add new book.\n");
            break;

        case 2:
            display_all_books(library);
            break;

        case 3:
        {
            char title[100];
            printf("Enter title to search: ");
            if (!fgets(title, sizeof(title), stdin))
            {
                printf("Input error.\n");
                break;
            }
            title[strcspn(title, "\n")] = '\0';

            Book *found = search_book_by_title(library, title);
            if (found)
                display_book(found);
            else
                printf("Book not found.\n");
            break;
        }

        case 4:
        {
            char isbn[20];
            printf("Enter ISBN to search: ");
            if (!fgets(isbn, sizeof(isbn), stdin))
            {
                printf("Input error.\n");
                break;
            }
            isbn[strcspn(isbn, "\n")] = '\0';

            Book *found = search_book_by_isbn(library, isbn);
            if (found)
                display_book(found);
            else
                printf("Book not found.\n");
            break;
        }

        case 5:
        {
            char isbn[20];
            char action_input[10];
            int borrow = -1;

            printf("Enter ISBN: ");
            if (!fgets(isbn, sizeof(isbn), stdin))
            {
                printf("Input error.\n");
                break;
            }
            isbn[strcspn(isbn, "\n")] = '\0';

            printf("Enter 1 to borrow, 0 to return: ");
            if (!fgets(action_input, sizeof(action_input), stdin))
            {
                printf("Input error.\n");
                break;
            }
            action_input[strcspn(action_input, "\n")] = '\0';

            if (strcmp(action_input, "1") == 0)
                borrow = 1;
            else if (strcmp(action_input, "0") == 0)
                borrow = 0;
            else
            {
                printf("Invalid input for borrow/return.\n");
                break;
            }

            if (!update_availability(library, isbn, borrow))
                printf("Failed to update availability.\n");
            else
                printf("Availability updated successfully.\n");
            break;
        }

        case 6:
        {
            char sort_input[10];
            int sort_by = 0;

            printf("Sort by:\n");
            printf("1. Title\n");
            printf("2. Author\n");
            printf("Enter choice: ");

            if (!fgets(sort_input, sizeof(sort_input), stdin))
            {
                printf("Input error.\n");
                break;
            }

            sort_by = atoi(sort_input);
            if (sort_by != 1 && sort_by != 2)
            {
                printf("Invalid sorting option.\n");
                break;
            }

            sort_books(&library, sort_by);
            printf("Books sorted successfully.\n");
            break;
        }

        case 7:
            if (save_books("books.txt", library) == 0)
                printf("Books saved successfully.\n");
            else
                printf("Failed to save books.\n");
            break;

        case 8:
            free_books(library);
            library = NULL;
            if (load_books("books.txt", &library) == 0)
                printf("Books loaded successfully.\n");
            else
                printf("Failed to load books.\n");
            break;

        case 9:
            printf("Exiting program.\n");
            free_books(library);
            return 0;
        }
    }

    return 0;
}
