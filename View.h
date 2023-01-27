#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"
#include "Reserve.h"
#include "Food.h"
#include "Self.h"
#include "mysql/mysql.h"
#include "fort.h"

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
    printf("~/\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
}

// -----------------------------------------------

// login as admin/
void admin_login_menu() {
    printf("~/Login/\n");
    printf("1. Student management\n");
    printf("2. Food management\n");
    printf("3. Self management\n");
    printf("4. Meal Plan management\n");
    printf("5. Profile\n");
    printf("0. logout\n");
}

// login as student/
void student_login_menu() {
    printf("~/Login/\n");
    printf("1. Reserve\n");
    printf("2. Check News\n");
    printf("3. Check Poll\n");
    printf("4. Profile\n");
    printf("0. logout\n");
}

// Register/
// -----------------------------------------------

// login as admin/ Student management/ 
void admin_student_management_menu() {
    printf("~/Login/Student management/\n");
    printf("1. Approve student\n");
    printf("2. Change Student Password\n");
    printf("3. Remove Student\n");
    printf("4. Deactivate Student\n");
    printf("5. Charge Student Account\n");
    printf("6. Take Student Report\n");
    printf("7. Add News\n");
    printf("8. Add Poll\n");
    printf("0. Back\n");
}

// login as admin/ Food management/
void admin_food_management_menu() {
    printf("~/Login/Food management/\n");
    printf("1. ADD Food\n");
    printf("2. Remove Food\n");
    printf("3. Change Food Price\n");
    printf("0. Back\n");
}

// login as admin/ Self management/
void admin_self_management_menu() {
    printf("~/Login/Self management/\n");
    printf("1. Add Self\n");
    printf("2. Remove Self\n");
    printf("0. Back\n");
}

// login as admin/ Meal management/
void admin_meal_plan_management_menu() {
    printf("~/Login/Meal management/\n");
    printf("1. Add Meal Plan\n");
    printf("2. Remove Meal Plan\n");
    printf("0. Back\n");
}


// login as student/ Profile/
void admin_profile_menu() {
    printf("~/Login/Profile/\n");
    printf("1. Change Password\n");
    printf("2. Charge Account\n");
    printf("3. Add Admin\n");
    printf("0. Back\n");
}

// login as student/ Reserve/
void student_reserve_menu() {
    printf("~/Login/Reserve/\n");
    printf("1. Reserve\n");
    printf("2. Cancel Reserve\n");
    printf("0. Back\n");
}

// login as student/ Check News/
void student_check_news_menu() {
    printf("~/Login/Check News/\n");
    printf("1. Check News\n");
    printf("0. Back\n");
}

// login as student/ Check Poll/
void student_check_poll_menu() {
    printf("~/Login/Check Poll/\n");
    printf("1. Check Poll\n");
    printf("0. Back\n");
}

// login as student/ Profile/
void student_profile_menu() {
    printf("~/Login/Profile/\n");
    printf("1. Change Password\n");
    printf("2. Charge Account\n");
    printf("3. Send Charge\n");
    printf("0. Back\n");
}

// -----------------------------------------------

void print_user_info(User* user) {
    printf("user name: %s\n", user->name);
    printf("user family: %s\n", user->family);
    printf("user id: %d\n", user->user_id);
    printf("user password: %s\n", user->password);
    printf("user nation id code: %s\n", user->nation_id_code);
    printf("user birth data: %lld\n", user->birthdate);
    printf("user gender: %s\n", user->gender);
    printf("user type: %s\n", user->type);
    printf("user status: %s\n", user->status);
    printf("user login logout: %s\n", user->login_logout);
    printf("user balance: %d\n", user->balance);
}

// -----------------------------------------------

// print result of select query in a table
void print_select_result(MYSQL_RES result) {
    MYSQL_ROW row;
    MYSQL_FIELD* field;
    int num_fields = mysql_num_fields(&result);
    int num_rows = mysql_num_rows(&result);

    const char* field_names[num_fields];
    for (int i = 0; i < num_fields; i++) {
        field = mysql_fetch_field(&result);
        field_names[i] = field->name;
    }
    ft_table_t* table = ft_create_table();
    ft_set_border_style(table, FT_BASIC2_STYLE);
    ft_row_write_ln(table, num_fields, field_names);
    const char* row_data[num_fields];
    while ((row = mysql_fetch_row(&result))) {
        for (int i = 0; i < num_fields; i++) {
            row_data[i] = row[i];
        }
        ft_row_write_ln(table, num_fields, row_data);
    }
    // ft_print_table(table);
    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
}
    
#endif