#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TicketInfo {
    int trainNumber;
    char trainName[50];
    float price;
};

struct UserInfo {
    char name[50];
    char email[50];
    char password[50];
};

void createAccount();
struct UserInfo login();
void bookTickets(struct UserInfo user);
void cancelTickets(struct UserInfo user);
void logout();

int main() {
    int choice;
    struct UserInfo currentUser;

    do {
        printf("\n1. Create Account\n2. Login\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                currentUser = login();
                if (strlen(currentUser.name) > 0) {
                    do {
                        printf("\n1. Book Tickets\n2. Cancel Tickets\n3. Logout\nEnter your choice: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1:
                                bookTickets(currentUser);
                                break;
                            case 2:
                                cancelTickets(currentUser);
                                break;
                            case 3:
                                logout();
                                break;
                            default:
                                printf("Invalid choice. Please try again.\n");
                        }
                    } while (choice != 3);
                }
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

void createAccount() {
    struct UserInfo newUser;

    printf("Enter your name: ");
    scanf("%s", newUser.name);
    printf("Enter your email: ");
    scanf("%s", newUser.email);
    printf("Enter your password: ");
    scanf("%s", newUser.password);

    FILE *file = fopen("userinfo.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(file, "%s %s %s\n", newUser.name, newUser.email, newUser.password);

    fclose(file);

    printf("Account created successfully!\n");
}

struct UserInfo login() {
    struct UserInfo user;
    char email[50];
    char password[50];

    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    FILE *file = fopen("userinfo.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    int userFound = 0;
    while (fscanf(file, "%s %s %s", user.name, user.email, user.password) != EOF) {
        if (strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0) {
            userFound = 1;
            break;
        }
    }

    fclose(file);

    if (userFound) {
        printf("Login successful, welcome %s!\n", user.name);
        return user;
    } else {
        printf("Invalid email or password. Please try again.\n");
        strcpy(user.name, "");
        return user;
    }
}

void bookTickets(struct UserInfo user) {
    int numTickets;
    struct TicketInfo tickets[3];

    printf("Available Tickets:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. Train %d - %s ($%.2f)\n", i + 1, i + 101, "Express", 50.0 + i * 10.0);
    }

    printf("Enter the number of tickets to book: ");
    scanf("%d", &numTickets);

    printf("Enter the ticket numbers to book (separated by spaces): ");
    for (int i = 0; i < numTickets; i++) {
        scanf("%d", &tickets[i].trainNumber);
        tickets[i].trainName[0] = '\0';
        tickets[i].price = 0.0;
    }

    FILE *file = fopen("bookedtickets.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(file, "%s", user.name);
    for (int i = 0; i < numTickets; i++) {
        fprintf(file, " %d", tickets[i].trainNumber);
    }
    fprintf(file, "\n");

    fclose(file);

    printf("Tickets booked successfully!\n");
}

void cancelTickets(struct UserInfo user) {
    int numTickets;
    struct TicketInfo tickets[3];

    printf("Booked Tickets:\n");

    FILE *file = fopen("bookedtickets.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char username[50];
    while (fscanf(file, "%s", username) != EOF) {
        if (strcmp(username, user.name) == 0) {
            printf("%s: ", user.name);
            while (fscanf(file, "%d", &numTickets) != EOF) {
                for (int i = 0; i < numTickets; i++) {
                    fscanf(file, "%d", &tickets[i].trainNumber);
                    printf("Train %d, ", tickets[i].trainNumber);
                }
                printf("\n");
            }
        }
    }

    fclose(file);

    printf("Enter the ticket numbers to cancel (separated by spaces): ");
    for (int i = 0; i < numTickets; i++) {
        scanf("%d", &tickets[i].trainNumber);
    }

    file = fopen("bookedtickets.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char tempUsername[50];
    while (fscanf(file, "%s", tempUsername) != EOF) {
        if (strcmp(tempUsername, user.name) == 0) {
            fprintf(tempFile, "%s", user.name);
            for (int i = 0; i < numTickets; i++) {
                fprintf(tempFile, " %d", tickets[i].trainNumber);
            }
            fprintf(tempFile, "\n");
        } else {
            fprintf(tempFile, "%s", tempUsername);
            while (fscanf(file, "%d", &numTickets) != EOF) {
                for (int i = 0; i < numTickets; i++) {
                    fprintf(tempFile, " %d", tickets[i].trainNumber);
                }
                fprintf(tempFile, "\n");
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("bookedtickets.txt");
    rename("temp.txt", "bookedtickets.txt");

    printf("Tickets canceled successfully!\n");
}

void logout() {
    printf("Logout successful. Returning to the main menu.\n");
}
