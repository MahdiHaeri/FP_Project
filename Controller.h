#ifndef CONTROLER_H
#define CONTROLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "View.h"
#include "User.h"
#include "Reserve.h"
#include "Food.h"
#include "Self.h"
#include "DatabaseCommand.h"

#define MAX_QUERY_SIZE 1000
#define LOGIN 1
#define LOGOUT 0

#define BACK 0


void handle_student_profile_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        student_profile_menu();
        scanf("%d", &choice);
        switch(choice) {
            // 4 case 
            case 1:
                // change password
                break;
            case 2:
                // change phone number
                break;
            case 3:
                // change email
                break;
            case BACK:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

void handle_student_check_poll_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        student_check_poll_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                // change password
                break;
            case 2:
                // change phone number
                break;
            case BACK:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

void handel_student_check_news_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        student_check_news_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                // change password
                break;
            case 2:
                // change phone number
                break;
            case BACK:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

void handel_student_reserve_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        student_reserve_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                // change password
                break;
            case 2:
                // change phone number
                break;
            case 3:
                // change email
                break;
            case BACK:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

void handel_admin_profile_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        admin_profile_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                // change password
                break;
            case 2:
                // change phone number
                break;
            case 3:
                // change email
                break;
            case BACK:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

void handel_admin_self_management_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        admin_self_management_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                // change password
                break;
            case 2:
                // change phone number
                break;
            case 3:
                // change email
                break;
            case BACK:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

void handel_admin_meal_management_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        admin_meal_management_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                // change password
                break;
            case 2:
                // change phone number
                break;
            case 3:
                // change email
                break;
            case BACK:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

void handel_admin_food_management_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        admin_food_management_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                // change password
                break;
            case 2:
                // change phone number
                break;
            case 3:
                // change email
                break;
            case BACK:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

void handel_admin_student_management_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        admin_student_management_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                // change password
                break;
            case 2:
                // change phone number
                break;
            case 3:
                // change email
                break;
            case BACK:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

void handel_admin_login_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        admin_login_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                handel_admin_profile_menu();
                break;
            case 2:
                handel_admin_self_management_menu();
                break;
            case 3:
                handel_admin_meal_management_menu();
                break;
            case 4:
                handel_admin_food_management_menu();
                break;
            case 5:
                handel_admin_student_management_menu();
                break;
            case BACK:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

void handel_student_login_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        student_login_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                handle_student_profile_menu();
                break;
            case 2:
                handle_student_check_poll_menu();
                break;
            case 3:
                handel_student_check_news_menu();
                break;
            case 4:
                handel_student_reserve_menu();
                break;
            case BACK:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

void handel_main_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        main_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                handel_student_login_menu();
                break;
            case 2:
                register_student_command();
                break;
            case 3:
                break_flag = true;
                break;
            default:
                printf("Invalid choice\n");
                break;
        };
    }
}

#endif