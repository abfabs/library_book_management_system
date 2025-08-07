#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	if (!file)
		return (1);

	char line[512];
	while (fgets(line, sizeof(line), file))
	{
		char *title, *author, *isbn;
		int total_copies, available_copies;

		/* Remove trailing newline if present */
		line[strcspn(line, "\n")] = '\0';

		title = strtok(line, "|");
		author = strtok(NULL, "|");
		isbn = strtok(NULL, "|");
		char *total_str = strtok(NULL, "|");
		char *available_str = strtok(NULL, "|");

		if (!title || !author || !isbn || !total_str || !available_str)
			continue;

		total_copies = atoi(total_str);
		available_copies = atoi(available_str);

		if (!add_book(head, title, author, isbn, total_copies, available_copies))
		{
			fclose(file);
			return (1);
		}
	}

	fclose(file);
	return (0);
}

/**
 * save_books - saves book data from linked list to a file
 * @filename: name of the file to write to
 * @head: pointer to head of the list
 *
 * Return: 0 on success, 1 on failure
 */
int save_books(const char *filename, const Book *head)
{
	FILE *file = fopen(filename, "w");
	if (!file)
		return (1);

	while (head)
	{
		fprintf(file, "%s|%s|%s|%d|%d\n", head->title, head->author, head->isbn,
				head->total_copies, head->available_copies);
		head = head->next;
	}

	fclose(file);
	return (0);
}
