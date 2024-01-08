
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

    // 主選單迴圈
    do {
        // 顯示主選單
        printf("\n1. Register\n");
        printf("2. Login\n");
        printf("3. Logout\n");
        printf("4. Display User Data\n");
        printf("5. Update User Data\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // 根據選擇執行相應的功能
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

// 註冊新使用者
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

    // 檢查使用者是否已存在
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

    // 寫入新使用者到檔案中
    fprintf(file, "%s %s\n", newUser.username, newUser.password);
    printf("User registered successfully!\n");

    fclose(file);
}

// 登入使用者
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

// 登出使用者
void logoutUser() {
    printf("Logout successful!\n");
}

// 顯示使用者資料
void displayUserData() {
    printf("User data displayed.\n");
    // 實際應用中需要實現顯示使用者資料的程式碼
}

// 更新使用者資料
void updateUserData() {
    printf("User data updated.\n");
    // 實際應用中需要實現更新使用者資料的程式碼
}
