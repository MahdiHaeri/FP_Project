#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "User.h"
#include "Reserve.h"
#include "Food.h"
#include "Self.h"
#include "CallBack.h"

#define MAX_QUERY_SIZE 1000
#define LOGIN 1
#define LOGOUT 0

sqlite3* db;
char* db_address = "program_data.db";


void open_database() {
    int rc = sqlite3_open(db_address, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s", sqlite3_errmsg(db));
    }
}

// ----------------- CREATE TABLES -----------------

void create_food_table() {
    int rc;
    char* error_message;
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS Food ("\
	"food_id	INTEGER NOT NULL,"\
	"name	INTEGER NOT NULL,"\
	"type	INTEGER NOT NULL,"\
	"price	INTEGER,"\
	"PRIMARY KEY(food_id));";
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create Food table error: %s\n", error_message);
    }
}

void create_user_table() {
    int rc;
    char* error_message;
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS User (" \
    "user_id	INTEGER NOT NULL," \
	"name 	TEXT NOT NULL," \
	"family 	TEXT NOT NULL," \
	"password 	INTEGER NOT NULL," \
	"nation_id_code 	TEXT NOT NULL UNIQUE," \
	"birthdate	INTEGER," \
	"gender 	TEXT," \
	"type	TEXT," \
	"status 	TEXT," \
	"login_logout 	INTEGER," \
	"balance 	INTEGER," \
	"PRIMARY KEY(user_id));";
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create User table error: %s\n", error_message);
    }
}

void create_Self_table() {
    int rc;
    char* error_message;
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
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create Self table error: %s\n", error_message);
    }
}

void create_reserve_table() {
    int rc;
    char* error_message;
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS Reserve (" \
    "reserve_id	INTEGER NOT NULL," \
    "self_id	INTEGER NOT NULL," \
    "date	INTEGER," \
    "meal	INTEGER," \
    "food_id	INTEGER NOT NULL," \
    "PRIMARY KEY(reserve_id));";
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create Reserve table error: %s\n", error_message);
    }
}

void create_meal_plan_table() {
    int rc;
    char* error_message;
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS MealPlan (" \
    "meal_id	INTEGER NOT NULL," \
    "self_id	INTEGER NOT NULL," \
    "type	TEXT," \
    "date	INTEGER," \
    "PRIMARY KEY(meal_id));";
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create MealPlan table error: %s\n", error_message);
    }
}

void create_food_plan_connector_table() {
    int rc;
    char* error_message;
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS FoodPlanConnector (" \
    "meal_plan_id	INTEGER NOT NULL," \
    "food_id	INTEGER NOT NULL," \
    "count	INTEGER NOT NULL," \
    "PRIMARY KEY(meal_plan_id,food_id));";
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create FoodPlanConnector table error: %s\n", error_message);
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
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "INSERT INTO User VALUES (%d, '%s', '%s', '%s', '%s', '%lld', '%s', '%s', '%s', '%s', %d);",
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
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "inser_user error: %s", error_message);
    }
}

void delete_user(User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "DELETE FROM User WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "delete_user error: %s", error_message);
        exit(1);
    }
}

void login_user(User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET login_logout = 1 WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "login_user error: %s", error_message);
        exit(1);
    }
}

void logout_user(User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET login_logout = 0 WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "logout_user error: %s", error_message);
        exit(1);
    }
}

// change user password 
void change_user_password(User* user, char* new_password) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET password = '%s' WHERE user_id = %d;", new_password, user->user_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "change_user_password error: %s", error_message);
        exit(1);
    }
}

// approve user 
void approve_user(User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET status = 'active' WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "approve_user error: %s", error_message);
        exit(1);
    }
}

// deactivate user
void deactivate_user(User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET status = 'deactive' WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "deactivate_user error: %s", error_message);
        exit(1);
    }
}

// charge user account  
void charge_user_account(User* user, int amount) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET balance = balance + %d WHERE user_id = %d;", amount, user->user_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "charge_user_account error: %s", error_message);
        exit(1);
    }
}

// reserve food
void reserve_food(Reserve* reserve) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "INSERT INTO Reserve VALUES (%d, %d, %lld, %d, %d);",
            reserve->reserve_id,
            reserve->self_id,
            reserve->date,
            reserve->meal,
            reserve->food_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "reserve_food error: %s", error_message);
        exit(1);
    }
}

// cancel reserve
void cancel_reserve(Reserve* reserve) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "DELETE FROM Reserve WHERE reserve_id = %d;", reserve->reserve_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "cancel_reserve error: %s", error_message);
        exit(1);
    }
}



// show user's reserve
void show_user_reserve(User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "SELECT * FROM Reserve WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "show_user_reserve error: %s", error_message);
        exit(1);
    }
}

void select_user_by_id_and_password(User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "SELECT * FROM User WHERE user_id = %d AND password = '%s';", user->user_id, user->password);
    rc = sqlite3_exec(db, query, callback_get_student, user, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "select_user_by_id_and_password error: %s", error_message);
        exit(1);
    }
}

#endif