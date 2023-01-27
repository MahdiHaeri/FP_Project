#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"
#include "Reserve.h"
#include "Food.h"
#include "Self.h"

#define MAX_QUERY_SIZE 1000
#define LOGIN 1
#define LOGOUT 0

MYSQL* con;

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void create_database() {
    char query[MAX_QUERY_SIZE] = "CREATE DATABASE IF NOT EXISTS Restaurant;";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void open_database() {
    con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    // if (mysql_real_connect(con, "localhost", "root", "", NULL, 0, NULL, 0) == NULL) {
    //     finish_with_error(con);
    // }
    // create_database();
    if (mysql_real_connect(con, "localhost", "root", "", "Restaurant", 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }
}

// ----------------- CREATE TABLES -----------------

void create_food_table() {
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS Food ("\
	"food_id	INTEGER NOT NULL,"\
	"name	INTEGER NOT NULL,"\
	"type	INTEGER NOT NULL,"\
	"price	INTEGER,"\
	"PRIMARY KEY(food_id));";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void create_user_table() {
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS User (" \
    "user_id	INTEGER NOT NULL," \
	"name 	TEXT NOT NULL," \
	"family 	TEXT NOT NULL," \
	"password 	TEXT NOT NULL," \
	"nation_id_code 	TEXT NOT NULL," \
	"birthdate	INTEGER," \
	"gender 	TEXT," \
	"type	TEXT," \
	"status 	TEXT," \
	"login_logout 	TEXT," \
	"balance 	INTEGER," \
	"PRIMARY KEY(user_id));";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void create_Self_table() {
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS Self (" \
    "self_id	INTEGER NOT NULL," \
    "name	TEXT," \
    "location	TEXT," \
    "capacity 	INTEGER," \
    "type	TEXT," \
    "meal	TEXT," \
    "lunch_start_time	INTEGER," \
    "lunch_end_time	INTEGER," \
    "dinner_start_time	INTEGER," \
    "dinner_finish_time	INTEGER," \
    "PRIMARY KEY(self_id));";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void create_reserve_table() {
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS Reserve (" \
    "reserve_id	INTEGER NOT NULL," \
    "self_id	INTEGER NOT NULL," \
    "date	INTEGER," \
    "meal	INTEGER," \
    "food_id	INTEGER NOT NULL," \
    "PRIMARY KEY(reserve_id));";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void create_meal_plan_table() {
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS MealPlan (" \
    "meal_id	INTEGER NOT NULL," \
    "self_id	INTEGER NOT NULL," \
    "type	TEXT," \
    "date	INTEGER," \
    "PRIMARY KEY(meal_id));";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void create_food_plan_connector_table() {
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS FoodPlanConnector (" \
    "meal_plan_id	INTEGER NOT NULL," \
    "food_id	INTEGER NOT NULL," \
    "count	INTEGER NOT NULL," \
    "PRIMARY KEY(meal_plan_id,food_id));";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void create_tables() {
    create_user_table();
    create_food_table();
    create_Self_table();
    create_reserve_table();
    create_meal_plan_table();
    create_food_plan_connector_table();
}

void init_database() {
    open_database();
    create_tables();
}










// ----------------------------------------------

void insert_user(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "INSERT IGNORE INTO User VALUES (%d, '%s', '%s', '%s', '%s', '%lld', '%s', '%s', '%s', '%s', %d);",
            user->user_id,
            user->name,
            user->family,
            user->password,
            user->nation_id_code,
            user->birthdate,
            user->gender,
            user->type,
            user->status,
            user->login_logout,
            user->balance);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void delete_user(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "DELETE FROM User WHERE user_id = %d;", user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void login_user(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "UPDATE User SET login_logout = 'login' WHERE user_id = %d;", user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void logout_user(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "UPDATE User SET login_logout = 'logout' WHERE user_id = %d;", user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// change user password 
void change_user_password(User* user, char* new_password) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "UPDATE User SET password = '%s' WHERE user_id = %d;", new_password, user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// approve user 
void approve_user(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "UPDATE User SET status = 'active' WHERE user_id = %d;", user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// deactivate user
void deactivate_user(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "UPDATE User SET status = 'deactive' WHERE user_id = %d;", user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// charge user account  
void charge_user_account(User* user, int amount) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "UPDATE User SET balance = balance + %d WHERE user_id = %d;", amount, user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// reserve food
void reserve_food(Reserve* reserve) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "INSERT INTO Reserve VALUES (%d, %d, %lld, %d, %d);",
            reserve->reserve_id,
            reserve->self_id,
            reserve->date,
            reserve->meal,
            reserve->food_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// cancel reserve
void cancel_reserve(Reserve* reserve) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "DELETE FROM Reserve WHERE reserve_id = %d;", reserve->reserve_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}



// show user's reserve
void show_user_reserve(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "SELECT * FROM Reserve WHERE user_id = %d;", user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

bool select_user_by_id_and_password(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "SELECT * FROM User WHERE user_id = %d AND password = '%s';", user->user_id, user->password);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    int num_rows = mysql_num_rows(result);
    if (num_rows == 0) {
        return false;
    }
    MYSQL_ROW row;
    row = mysql_fetch_row(result);
    user->user_id = atoi(row[0]);
    strcpy(user->name, row[1]);
    strcpy(user->family, row[2]);
    strcpy(user->password, row[3]);
    strcpy(user->nation_id_code, row[4]);
    user->birthdate = atoi(row[5]);
    strcpy(user->gender, row[6]);
    strcpy(user->type, row[7]);
    strcpy(user->status, row[8]);
    strcpy(user->login_logout, row[9]);
    user->balance = atoi(row[10]);
    return true;
}

void select_all_users() {
    char query[MAX_QUERY_SIZE] = "SELECT * FROM User;";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    print_select_result(*result);
}

// ------------------ Food ------------------ //

void insert_food(Food* food) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "INSERT INTO Food VALUES(%d, '%s', '%s', %d);", 
            food->food_id,
            food->name,
            food->type,
            food->price);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void delete_food(Food* food) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "DELETE FROM Food WHERE food_id = %d;", food->food_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void change_food_price(Food* food, int new_price) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "UPDATE Food SET price = %d WHERE food_id = %d;", new_price, food->food_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

#endif