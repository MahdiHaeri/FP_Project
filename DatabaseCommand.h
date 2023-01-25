#ifndef DATABASECOMMAND_H
#define DATABASECOMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "User.h"
#include "Reserve.h"
#include "Food.h"
#include "Self.h"
#include "Database.h"


#define MAX_QUERY_SIZE 1000
#define MAX_ARRAY_SIZE 100
#define LOGIN 1
#define LOGOUT 0

User current_user;

void register_student_command() {
    // define variables
    char name[MAX_ARRAY_SIZE];
    char family[MAX_ARRAY_SIZE];
    int user_id;
    char password[MAX_ARRAY_SIZE];
    int nation_id_code;
    long long int birth_date;
    char gender[MAX_ARRAY_SIZE];
    char type[MAX_ARRAY_SIZE] = "student";
    char status[MAX_ARRAY_SIZE] = "deactive";
    char login_status[MAX_ARRAY_SIZE] = "logout";
    int balance = 0;

    // get input
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your family: ");
    scanf("%s", family);
    printf("Enter your user id: ");
    scanf("%d", &user_id);
    printf("Enter your password: ");
    scanf("%s", password);
    printf("Enter your national id code: ");
    scanf("%d", &nation_id_code);
    printf("Enter your birth date: ");
    scanf("%lld", &birth_date);
    printf("Enter your gender: ");
    scanf("%s", gender);
    
    // create user
    User new_user;
    new_user.name = name;
    new_user.family = family;
    new_user.user_id = user_id;
    new_user.password = password;
    new_user.nation_id_code = nation_id_code;
    new_user.birthdate = birth_date;
    new_user.gender = gender;
    new_user.type = type;
    new_user.status = status;
    new_user.login_logout = login_status;
    new_user.balance = balance;
    
    // insert user to database
    insert_user(&new_user);
}

#endif