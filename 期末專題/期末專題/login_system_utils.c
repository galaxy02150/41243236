#define _CRT_SECURE_NO_WARNINGS
#include "login_system.h"
#include <stdio.h>
#include <string.h>

int loadUsers(struct User* users, int maxUsers) {
    FILE* file = fopen("user.txt", "r");

    if (file == NULL) {
        printf("���~�G�L�k���}�Τ���C\n");
        return 0;  // Ū������
    }

    int count = 0;

    while (fscanf(file, "%s %s", users[count].username, users[count].password) == 2) {
        count++;

        if (count >= maxUsers) {
            printf("���~�G�Τ�ƶW�X�̤j����C\n");
            break;
        }
    }

    fclose(file);

    return count;  // ��^���\Ū�����Τ��
}

int userExists(const struct User* users, int userCount, const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;  // �Τ�s�b
        }
    }

    return 0;  // �Τᤣ�s�b
}

int login(struct User* users, int userCount, struct User* user) {
    printf("�п�J�Τ�W�G ");
    scanf("%s", user->username);

    printf("�п�J�K�X�G ");
    scanf("%s", user->password);

    if (userExists(users, userCount, user->username, user->password)) {
        printf("�Τ�n�J���\�I\n");
        return 1;  // �n�J���\
    }
    else {
        printf("���~�G�Τ�W�αK�X�����T�C\n");
        return 0;  // �n�J����
    }
}

int registerUser(struct User* users, int userCount, struct User* user) {
    printf("�п�J�s���Τ�W�G ");
    scanf("%s", user->username);

    printf("�п�J�K�X�G ");
    scanf("%s", user->password);

    // �ˬd�Τ�O�_�w�g�s�b
    if (userExists(users, userCount, user->username, user->password)) {
        printf("�Τ�w�s�b�A���U���ѡC\n");
        return 0;  // ���U����
    }

    // �}�ҥΤ���H�g�J�Ҧ�
    FILE* userFile = fopen("user.txt", "a");

    if (userFile != NULL) {
        // �N�s�Τ��T�g�J���
        fprintf(userFile, "%s %s\n", user->username, user->password);

        // �������
        fclose(userFile);

        // �ЫإΤ᪺���v�O�����
        FILE* historyFile = fopen(user->historyFile, "w");
        if (historyFile != NULL) {
            fclose(historyFile);
        }
        else {
            printf("���~�G�L�k�Ыؾ��v�O�����C\n");
            return 0;  // ���U����
        }

        printf("�Τ���U���\�I\n");
        return 1;  // ���U���\
    }
    else {
        printf("���~�G�L�k���}�Τ���C\n");
        return 0;  // ���U����
    }
}