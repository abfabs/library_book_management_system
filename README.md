# Library Book Management System

##  Type of Application  
A command-line application to manage books in a small library. Users will be able to add new books, display the catalog, search for specific titles or ISBNs, update availability status (borrow/return), and save/load book data using files.

##  Purpose  
This project simulates a simplified library system using C programming. It will use **structs** to represent books and a **linked list** to dynamically store and manage them. The program helps reinforce skills like function use, file handling, searching, sorting, and memory management.

## Key Functionalities  
- Add new book  
- Display all books  
- Search for book by **title** or **ISBN**  
- Mark book as **borrowed/returned**  
- Save and load book data from file  
- Exit program

##  Data Representation
```c
typedef struct Book {
    char title[100];
    char author[100];
    char isbn[20];
    int available; // 1 = available, 0 = borrowed
    struct Book *next; // For linked list
} Book;
```
## Data Structure

Usage of a linked list to store books. This allows easy dynamic addition/removal and flexibility without knowing the number of books in advance.

## Planned Menu Options
```
1. Add a New Book  
2. Display All Books  
3. Search Book by Title  
4. Search Book by ISBN  
5. Update Availability (Borrow/Return)  
6. Save to File  
7. Load from File  
8. Exit
```
## Technical Implementation
The program will be developed in C and run in the terminal as a menu-driven application. It will include:

- Structs to represent books
- Linked list to dynamically store book data
- Functions to modularize operations (add, search, update, etc.)
- Switch statements to handle user menu choices
- File handling for saving and loading book records
- Linear search to find books by title or ISBN


## Expected Outcome

By the end of the project, we aim to deliver:

- A fully functional, interactive Command Line interface application

- Real-time book management with a dynamic list

- Status tracking for borrowed/available books

- Save/load functionality using text files

## Developers
This project is developed by:

- Alba Eftimi
- Sokol Gjeka
