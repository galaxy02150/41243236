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
        printf("�L�k���}�Τ���C\n");
        return 0;  // Ū������
    }

    int count = 0;

    // �ˬd���O�_����
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == 0) {
        fclose(file);
        printf("�Τ���O�Ū��C\n");
        return 0;
    }

    // �N�����w���s�]�w��}�Y
    fseek(file, 0, SEEK_SET);

    while (fscanf(file, "%s %s %s", users[count].username, users[count].password, users[count].historyFile) == 3) {
        count++;

        if (count >= MAX_USERS) {
            printf("���~�G�Τ�ƶW�X�̤j����C\n");
            break;
        }
    }
    *userCount = count;  // �N count ��ȵ� *userCount�A�H��s�եΨ�Ƥ��� userCount �ܼ�
    fclose(file);
    return count;  // ��^���\Ū�����Τ��
}
int userExists(struct User* users, int userCount, const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        // �u���Τ�W
        if (strcmp(users[i].username, username) == 0) {
            // �p�G���ѤF�K�X�A�P�ɤ��K�X
            if (password[0] != '\0' && strcmp(users[i].password, password) == 0) {
                return 1;  // �Τ�s�b
            }
            else if (password[0] == '\0') {
                return 1;  // �u���Τ�W�A�B�S�����ѱK�X�A�]�����Τ�s�b
            }
        }
    }
    return 0;  // �Τᤣ�s�b
}
int userExistsByUsernameAndPassword(struct User* users, int userCount, const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;  // �Τ�W�M�K�X���ǰt
        }
    }
    return 0;  // �Τᤣ�s�b�αK�X���ǰt
}


void addToHistory(const char* result, const char* historyFile) {
    FILE* file = fopen(historyFile, "a");

    if (file != NULL) {
        fprintf(file, "%s\n", result);
        fclose(file);
    }
    else {
        printf("�L�k���}���v�ɮסG%s\n", historyFile);
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
            printf("�S�����v�����C\n");
        }
    }
    else {
        printf("�L�k���}���v�ɮסG%s\n", historyFile);
    }
}
void logout(struct User* user) {
    printf("�Τ�w�h�X�C\n");
}

int handleLogin(struct User* user) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    loadUsers(users, &userCount);
    printf("�п�J�b��: ");
    scanf("%19s", username);

    printf("�п�J�K�X: ");
    scanf("%19s", password);

    // �A�ˬd�Τ�W�M�K�X�O�_�ǰt
    if (userExistsByUsernameAndPassword(users, userCount, username, password) == 1) {
        // �n�J���\���B�z�޿�
        strcpy(user->username, username);
        strcpy(user->password, password);
        snprintf(user->historyFile, sizeof(user->historyFile), "%s_history.txt", username);
        printf("�n�J���\�I\n");
        return 1;
    }
    else {
        // �n�J���Ѫ��B�z�޿�
        printf("�n�J���ѡC�нT�{�K�X�O�_���T�C\n");
        return 0;
    }
}

int handleRegistration(struct User* user, struct User* users, int* userCount) {
    loadUsers(users, userCount);
    printf("�п�J�s���Τ�W: ");
    scanf("%s", user->username);

    // �ˬd�s�Τ�O�_�w�s�b
    if (userExists(users, *userCount, user->username, "")) {
        printf("�Τ�w�s�b�A���U���ѡC\n");
        return 0;  // ��ܵ��U����
    }

    printf("�п�J�K�X: ");
    scanf("%s", user->password);

    snprintf(user->historyFile, sizeof(user->historyFile), "%s_history.txt", user->username);

    FILE* historyFile = fopen(user->historyFile, "w");
    if (historyFile != NULL) {
        fclose(historyFile);
    }
    else {
        printf("�L�k�Ыؾ��v�ɮסG%s\n", user->historyFile);
        return 0;  // ��ܵ��U����
    }

    FILE* userFile = fopen("user.txt", "a");
    if (userFile != NULL) {
        // �N�s�Τ�H���g�J�Τ��ɮ�
        fprintf(userFile, "%s %s %s\n", user->username, user->password, user->historyFile);
        fclose(userFile);

        // �N�s�Τ�K�[�� users �Ʋդ�
        strcpy(users[*userCount].username, user->username);
        strcpy(users[*userCount].password, user->password);
        strcpy(users[*userCount].historyFile, user->historyFile);
        (*userCount)++;

        printf("���U���\�I\n");
        return 1;  // ��ܵ��U���\
    }
    else {
        printf("�L�k���}�Τ��ɮסGuser.txt\n");
        return 0;  // ��ܵ��U����
    }
}
