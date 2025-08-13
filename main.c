#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function prototypes */
void print_menu(void);
int get_valid_choice(int min, int max);
void handle_add_book(Book **library);
void handle_display_books(Book *library);
void handle_search_title(Book *library);
void handle_search_isbn(Book *library);
void handle_update_availability(Book *library);
void handle_sort_books(Book **library);
void handle_save_books(Book *library);
void handle_load_books(Book **library);
void handle_exit(Book **library);

int main(void)
{
    Book *library = NULL;
    int result, choice;

    printf("Loading books from file...\n");
    result = load_books("books.txt", &library);
    if (result != 0)
    {
        printf("Error: Failed to load books from file.\n");
        return 1;
    }

    while (1)
    {
        print_menu();
        choice = get_valid_choice(1, 9);

        switch (choice)
        {
            case 1: handle_add_book(&library); break;
            case 2: handle_display_books(library); break;
            case 3: handle_search_title(library); break;
            case 4: handle_search_isbn(library); break;
            case 5: handle_update_availability(library); break;
            case 6: handle_sort_books(&library); break;
            case 7: handle_save_books(library); break;
            case 8: handle_load_books(&library); break;
            case 9: handle_exit(&library); return 0;
        }
    }

    return 0;
}

/* Prints the menu */
void print_menu(void)
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
    printf("Enter choice: \n");
}

/* Validates and returns a number input within [min, max] */
int get_valid_choice(int min, int max)
{
    char input[100];
    int choice;

    while (1)
    {
        if (!fgets(input, sizeof(input), stdin))
        {
            printf("Error reading input. Try again.\n");
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        int valid = 1;
        for (size_t i = 0; input[i] != '\0'; i++)
        {
            if (input[i] < '0' || input[i] > '9')
            {
                valid = 0;
                break;
            }
        }

        if (!valid || sscanf(input, "%d", &choice) != 1 || choice < min || choice > max)
        {
            printf("Invalid choice. Enter a number between %d and %d.\n", min, max);
            continue;
        }

        return choice;
    }
}

/* Menu option handlers */

void handle_add_book(Book **library)
{
    if (!add_book_from_input(library))
        printf("Failed to add new book.\n");
}

void handle_display_books(Book *library)
{
    display_all_books(library);
}

void handle_search_title(Book *library)
{
    char title[100];

    printf("Enter title to search: ");
    if (!fgets(title, sizeof(title), stdin))
    {
        printf("Input error.\n");
        return;
    }
    title[strcspn(title, "\n")] = '\0';

    search_book_by_title(library, title);
}

void handle_search_isbn(Book *library)
{
    char isbn[20];
    Book *found;

    printf("Enter ISBN to search: ");
    if (!fgets(isbn, sizeof(isbn), stdin))
    {
        printf("Input error.\n");
        return;
    }
    isbn[strcspn(isbn, "\n")] = '\0';

    found = search_book_by_isbn(library, isbn);
    if (found)
        display_book(found);
    else
        printf("Book not found.\n");
}

void handle_update_availability(Book *library)
{
    int search_field = 0;
    char search_str[100];
    char action_input[10];
    int borrow = -1;

    printf("Update availability by:\n");
    printf("1. ISBN\n2. Title\n3. Author\n");
    printf("Enter choice: ");
    if (!fgets(search_str, sizeof(search_str), stdin))
    {
        printf("Input error.\n");
        return;
    }
    search_field = atoi(search_str);
    if (search_field < 1 || search_field > 3)
    {
        printf("Invalid choice.\n");
        return;
    }

    printf("Enter search string: ");
    if (!fgets(search_str, sizeof(search_str), stdin))
    {
        printf("Input error.\n");
        return;
    }
    search_str[strcspn(search_str, "\n")] = '\0';

    printf("Enter 1 to borrow, 0 to return: ");
    if (!fgets(action_input, sizeof(action_input), stdin))
    {
        printf("Input error.\n");
        return;
    }
    action_input[strcspn(action_input, "\n")] = '\0';

    if (strcmp(action_input, "1") == 0)
        borrow = 1;
    else if (strcmp(action_input, "0") == 0)
        borrow = 0;
    else
    {
        printf("Invalid input for borrow/return.\n");
        return;
    }

    if (!update_availability(library, search_str, borrow, search_field))
        printf("Failed to update availability.\n");
    else
        printf("Availability updated successfully.\n");
}

void handle_sort_books(Book **library)
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
        return;
    }

    sort_by = atoi(sort_input);
    if (sort_by != 1 && sort_by != 2)
    {
        printf("Invalid sorting option.\n");
        return;
    }

    sort_books(library, sort_by);
    printf("Books sorted successfully.\n");
}

void handle_save_books(Book *library)
{
    if (save_books("books.txt", library) == 0)
        printf("Books saved successfully.\n");
    else
        printf("Failed to save books.\n");
}

void handle_load_books(Book **library)
{
    free_books(*library);
    *library = NULL;

    if (load_books("books.txt", library) == 0)
        printf("Books loaded successfully.\n");
    else
        printf("Failed to load books.\n");
}

void handle_exit(Book **library)
{
    printf("Exiting program.\n");
    free_books(*library);
    *library = NULL;
}
