#define _CRT_SECURE_NO_WARNINGS
#include "login_system.h"
#include <stdio.h>
#include <string.h>

int loadUsers(struct User* users, int maxUsers) {
    FILE* file = fopen("user.txt", "r");

    if (file == NULL) {
        printf("錯誤：無法打開用戶文件。\n");
        return 0;  // 讀取失敗
    }

    int count = 0;

    while (fscanf(file, "%s %s", users[count].username, users[count].password) == 2) {
        count++;

        if (count >= maxUsers) {
            printf("錯誤：用戶數超出最大限制。\n");
            break;
        }
    }

    fclose(file);

    return count;  // 返回成功讀取的用戶數
}

int userExists(const struct User* users, int userCount, const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;  // 用戶存在
        }
    }

    return 0;  // 用戶不存在
}

int login(struct User* users, int userCount, struct User* user) {
    printf("請輸入用戶名： ");
    scanf("%s", user->username);

    printf("請輸入密碼： ");
    scanf("%s", user->password);

    if (userExists(users, userCount, user->username, user->password)) {
        printf("用戶登入成功！\n");
        return 1;  // 登入成功
    }
    else {
        printf("錯誤：用戶名或密碼不正確。\n");
        return 0;  // 登入失敗
    }
}

int registerUser(struct User* users, int userCount, struct User* user) {
    printf("請輸入新的用戶名： ");
    scanf("%s", user->username);

    printf("請輸入密碼： ");
    scanf("%s", user->password);

    // 檢查用戶是否已經存在
    if (userExists(users, userCount, user->username, user->password)) {
        printf("用戶已存在，註冊失敗。\n");
        return 0;  // 註冊失敗
    }

    // 開啟用戶文件以寫入模式
    FILE* userFile = fopen("user.txt", "a");

    if (userFile != NULL) {
        // 將新用戶資訊寫入文件
        fprintf(userFile, "%s %s\n", user->username, user->password);

        // 關閉文件
        fclose(userFile);

        // 創建用戶的歷史記錄文件
        FILE* historyFile = fopen(user->historyFile, "w");
        if (historyFile != NULL) {
            fclose(historyFile);
        }
        else {
            printf("錯誤：無法創建歷史記錄文件。\n");
            return 0;  // 註冊失敗
        }

        printf("用戶註冊成功！\n");
        return 1;  // 註冊成功
    }
    else {
        printf("錯誤：無法打開用戶文件。\n");
        return 0;  // 註冊失敗
    }
}