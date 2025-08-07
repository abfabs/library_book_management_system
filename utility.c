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
 * search_book_by_title - Print all books with titles containing the given substring (case-insensitive)
 * @head: Pointer to the head of the book list
 * @title: Title substring to search for
 */
void search_book_by_title(Book *head, const char *title)
{
	if (head == NULL)
	{
		printf("No books in the library.\n");
		return;
	}

	char lower_search[100];
	to_lower(title, lower_search);

	Book *ptr = head;
	int found = 0;

	while (ptr)
	{
		char lower_title[100];
		to_lower(ptr->title, lower_title);

		if (strstr(lower_title, lower_search) != NULL)
		{
			printf("Title: %s\n", ptr->title);
			printf("Author: %s\n", ptr->author);
			printf("ISBN: %s\n", ptr->isbn);
			printf("Available Copies: %d\n\n", ptr->available_copies);
			found = 1;
		}
		ptr = ptr->next;
	}

	if (!found)
		printf("No books found with title matching \"%s\".\n", title);
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
		return (NULL);

	Book *ptr = head;
	while (ptr)
	{
		if (strcmp(ptr->isbn, isbn) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
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

	/* Swap titles */
	strcpy(temp_title, a->title);
	strcpy(a->title, b->title);
	strcpy(b->title, temp_title);

	/* Swap authors */
	strcpy(temp_author, a->author);
	strcpy(a->author, b->author);
	strcpy(b->author, temp_author);

	/* Swap ISBNs */
	strcpy(temp_isbn, a->isbn);
	strcpy(a->isbn, b->isbn);
	strcpy(b->isbn, temp_isbn);

	/* Swap copies */
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
			if (sort_by == 1) /* sort by title */
				cmp = strcmp(ptr->title, ptr->next->title);
			else if (sort_by == 2) /* sort by author */
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
 * contains_case_insensitive - helper for case-insensitive substring check
 * @str: main string
 * @substr: substring to check
 *
 * Return: 1 if substr is in str (case-insensitive), 0 otherwise
 */
int contains_case_insensitive(const char *str, const char *substr)
{
	if (!str || !substr)
		return (0);

	size_t len_sub = strlen(substr);
	size_t len_str = strlen(str);

	if (len_sub > len_str)
		return (0);

	for (size_t i = 0; i <= len_str - len_sub; i++)
	{
		int matched = 1;
		for (size_t j = 0; j < len_sub; j++)
		{
			if (tolower((unsigned char)str[i + j]) != tolower((unsigned char)substr[j]))
			{
				matched = 0;
				break;
			}
		}
		if (matched)
			return (1);
	}
	return (0);
}

/**
 * update_availability - update borrow/return status of books by ISBN, author, or title
 * @head: pointer to head of list
 * @search_str: string to find book(s) by ISBN, author, or title
 * @borrow: 1 to borrow (decrement available), 0 to return (increment available)
 * @search_field: 1 = ISBN, 2 = Title, 3 = Author
 *
 * Return: 1 if updated successfully, 0 otherwise
 */
int update_availability(Book *head, const char *search_str, int borrow, int search_field)
{
	if (!head || !search_str || search_str[0] == '\0')
		return (0);

	Book *ptr = head;

	while (ptr)
	{
		int match = 0;

		switch (search_field)
		{
			case 1: /* ISBN exact match */
				if (strcmp(ptr->isbn, search_str) == 0)
					match = 1;
				break;
			case 2: /* Title partial case-insensitive match */
				if (contains_case_insensitive(ptr->title, search_str))
					match = 1;
				break;
			case 3: /* Author partial case-insensitive match */
				if (contains_case_insensitive(ptr->author, search_str))
					match = 1;
				break;
			default:
				return (0);
		}

		if (match)
		{
			if (borrow)
			{
				if (ptr->available_copies <= 0)
					return (0);
				ptr->available_copies--;
			}
			else
			{
				if (ptr->available_copies >= ptr->total_copies)
					return (0);
				ptr->available_copies++;
			}
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

/**
 * read_line - helper to safely read a line from stdin
 * @buffer: buffer to store input
 * @size: buffer size
 *
 * Return: 1 on success, 0 on failure or EOF
 */
static int read_line(char *buffer, size_t size)
{
	if (fgets(buffer, size, stdin) == NULL)
		return (0);
	buffer[strcspn(buffer, "\n")] = '\0'; /* remove newline */
	return (1);
}

/**
 * add_book_from_input - prompts user for book info and adds the book
 * @head: pointer to the head pointer of the list
 *
 * Return: 1 on success, 0 on failure
 */
int add_book_from_input(Book **head)
{
	char title[100], author[100], isbn[20];
	char total_str[20], available_str[20];
	int total_copies, available_copies;

	printf("Enter book title: ");
	if (!read_line(title, sizeof(title)))
		return (0);

	printf("Enter book author: ");
	if (!read_line(author, sizeof(author)))
		return (0);

	printf("Enter book ISBN: ");
	if (!read_line(isbn, sizeof(isbn)))
		return (0);

	printf("Enter total copies: ");
	if (!read_line(total_str, sizeof(total_str)))
		return (0);
	total_copies = atoi(total_str);
	if (total_copies <= 0)
	{
		printf("Invalid total copies number.\n");
		return (0);
	}

	printf("Enter available copies: ");
	if (!read_line(available_str, sizeof(available_str)))
		return (0);
	available_copies = atoi(available_str);
	if (available_copies < 0 || available_copies > total_copies)
	{
		printf("Invalid available copies number.\n");
		return (0);
	}

	if (!add_book(head, title, author, isbn, total_copies, available_copies))
	{
		printf("Failed to add book due to memory allocation error.\n");
		return (0);
	}

	printf("Book added successfully.\n");
	return (1);
}
