// login_system.c
#define _CRT_SECURE_NO_WARNINGS
#include "login_system.h"
#include <stdio.h>
#include <string.h>

struct User users[MAX_USERS];
int userCount = 0;

int loadUsers(struct User* users, int* userCount) {
    FILE* file = fopen("user.txt", "r");
    if (file == NULL) {
        printf("無法打開用戶文件。\n");
        return 0;  // 讀取失敗
    }

    int count = 0;

    // 檢查文件是否為空
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == 0) {
        fclose(file);
        printf("用戶文件是空的。\n");
        return 0;
    }

    // 將文件指針重新設定到開頭
    fseek(file, 0, SEEK_SET);

    while (fscanf(file, "%s %s %s", users[count].username, users[count].password, users[count].historyFile) == 3) {
        count++;

        if (count >= MAX_USERS) {
            printf("錯誤：用戶數超出最大限制。\n");
            break;
        }
    }
    *userCount = count;  // 將 count 賦值給 *userCount，以更新調用函數中的 userCount 變數
    fclose(file);
    return count;  // 返回成功讀取的用戶數
}
int userExists(struct User* users, int userCount, const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        // 只比對用戶名
        if (strcmp(users[i].username, username) == 0) {
            // 如果提供了密碼，同時比對密碼
            if (password[0] != '\0' && strcmp(users[i].password, password) == 0) {
                return 1;  // 用戶存在
            }
            else if (password[0] == '\0') {
                return 1;  // 只比對用戶名，且沒有提供密碼，也視為用戶存在
            }
        }
    }
    return 0;  // 用戶不存在
}
int userExistsByUsernameAndPassword(struct User* users, int userCount, const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;  // 用戶名和密碼都匹配
        }
    }
    return 0;  // 用戶不存在或密碼不匹配
}


void addToHistory(const char* result, const char* historyFile) {
    FILE* file = fopen(historyFile, "a");

    if (file != NULL) {
        fprintf(file, "%s\n", result);
        fclose(file);
    }
    else {
        printf("無法打開歷史檔案：%s\n", historyFile);
    }
}

void displayHistory(const char* historyFile) {
    FILE* file = fopen(historyFile, "r");

    if (file != NULL) {
        char line[100];
        int isEmpty = 1;

        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
            isEmpty = 0;
        }

        fclose(file);

        if (isEmpty) {
            printf("沒有歷史紀錄。\n");
        }
    }
    else {
        printf("無法打開歷史檔案：%s\n", historyFile);
    }
}
void logout(struct User* user) {
    printf("用戶已退出。\n");
}

int handleLogin(struct User* user) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    loadUsers(users, &userCount);
    printf("請輸入帳號: ");
    scanf("%19s", username);

    printf("請輸入密碼: ");
    scanf("%19s", password);

    // 再檢查用戶名和密碼是否匹配
    if (userExistsByUsernameAndPassword(users, userCount, username, password) == 1) {
        // 登入成功的處理邏輯
        strcpy(user->username, username);
        strcpy(user->password, password);
        snprintf(user->historyFile, sizeof(user->historyFile), "%s_history.txt", username);
        printf("登入成功！\n");
        return 1;
    }
    else {
        // 登入失敗的處理邏輯
        printf("登入失敗。請確認密碼是否正確。\n");
        return 0;
    }
}

int handleRegistration(struct User* user, struct User* users, int* userCount) {
    loadUsers(users, userCount);
    printf("請輸入新的用戶名: ");
    scanf("%s", user->username);

    // 檢查新用戶是否已存在
    if (userExists(users, *userCount, user->username, "")) {
        printf("用戶已存在，註冊失敗。\n");
        return 0;  // 表示註冊失敗
    }

    printf("請輸入密碼: ");
    scanf("%s", user->password);

    snprintf(user->historyFile, sizeof(user->historyFile), "%s_history.txt", user->username);

    FILE* historyFile = fopen(user->historyFile, "w");
    if (historyFile != NULL) {
        fclose(historyFile);
    }
    else {
        printf("無法創建歷史檔案：%s\n", user->historyFile);
        return 0;  // 表示註冊失敗
    }

    FILE* userFile = fopen("user.txt", "a");
    if (userFile != NULL) {
        // 將新用戶信息寫入用戶檔案
        fprintf(userFile, "%s %s %s\n", user->username, user->password, user->historyFile);
        fclose(userFile);

        // 將新用戶添加到 users 數組中
        strcpy(users[*userCount].username, user->username);
        strcpy(users[*userCount].password, user->password);
        strcpy(users[*userCount].historyFile, user->historyFile);
        (*userCount)++;

        printf("註冊成功！\n");
        return 1;  // 表示註冊成功
    }
    else {
        printf("無法打開用戶檔案：user.txt\n");
        return 0;  // 表示註冊失敗
    }
}
