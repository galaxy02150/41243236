
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define FILENAME "users.txt"

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    // You can add more fields for user data if needed
};

// Function prototypes
void registerUser();
void loginUser();
void logoutUser();
void displayUserData();
void updateUserData();

int rost() {
    int choice;

    // �D���j��
    do {
        // ��ܥD���
        printf("\n1. Register\n");
        printf("2. Login\n");
        printf("3. Logout\n");
        printf("4. Display User Data\n");
        printf("5. Update User Data\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // �ھڿ�ܰ���������\��
        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            logoutUser();
            break;
        case 4:
            displayUserData();
            break;
        case 5:
            updateUserData();
            break;
        case 6:
            printf("Exiting program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}

// ���U�s�ϥΪ�
void registerUser() {
    FILE* file = fopen(FILENAME, "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct User newUser;
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);

    // �ˬd�ϥΪ̬O�_�w�s�b
    FILE* checkFile = fopen(FILENAME, "r");
    if (checkFile != NULL) {
        struct User existingUser;
        while (fscanf(checkFile, "%s %s", existingUser.username, existingUser.password) == 2) {
            if (strcmp(existingUser.username, newUser.username) == 0) {
                printf("User with the same username already exists. Registration failed.\n");
                fclose(file);
                fclose(checkFile);
                return;
            }
        }
        fclose(checkFile);
    }

    // �g�J�s�ϥΪ̨��ɮפ�
    fprintf(file, "%s %s\n", newUser.username, newUser.password);
    printf("User registered successfully!\n");

    fclose(file);
}

// �n�J�ϥΪ�
void loginUser() {
    char enteredUsername[MAX_USERNAME_LENGTH];
    char enteredPassword[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", enteredUsername);
    printf("Enter password: ");
    scanf("%s", enteredPassword);

    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct User currentUser;
    while (fscanf(file, "%s %s", currentUser.username, currentUser.password) == 2) {
        if (strcmp(currentUser.username, enteredUsername) == 0 &&
            strcmp(currentUser.password, enteredPassword) == 0) {
            printf("Login successful!\n");
            fclose(file);
            return;
        }
    }

    printf("Login failed. Please check your username and password.\n");
    fclose(file);
}

// �n�X�ϥΪ�
void logoutUser() {
    printf("Logout successful!\n");
}

// ��ܨϥΪ̸��
void displayUserData() {
    printf("User data displayed.\n");
    // ������Τ��ݭn��{��ܨϥΪ̸�ƪ��{���X
}

// ��s�ϥΪ̸��
void updateUserData() {
    printf("User data updated.\n");
    // ������Τ��ݭn��{��s�ϥΪ̸�ƪ��{���X
}
