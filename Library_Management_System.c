#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define MAX_BOOKS 100
#define TITLE_LENGTH 100
#define AUTHOR_LENGTH 100

typedef struct {
    int id;
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int is_available; // 1 for available, 0 for not available
}
Book;

Book library[MAX_BOOKS];
int book_count = 0;

void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    Book new_book;
    new_book.id = book_count + 1; // Simple ID assignment
    printf("Enter book title: ");
    getchar(); // To consume the newline character left by previous input
    fgets(new_book.title, TITLE_LENGTH, stdin);
    new_book.title[strcspn(new_book.title, "\n")] = 0; // Remove newline character

    printf("Enter author name: ");
    fgets(new_book.author, AUTHOR_LENGTH, stdin);
    new_book.author[strcspn(new_book.author, "\n")] = 0; // Remove newline character

    new_book.is_available = 1; // Book is available when added

    library[book_count] = new_book;
    book_count++;
    printf("Book added successfully!\n");
}

void display_books() {
    if (book_count == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\nList of Books:\n");
    for (int i = 0; i < book_count; i++) {
        printf("ID: %d\n", library[i].id);
        printf("Title: %s\n", library[i].title);
        printf("Author: %s\n", library[i].author);
        printf("Availability: %s\n", library[i].is_available ? "Available" : "Not Available");
        printf("-------------------------\n");
    }
}

void borrow_book() {
    int id;
    printf("Enter the ID of the book to borrow: ");
    scanf("%d", & id);

    if (id < 1 || id > book_count) {
        printf("Invalid book ID.\n");
        return;
    }

    if (library[id - 1].is_available) {
        library[id - 1].is_available = 0; // Mark as borrowed
        printf("You have borrowed the book: %s\n", library[id - 1].title);
    } else {
        printf("Sorry, the book is currently not available.\n");
    }
}

void return_book() {
    int id;
    printf("Enter the ID of the book to return: ");
    scanf("%d", & id);

    if (id < 1 || id > book_count) {
        printf("Invalid book ID.\n");
        return;
    }

    if (!library[id - 1].is_available) {
        library[id - 1].is_available = 1; // Mark as available
        printf("You have returned the book: %s\n", library[id - 1].title);
    } else {
        printf("This book was not borrowed.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", & choice);

        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                display_books();
                break;
            case 3:
                borrow_book();
                break;
            case 4:
                return_book();
                break;
            case 5:
                printf("Exiting the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}