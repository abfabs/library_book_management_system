# Library Book Management System

## Phase 2 - Basic Functionality Implementation

This project is a simple command-line program to manage books in a small library.  

### Features Implemented So Far:
- Load books from a text file (`books.txt`) into a linked list.
- Display all books with details (Title, Author, ISBN, Availability).
- Add new books programmatically (used internally during file loading).
- Free memory after use to avoid leaks.

### Technologies
- Language: C
- Data Structure: Singly linked list for book storage
- File I/O: Reading book data from a text file

### File Structure
- `main.c` — program entry point and menu loop
- `book.h` — book struct and function declarations
- `book.c` — implementation of book management functions
- `books.txt` — sample book data file

### Usage
1. Compile the program using `gcc`.
2. Run the executable.
3. Choose one of the two options from the menu to either display all the books or exit.

### Next Steps
- Add interactive user input to add books manually.
- Implement search by title or ISBN.
- Allow updating book availability status.
- Save updated records back to file.

## Developers
This project was developed by:

- Alba Eftimi
- Sokol Gjeka
---