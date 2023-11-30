#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent user information
struct User {
    char username[50];
    char password[50];
};

// Structure to represent a booked ticket
struct Ticket {
    char username[50];
    char source[50];
    char destination[50];
};

// Function declarations
void createAccount();
void login();
void bookTicket();
void cancelTicket();
void printTicket(struct Ticket ticket);
void saveUserToFile(struct User user);
void saveTicketToFile(struct Ticket ticket);

int main() {
    int choice;

    do {
        printf("\nRailway Ticket Booking System\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Book Ticket\n");
        printf("4. Cancel Ticket\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                login();
                break;
            case 3:
                bookTicket();
                break;
            case 4:
                cancelTicket();
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void createAccount() {
    FILE *file = fopen("userinfo.txt", "a");
    struct User user;

    printf("Enter username: ");
    scanf("%s", user.username);
    printf("Enter password: ");
    scanf("%s", user.password);

    fprintf(file, "%s %s\n", user.username, user.password);

    fclose(file);
}

void login() {
    char enteredUsername[50];
    char enteredPassword[50];

    printf("Enter username: ");
    scanf("%s", enteredUsername);
    printf("Enter password: ");
    scanf("%s", enteredPassword);

    FILE *file = fopen("userinfo.txt", "r");
    struct User user;

    while (fscanf(file, "%s %s", user.username, user.password) != EOF) {
        if (strcmp(enteredUsername, user.username) == 0 &&
            strcmp(enteredPassword, user.password) == 0) {
            printf("Login successful!\n");
            fclose(file);
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
    fclose(file);
}

void bookTicket() {
    struct Ticket ticket;

    printf("Enter your username: ");
    scanf("%s", ticket.username);
    printf("Enter source station: ");
    scanf("%s", ticket.source);
    printf("Enter destination station: ");
    scanf("%s", ticket.destination);

    // Assuming the ticket is confirmed when booked
    saveTicketToFile(ticket);
    printTicket(ticket);
}

void cancelTicket() {
    // Implementation for ticket cancellation can be added here
    printf("Ticket cancellation feature is not implemented in this example.\n");
}

void saveUserToFile(struct User user) {
    FILE *file = fopen("userinfo.txt", "a");
    fprintf(file, "%s %s\n", user.username, user.password);
    fclose(file);
}

void saveTicketToFile(struct Ticket ticket) {
    FILE *file = fopen("tickets.txt", "a");
    fprintf(file, "%s %s %s\n", ticket.username, ticket.source, ticket.destination);
    fclose(file);
}

void printTicket(struct Ticket ticket) {
    char fileName[50];
    sprintf(fileName, "%s_ticket.txt", ticket.username);

    FILE *file = fopen(fileName, "w");
    fprintf(file, "Railway Ticket\n");
    fprintf(file, "Username: %s\n", ticket.username);
    fprintf(file, "Source: %s\n", ticket.source);
    fprintf(file, "Destination: %s\n", ticket.destination);

    fclose(file);

    printf("Ticket details saved to %s\n", fileName);
}
