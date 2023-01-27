#ifndef DATABASECOMMAND_H
#define DATABASECOMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// #include <sqlite3.h>
#include "User.h"
#include "Reserve.h"
#include "Food.h"
#include "Self.h"
// #include "Database.h"
#include "Database_mysql.h"
#include "Controller.h"
#include "TimeLimit.h"

void handel_student_login_menu();
void handel_admin_login_menu();  


#define MAX_QUERY_SIZE 1000
#define MAX_ARRAY_SIZE 100
#define LOGIN 1
#define LOGOUT 0

User* current_user;

void register_user_command(char* user_type, char* user_status) {
    // define variables
    char name[MAX_ARRAY_SIZE];
    char family[MAX_ARRAY_SIZE];
    int user_id;
    char password[MAX_ARRAY_SIZE];
    char nation_id_code[MAX_ARRAY_SIZE];
    long long int birth_date;
    char gender[MAX_ARRAY_SIZE];
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
    new_user.type = user_type;
    new_user.status = user_status;
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


    if (select_user_by_id_and_password(user)) {
        printf("User found!\n");
    } else {
        printf("User not found, your user id or password is not correct!\n");
        return;
    }

    if (strcmp(user->status, "active") != 0) {
        printf("Your account is not active!\n");
    } else {
        if (strcmp(user->login_logout, "login") == 0) {
            printf("You are already logged in!\n");
            return;
        } else {
            current_user = user;
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

void logout_user_command() {
    if (strcmp(current_user->login_logout, "logout") == 0) {
        printf("You are already logged out!\n");
    } else {
        current_user->login_logout = "logout";
        logout_user(current_user);
        current_user = NULL;
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

void change_current_user_password_command() {
    char old_password[MAX_ARRAY_SIZE];
    char new_password[MAX_ARRAY_SIZE];
    printf("Please enter your old password: ");
    scanf(" %s", old_password);
    if (strcmp(old_password, current_user->password) != 0) {
        printf("Your old password is not correct!\n");
        return;
    }
    printf("Please enter your new password: ");
    scanf(" %s", new_password);
    change_user_password(current_user, new_password);
    strcpy(current_user->password, new_password);
}

void approve_user_command() {
    select_deactive_users();
    int user_id;
    printf("Whose User do you want to approve?\n");
    printf("Enter User id: ");
    scanf("%d", &user_id);

    User user;
    user.user_id = user_id;
    approve_user(&user);
}

void deactivate_user_command() {
    int user_id;
    printf("Whose User do you want to deactive?\n");
    printf("Enter User id: ");
    scanf("%d", &user_id);

    User user;
    user.user_id = user_id;
    deactivate_user(&user);
}

void charge_user_account_with_admin_command() {
    int user_id;
    int amount;
    printf("Whose User do you want to charge?\n");
    printf("Enter User id: ");
    scanf("%d", &user_id);
    printf("Enter amount: ");
    scanf("%d", &amount);

    User user;
    user.user_id = user_id;
    charge_user_account(&user, amount);
}

void charge_current_user_account_command() {
    int amount;
    printf("Enter amount: ");
    scanf("%d", &amount);
    charge_user_account(current_user, amount);
    current_user->balance += amount;
}

// ----------------- Food -----------------

void define_food_command() {
    int food_id;
    char name[MAX_ARRAY_SIZE];
    int price;
    char type[MAX_ARRAY_SIZE];

    printf("Enter food id: ");
    scanf("%d", &food_id);
    printf("Enter food name: ");
    scanf(" %s", name);
    printf("Enter food price: ");
    scanf("%d", &price);
    printf("Enter food type: ");
    scanf(" %s", type);

    Food food;
    food.food_id = food_id;
    food.name = name;
    food.price = price;
    food.type = type;

    insert_food(&food);
}

void delete_food_command() {
    int food_id;
    printf("Which one of the food you want to delete?\n");
    printf("Enter food id : ");
    scanf("%d", &food_id);
    printf("Are you sure you want to delete food with id %d? (y/n): ", food_id);
    char answer;
    scanf(" %c", &answer);
    if (answer == 'n') {
        return;
    }
    Food food;
    food.food_id = food_id;
    delete_food(&food);
}

void change_food_price_command() {
    int food_id;
    int new_price;
    printf("Which one of the food you want to change price?\n");
    printf("Enter food id : ");
    scanf("%d", &food_id);
    printf("Enter new price: ");
    scanf("%d", &new_price);

    Food food;
    food.food_id = food_id;
    change_food_price(&food, new_price);
}

void send_charge_command() {
    int user_id;
    int amount;


    printf("Whose user do you want send charge?\n");
    printf("Enter user id: ");
    scanf("%d", &user_id);
    if (user_id == current_user->user_id) {
        printf("You can't send charge to yourself!\n");
        return;
    }

    User user;
    user.user_id = user_id;
    
    if (!select_public_info_of_user(&user)) {
        printf("User with id %d doesn't exist!\n", user_id);
        return;
    }

    printf("Enter amount: ");
    scanf("%d", &amount);
    if (amount > current_user->balance) {
        printf("You don't have enough money!\n");
        return;
    }

    charge_user_account(&user, amount);
    charge_user_account(current_user, -amount);
    current_user->balance -= amount;
}

// ----------------- Self -----------------

void define_self_command() {
    int self_id;
    char name[MAX_ARRAY_SIZE];
    char location[MAX_ARRAY_SIZE];
    int capacity;
    char type[MAX_ARRAY_SIZE]; // boyish, girlish
    char meal[MAX_ARRAY_SIZE]; // lunch, dinner
    TimeLimit lunch_time_limit;
    TimeLimit dinner_time_limit;
    bool is_open = true;

    printf("Enter self id: ");
    scanf("%d", &self_id);
    printf("Enter self name: ");
    scanf(" %s", name);
    printf("Enter self location: ");
    scanf(" %s", location);
    printf("Enter self capacity: ");
    scanf("%d", &capacity);
    printf("Enter self type: ");
    scanf(" %s", type);
    printf("Enter self meal: ");
    scanf(" %s", meal);
    printf("Enter self lunch time limit: ");
    scanf("%lld %lld", &lunch_time_limit.start_time, &lunch_time_limit.end_time);
    printf("Enter self dinner time limit: ");
    scanf("%lld %lld", &dinner_time_limit.start_time, &dinner_time_limit.end_time);

    Self self;
    self.self_id = self_id;
    self.name = name;
    self.location = location;
    self.capacity = capacity;
    self.type = type;
    self.meal = meal;
    self.lunch_time_limit = lunch_time_limit;
    self.dinner_time_limit = dinner_time_limit;
    self.is_open = is_open;
    
    insert_self(&self);
}

void delete_self_command() {
    int self_id;
    printf("Which one of the self you want to delete?\n");
    printf("Enter self id : ");
    scanf("%d", &self_id);
    printf("Are you sure you want to delete self with id %d? (y/n): ", self_id);
    char answer;
    scanf(" %c", &answer);
    if (answer == 'n') {
        return;
    }
    Self self;
    self.self_id = self_id;
    delete_self(&self);
}


#endif