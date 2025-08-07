#include "book.h"
#include <string.h>

Book *search_book_by_title(Book *head, const char *title)
{
    while (head)
    {
        if (strcmp(head->title, title) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

Book *search_book_by_isbn(Book *head, const char *isbn)
{
    while (head)
    {
        if (strcmp(head->isbn, isbn) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}