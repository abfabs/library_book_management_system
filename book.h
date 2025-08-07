#ifndef BOOK_H
#define BOOK_H

#include <stddef.h>

/**
 * struct Book - Represents a book in the library
 * @title: Title of the book
 * @author: Author of the book
 * @isbn: ISBN of the book
 * @total_copies: Total number of copies the library owns
 * @available_copies: Number of copies currently available for borrowing
 * @next: Pointer to the next book in the linked list
 */
typedef struct Book
{
	char title[100];
	char author[100];
	char isbn[20];
	int total_copies;
	int available_copies;
	struct Book *next;
} Book;

/* File operations */
int load_books(const char *filename, Book **head);
int save_books(const char *filename, const Book *head);

/* Book operations */
int add_book(Book **head, const char *title, const char *author,
			 const char *isbn, int total_copies, int available_copies);
void display_book(const Book *book);
void display_all_books(const Book *head);
void free_books(Book *head);

/* Utility functions */
void search_book_by_title(Book *head, const char *title);
Book *search_book_by_isbn(Book *head, const char *isbn);
void sort_books(Book **head, int sort_by);
int add_book_from_input(Book **head);
int update_availability(Book *head, const char *search_str, int borrow,
						int search_field);
int contains_case_insensitive(const char *str, const char *substr);
void to_lower(const char *src, char *dest);

#endif /* BOOK_H */
