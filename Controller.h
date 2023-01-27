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
                change_current_user_password_command();
                break;
            case 2:
                // charge account
                charge_current_user_account_command();
                break;
            case 3:
                // send charge 
                send_charge_command();
                break;
            case 4:
                // show profile
                show_profile_command();
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
                change_current_user_password_command();
                break;
            case 2:
                // charge account
                charge_current_user_account_command();
                break;
            case 3:
                // add new admin 
                register_user_command("admin", "active");
                break;
            case 4:
                // show admins table
                show_admins_table_command();
                break;
            case 5:
                // show profile
                show_profile_command();
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

void handel_admin_meal_plan_management_menu() {
    bool break_flag = false;
    int choice;
    while (!break_flag) {
        admin_meal_plan_management_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                // define meal plan
                define_meal_plan_command();
                break;
            case 2:
                // remove meal plan
                delete_meal_plan_command();
                break;
            case 3:
                // show meal plans table
                show_meal_plans_table_command();
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
                // define new self
                define_self_command();
                break;
            case 2:
                // remove self from database
                delete_self_command();
                break;
            case 3:
                // show self table
                show_selfs_table_command();
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
                // add new food to database 
                define_food_command();
                break;
            case 2:
                // remove food from database
                delete_food_command();
                break;
            case 3:
                // change food price 
                change_food_price_command();
                break;
            case 4:
                // show foods table
                show_foods_table_command();
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
                approve_user_command();
                break;
            case 2:
                change_pass_with_admi_command();
                break;
            case 3:
                // remove student 
                delete_user_command();
                break;
            case 4:
                // deactive student
                deactivate_user_command();
                break;
            case 5:
                // charge student account 
                charge_user_account_with_admin_command();
            case 6:
                // add poll 
                // add_poll_command();
                // break;
            case 7:
                // add news 
                add_news_command();
                break;
            case 8:
                // delete news
                delete_news_command();
                break;
            case 9:
                // add poll
                // add_poll_command();
                break;
            case 10:
                // show student table
                show_students_table_command();
                break;
            case 11:
                // show news table
                show_news_table_command();
                break;
            case 12:
                // show poll table
                // 
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
                handel_admin_student_management_menu();
                break;
            case 2:
                handel_admin_food_management_menu();
                break;
            case 3:
                handel_admin_self_management_menu();
                break;
            case 4:
                // handel meal plan management
                handel_admin_meal_plan_management_menu();
                break;
            case 5:
                // handel profile
                handel_admin_profile_menu();
                break;
            case BACK:
                break_flag = true;
                logout_user_command();
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
                // check news
                show_news_table_command();
                break;
            case 3:
                handel_student_check_news_menu();
                break;
            case 4:
                // student profile
                handle_student_profile_menu();
                break;
            case BACK:
                break_flag = true;
                logout_user_command();
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
                login_user_command();
                break;
            case 2:
                register_user_command("student", "deactive");
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

#endif