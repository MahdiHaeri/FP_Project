#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct User User;

struct User {
    char* name;
    char* family;
    int user_id;
    char* password;
    int nation_id_code;
    long long int birthdate;
    char* gender;
    char* type;
    char* status;
    bool login_logout;
    int balance;
};


#endif
