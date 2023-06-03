#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ARRAY_SIZE 100

typedef struct User User;

struct User {
    char* name;
    char* family;
    int user_id;
    char* password;
    char* nation_id_code;
    long long int birthdate;
    char* gender;
    char* type;
    char* status;
    char* login_logout;
    int balance;
};

void user_constructor(User* user) {
    user->name = (char*)malloc(sizeof(char) * MAX_ARRAY_SIZE);
    user->family = (char*)malloc(sizeof(char) * MAX_ARRAY_SIZE);
    user->password = (char*)malloc(sizeof(char) * MAX_ARRAY_SIZE);
    user->nation_id_code = (char*)malloc(sizeof(char) * MAX_ARRAY_SIZE);
    user->gender = (char*)malloc(sizeof(char) * MAX_ARRAY_SIZE);
    user->type = (char*)malloc(sizeof(char) * MAX_ARRAY_SIZE);
    user->status = (char*)malloc(sizeof(char) * MAX_ARRAY_SIZE);
    user->login_logout = (char*)malloc(sizeof(char) * MAX_ARRAY_SIZE);
}



#endif
