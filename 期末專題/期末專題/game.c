#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "login_system.h"

int getValidChoice() {
    int choice;
    char input[100];

    do {
        printf("請輸入您的選擇: ");
        scanf("%s", input);

        if (isdigit(input[0])) {
            choice = atoi(input);

            if (choice >= 1 && choice <= 3) {
                break;
            }
            else {
                printf("輸入數字超出範圍，請重新輸入。\n");
            }
        }
        else {
            printf("輸入不是有效的數字，請重新輸入。\n");
        }

    } while (1);

    return choice;
}




void playGame(struct User* user) {
    int lowerBound = 1, upperBound = 100;
    int secretNumber, playerGuess, playerAttempts = 0;
    int computerGuess = 0, computerAttempts = 0;
    srand(time(NULL));

    printf("歡迎來到猜數字遊戲！\n");

    do {
        secretNumber = rand() % (upperBound - lowerBound + 1) + lowerBound;

        printf("新的一輪開始！\n");

        do {
            printf("請猜一個數字（%d~%d之間的數字）: ", lowerBound, upperBound);

            while (getchar() != '\n');

            if (scanf("%d", &playerGuess) == 1) {
                if (playerGuess >= lowerBound && playerGuess <= upperBound) {
                    playerAttempts++;

                    if (playerGuess > secretNumber) {
                        printf("太大了！再試一次。\n");
                        upperBound = playerGuess - 1;
                    }
                    else if (playerGuess < secretNumber) {
                        printf("太小了！再試一次。\n");
                        lowerBound = playerGuess + 1;
                    }
                    else {
                        printf("恭喜你猜中了！答案是 %d，你用了 %d 次嘗試。\n", secretNumber, playerAttempts);
                        addToHistory("玩家勝利", user->historyFile);
                        break;  // 玩家猜中，結束遊戲
                    }

                    computerGuess = rand() % (upperBound - lowerBound + 1) + lowerBound;
                    computerAttempts++;

                    printf("電腦猜了 %d。\n", computerGuess);

                    if (computerGuess > secretNumber) {
                        printf("電腦猜的太大了！\n");
                        upperBound = computerGuess - 1;
                    }
                    else if (computerGuess < secretNumber) {
                        printf("電腦猜的太小了！\n");
                        lowerBound = computerGuess + 1;
                    }
                    else {
                        printf("電腦猜中了！答案是 %d，它用了 %d 次嘗試。\n", secretNumber, computerAttempts);
                        addToHistory("電腦勝利", user->historyFile);
                        break;  // 電腦猜中，結束遊戲
                    }
                }
                else {
                    printf("輸入數字超出範圍，請重新輸入。\n");
                }
            }
            else {
                printf("輸入不是有效的數字，請重新輸入。\n");
            }

        } while (1);

        lowerBound = 1;
        upperBound = 100;

        char continueGame;
        printf("遊戲結束，是否繼續遊戲？（Y/N）: ");
        if (scanf(" %c", &continueGame) == 1) {
            if (continueGame != 'Y' && continueGame != 'y') {
                printf("感謝您的遊玩！再見！\n");
                break;
            }
        }
        else {
            printf("輸入無效，遊戲結束。\n");
            logout(user);
            break;
        }

    } while (1);
}
// main.c

int main() {
    struct User currentUser;
    int choice;
    int userCount = 0;
    struct User users[MAX_USERS];

    srand(time(NULL));
    do {
        // 正確傳遞 users 數組和 userCount 的地址
        loadUsers(users, &userCount);

        printf("歡迎來到登入系統和猜數字遊戲！\n");
        printf("1. 登入\n");
        printf("2. 註冊\n");
        printf("3. 退出\n");

        choice = getValidChoice();

        switch (choice) {
        case 1:
            if (handleLogin(&currentUser, users, userCount) == 1) {
                showUserMenu(&currentUser);
            }
            break;
        case 2:
            handleRegistration(&currentUser, users, &userCount);
            break;
        case 3:
            logout(&currentUser);
            break;
        default:
            printf("無效的選項，請重新輸入。\n");
        }

    } while (choice != 3);

    return 0;
}



void showUserMenu(struct User* user) {
    int gameChoice;

    do {
        printf("歡迎, %s！請選擇操作：\n", user->username);
        printf("1. 開始遊戲\n");
        printf("2. 顯示歷史記錄\n");
        printf("3. 登出\n");

        gameChoice = getValidChoice();

        switch (gameChoice) {
        case 1:
            playGame(user);
            break;
        case 2:
            displayHistory(user->historyFile);
            break;
        case 3:
            printf("已登出。\n");
            break;
        default:
            printf("無效的選項，請重新輸入。\n");
        }

    } while (gameChoice != 3);
}