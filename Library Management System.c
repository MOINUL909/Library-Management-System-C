#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_USERS 10
#define MAX_TITLE 100
#define MAX_NAME 50
#define MAX_PASSWORD 20

// Structure for book
typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_NAME];
    int available; // 1 for available, 0 for issued
} Book;

// Structure for user
typedef struct {
    char username[MAX_NAME];
    char password[MAX_PASSWORD];
    int isAdmin; // 1 for admin, 0 for regular user
} User;

Book library[MAX_BOOKS];
User users[MAX_USERS];
int book_count = 0;
int user_count = 0;

// Function prototypes
void add_book();
void delete_book();
void search_book();
void check_availability();
void issue_book();
void return_book();
int login();
void display_menu(int isAdmin);

// Unique identifier comment
// moinul909: This code is for managing library books efficiently.

int main() {
    // Predefined admin user for login
    strcpy(users[0].username, "Moinul");
    strcpy(users[0].password, "Moinul909");
    users[0].isAdmin = 1;
    user_count++;

    int user_index = login();
    if (user_index == -1) {
        printf("Login failed!\n");
        return 1;
    }

    display_menu(users[user_index].isAdmin);
    return 0;
}

int login() {
    char username[MAX_NAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return i; // Return user index
        }
    }

    return -1; // Login failed
}

void display_menu(int isAdmin) {
    int choice;
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. Check Availability\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: if (isAdmin) add_book(); else printf("Access denied.\n"); break;
            case 2: if (isAdmin) delete_book(); else printf("Access denied.\n"); break;
            case 3: search_book(); break;
            case 4: check_availability(); break;
            case 5: issue_book(); break;
            case 6: return_book(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid option. Please try again.\n");
        }
    } while (choice != 7);
}

void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book new_book;
    new_book.id = book_count + 1; // Simple ID generation
    printf("Enter book title: ");
    scanf(" %[^\n]", new_book.title);

    // Check for duplicate book title
    for (int i = 0; i < book_count; i++) {
        if (strcmp(library[i].title, new_book.title) == 0) {
            printf("Book with this title already exists. Cannot add duplicate.\n");
            return;
        }
    }

    printf("Enter book author: ");
    scanf(" %[^\n]", new_book.author);
    new_book.available = 1; // Book is available

    library[book_count] = new_book;
    book_count++;
    printf("Book added successfully! ID: %d\n", new_book.id);
}

void delete_book() {
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            for (int j = i; j < book_count - 1; j++) {
                library[j] = library[j + 1]; // Shift left
            }
            book_count--;
            printf("Book deleted successfully!\n");
            return;
        }
    }

    printf("Book not found.\n");
}

void search_book() {
    char title[MAX_TITLE];
    printf("Enter book title to search: ");
    scanf(" %[^\n]", title);

    for (int i = 0; i < book_count; i++) {
        if (strstr(library[i].title, title) != NULL) {
            printf("Found Book ID: %d, Title: %s, Author: %s, Available: %s\n",
                   library[i].id, library[i].title, library[i].author,
                   library[i].available ? "Yes" : "No");
            return;
        }
    }

    printf("Book not found.\n");
}

void check_availability() {
    int id;
    printf("Enter book ID to check availability: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            printf("Book ID: %d, Title: %s, Available: %s\n",
                   library[i].id, library[i].title,
                   library[i].available ? "Yes" : "No");
            return;
        }
    }

    printf("Book not found.\n");
}

void issue_book() {
    int id;
    printf("Enter book ID to issue: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            if (library[i].available) {
                library[i].available = 0; // Mark as issued
                printf("Book issued successfully!\n");
            } else {
                printf("Book is already issued.\n");
            }
            return;
        }
    }

    printf("Book not found.\n");
}

void return_book() {
    int id;
    printf("Enter book ID to return: ");
    scanf("%d", &id);

    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            if (!library[i].available) {
                library[i].available = 1; // Mark as available
                printf("Book returned successfully!\n");
            } else {
                printf("Book was not issued.\n");
            }
            return;
        }
    }

    printf("Book not found.\n");
}
