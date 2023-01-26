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
#include "Controller.h"

void handel_student_login_menu();
void handel_admin_login_menu();  


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
    char nation_id_code[MAX_ARRAY_SIZE];
    long long int birth_date;
    char gender[MAX_ARRAY_SIZE];
    char type[MAX_ARRAY_SIZE] = "student";
    char status[MAX_ARRAY_SIZE] = "deactive";
    char login_status[MAX_ARRAY_SIZE] = "logout";
    int balance = 0;

    // get input
    printf("Enter your name: ");
    scanf(" %s", name);
    printf("Enter your family: ");
    scanf(" %s", family);
    printf("Enter your user id: ");
    scanf("%d", &user_id);
    printf("Enter your password: ");
    scanf(" %s", password);
    printf("Enter your nation id code: ");
    scanf(" %s", nation_id_code);
    printf("Enter your birth date: ");
    scanf("%lld", &birth_date);
    printf("Enter your gender: ");
    scanf(" %s", gender);
    
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

void login_user_command() {
    User* user = (User*)malloc(sizeof(User));
    user_constructor(user);
    printf("Enter your user id: ");
    scanf("%d", &user->user_id);
    printf("Enter your password: ");
    scanf(" %s", user->password);

    select_user_by_id_and_password(user);

    if (user->name == NULL) {
        printf("User not found, your user id or password is not correct!\n");
    } else {
        current_user = *user;
        printf("User found!\n");
    }
    if (strcmp(user->status, "deactive") == 0) {
        printf("Your account is deactive!\n");
    } else {
        if (strcmp(user->login_logout, "login") == 0) {
            printf("You are already logged in!\n");
        } else {
            user->login_logout = "login";
            login_user(user);
            if (strcmp(user->type, "student") == 0) {
                printf("Welcome student!\n");
                handel_student_login_menu();
            } else if (strcmp(user->type, "admin") == 0) {
                printf("Welcome admin!\n");
                handel_admin_login_menu();
            }
        }
    }
}

void delete_user_command() {
    int user_id;
    printf("Which one of the user you want to delete?\n");
    printf("Enter user id : ");
    scanf("%d", &user_id);
    printf("Are you sure you want to delete user with id %d? (y/n): ", user_id);
    char answer;
    scanf(" %c", &answer);
    if (answer == 'n') {
        return;
    }
    User user;
    user.user_id = user_id;
    delete_user(&user);
}

void change_pass_with_admi_command() {
    int user_id;
    char new_password[MAX_ARRAY_SIZE];
    printf("Whose password do you want to change?\n");
    printf("Enter user id: ");
    scanf("%d", &user_id);
    printf("Please enter new password for user with id %d: ", user_id);
    scanf(" %s", new_password);

    User user;
    user.user_id = user_id;
    change_user_password(&user, new_password);
}

void approve_command() {
    int user_id;
    printf("Whose User do you want to approve?\n");
    printf("Enter User id: ");
    scanf("%d", &user_id);

    User user;
    user.user_id = user_id;
    approve_user(&user);
}
#endif