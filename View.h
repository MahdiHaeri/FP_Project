#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "User.h"
#include "Reserve.h"
#include "Food.h"
#include "Self.h"

#define MAX_QUERY_SIZE 1000

int callback(void* data, int argc, char** argv, char** azColName) {
    printf("|");
    for (int i = 0; i < argc; i++) {
        printf("%-15s", argv[i]? argv[i] : "NULL");
        printf("|");
    }
    printf("\n");
    return 0;
}


//
void main_menu() {
    printf("Welcome to the restaurant reservation system\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
}

// -----------------------------------------------

// login as admin/
void admin_login_menu() {
    printf("1. Student management\n");
    printf("2. Food management\n");
    printf("3. Meal management\n");
    printf("4. Self management\n");
    printf("6. Profile\n");
    printf("7. Back\n");
}

// login as student/
void student_login_menu() {
    printf("1. Reserve\n");
    printf("2. Check News\n");
    printf("3. Check Poll\n");
    printf("4. Profile\n");
    printf("5. Back\n");
}

// Register/
// void register_menu() {
//     // get user info
//     printf("Enter your name: ");
//     char name[50];
//     scanf("%s", name);
//     printf("Enter your password: ");
//     char password[50];
//     scanf("%s", password);
//     printf("Enter your student id: ");
//     char student_id[50];
//     scanf("%s", student_id);
//     printf("Enter your phone number: ");
//     char phone_number[50];
//     scanf("%s", phone_number);
//     printf("Enter your email: ");
//     char email[50];
//     scanf("%s", email);
//     printf("Enter your address: ");
//     char address[50];
//     scanf("%s", address);
//     printf("Enter your balance: ");
//     int balance;
//     scanf("%d", &balance);
//     printf("Enter your status: ");
//     int status;
//     scanf("%d", &status);
//     printf("Enter your type: ");
//     int type;
//     scanf("%d", &type);
//     // create user
//     User* user = create_user(name, password, student_id, phone_number, email, address, balance, status, type);
//     // insert user to database
//     insert_user(user);
//     // free user
//     free_user(user);
// }
// -----------------------------------------------

// login as admin/ Student management/ 
void admin_student_management_menu() {
    printf("1. Approve student\n");
    printf("2. Change Student Password\n");
    printf("3. Remove Student\n");
    printf("4. Deactivate Student\n");
    printf("5. Charge Student Account\n");
    printf("6. Take Student Report\n");
    printf("7. Add News\n");
    printf("8. Add Poll\n");
    printf("9. Back\n");
}

// login as admin/ Food management/
void admin_food_management_menu() {
    printf("1. ADD Food\n");
    printf("2. Remove Food\n");
    printf("3. Change Food Price\n");
    printf("4. Back\n");
}

// login as admin/ Meal management/
void admin_meal_management_menu() {
    printf("1. Add Meal\n");
    printf("2. Remove Meal\n");
    printf("3. Back\n");
}

// login as admin/ Self management/
void admin_self_management_menu() {
    printf("1. Add Self\n");
    printf("2. Remove Self\n");
    printf("3. Back\n");
}

// login as student/ Profile/
void admin_profile_menu() {
    printf("1. Change Password\n");
    printf("2. Charge Account\n");
    printf("3. Add Admin\n");
    printf("4. Back\n");
}

// login as student/ Reserve/
void student_reserve_menu() {
    printf("1. Reserve\n");
    printf("2. Cancel Reserve\n");
    printf("3. Back\n");
}

// login as student/ Check News/
void student_check_news_menu() {
    printf("1. Check News\n");
    printf("2. Back\n");
}

// login as student/ Check Poll/
void student_check_poll_menu() {
    printf("1. Check Poll\n");
    printf("2. Back\n");
}

// login as student/ Profile/
void student_profile_menu() {
    printf("1. Change Password\n");
    printf("2. Charge Account\n");
    printf("3. Send Charge\n");
    printf("4. Back\n");
}

// -----------------------------------------------





    
#endif