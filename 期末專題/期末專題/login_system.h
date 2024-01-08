#ifndef LOGIN_SYSTEM_H
#define LOGIN_SYSTEM_H

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_USERS 100

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char historyFile[1000];
};
struct User currentUser;
extern struct User users[MAX_USERS];
extern int userCount;
int userExistsByUsername(struct User* users, int userCount, const char* username);
int userExists(const char* username, const char* password, int checkPassword);
void logout(struct User* user);
void addToHistory(const char* result, const char* historyFile);
void displayHistory(const char* historyFile);
int handleLogin(struct User* user);
int handleRegistration(struct User* user, struct User* users, int* userCount);
void showUserMenu(struct User* user);
int loadUsers(struct User* users, int* userCount);

#endif