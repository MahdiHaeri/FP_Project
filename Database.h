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


#define MAX_QUERY_SIZE 1000
#define LOGIN 1
#define LOGOUT 0

struct Database {
    sqlite3* db;
    char* db_address;
};

void open_database(sqlite3** db, char* db_address) {
    int rc = sqlite3_open(db_address, db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s", sqlite3_errmsg(*db));
    }
}







// ----------------- CREATE TABLES -----------------

void create_food_table(sqlite3** db) {
    int rc;
    char* error_message;
    char query[MAX_QUERY_SIZE] = "CREATE TABLE 'Food' ("\
	"'food_id'	INTEGER NOT NULL,"\
	"'name'	INTEGER NOT NULL,"\
	"'type'	INTEGER NOT NULL,"\
	"'price '	INTEGER,"\
	"PRIMARY KEY('name');";
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create food table error: %s", error_message);
    }
}

void create_user_table(sqlite3** db) {
    int rc;
    char* error_message;
    char query[MAX_QUERY_SIZE] = "CREATE TABLE 'Reserve' (" \
	"'reserve_id'	INTEGER NOT NULL," \
	"'self_id'	INTEGER NOT NULL," \
	"'date'	INTEGER," \
	"'meal'	INTEGER," \
	"'food_id'	INTEGER NOT NULL," \
	"PRIMARY KEY('reserve_id' AUTOINCREMENT)";
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create user table error: %s", error_message);
    }
}

void create_Self_table(sqlite3** db) {
    int rc;
    char* error_message;
    char query[MAX_QUERY_SIZE] = "CREATE TABLE 'Self' (" \
    "'self_id'	INTEGER NOT NULL," \
    "'name'	TEXT," \
    "'location'	TEXT," \
    "'capacity '	INTEGER," \
    "'type'	TEXT," \
    "'meal'	TEXT," \
    "'lunch_start_time'	INTEGER," \
    "'lunch_end_time'	INTEGER," \
    "'dinner_start_time'	INTEGER," \
    "'dinner_finish_time'	INTEGER," \
    "PRIMARY KEY('self_id')";
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create Self table error: %s", error_message);
    }
}

void create_reserve_table(sqlite3** db) {
    int rc;
    char* error_message;
    char query[MAX_QUERY_SIZE] = "CREATE TABLE 'Reserve' (" \
    "'reserve_id'	INTEGER NOT NULL," \
    "'self_id'	INTEGER NOT NULL," \
    "'date'	INTEGER," \
    "'meal'	INTEGER," \
    "'food_id'	INTEGER NOT NULL," \
    "PRIMARY KEY('reserve_id' AUTOINCREMENT)";
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create reserve table error: %s", error_message);
    }
}

void create_meal_plan_table(sqlite3** db) {
    int rc;
    char* error_message;
    char query[MAX_QUERY_SIZE] = "CREATE TABLE 'MealPlan' (" \
    "'meal_id'	INTEGER NOT NULL," \
    "'self_id'	INTEGER NOT NULL," \
    "'type'	TEXT," \
    "'date'	INTEGER," \
    "PRIMARY KEY('meal_id')";
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create meal plan table error: %s", error_message);
    }
}

void create_food_plan_connector_table(sqlite3** db) {
    int rc;
    char* error_message;
    char query[MAX_QUERY_SIZE] = "CREATE TABLE 'FoodPlanConnector' (" \
    "'meal_plan_id'	INTEGER NOT NULL," \
    "'food_id'	INTEGER NOT NULL," \
    "'count'	INTEGER NOT NULL," \
    "PRIMARY KEY('meal_plan_id','food_id')";
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "create food plan connector table error: %s", error_message);
    }
}

void create_tables(sqlite3** db) {
    create_food_table(db);
    create_user_table(db);
    create_Self_table(db);
    create_reserve_table(db);
    create_meal_plan_table(db);
    create_food_plan_connector_table(db);
}









// ----------------------------------------------

void insert_user(sqlite3** db, User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "INSERT INTO User VALUSE (%d, '%s', '%s', '%s', %d, '%lld', '%s', '%s', '%s', %d);",
            user->user_id,
            user->name,
            user->family,
            user->password,
            user->nation_id_code,
            user->birthdate,
            user->gender,
            user->type,
            user->status,
            user->login_logout);
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "inser_user error: %s", error_message);
        exit(1);
    }
}

void delete_user(sqlite3** db, User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "DELETE FROM User WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "delete_user error: %s", error_message);
        exit(1);
    }
}

void login_user(sqlite3** db, User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET login_logout = 1 WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "login_user error: %s", error_message);
        exit(1);
    }
}

void logout_user(sqlite3** db, User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET login_logout = 0 WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "logout_user error: %s", error_message);
        exit(1);
    }
}

// change user password 
void change_user_password(sqlite3** db, User* user, char* new_password) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET password = '%s' WHERE user_id = %d;", new_password, user->user_id);
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "change_user_password error: %s", error_message);
        exit(1);
    }
}

// approve user 
void approve_user(sqlite3** db, User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET status = 'approved' WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "approve_user error: %s", error_message);
        exit(1);
    }
}

// deactivate user
void deactivate_user(sqlite3** db, User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET status = 'deactivated' WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "deactivate_user error: %s", error_message);
        exit(1);
    }
}

// charge user account  
void charge_user_account(sqlite3** db, User* user, int amount) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "UPDATE User SET balance = balance + %d WHERE user_id = %d;", amount, user->user_id);
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "charge_user_account error: %s", error_message);
        exit(1);
    }
}

// reserve food
void reserve_food(sqlite3** db, Reserve* reserve) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "INSERT INTO Reserve VALUES (%d, %d, %lld, %d, %d);",
            reserve->reserve_id,
            reserve->self_id,
            reserve->date,
            reserve->meal,
            reserve->food_id);
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "reserve_food error: %s", error_message);
        exit(1);
    }
}

// cancel reserve
void cancel_reserve(sqlite3** db, Reserve* reserve) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "DELETE FROM Reserve WHERE reserve_id = %d;", reserve->reserve_id);
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "cancel_reserve error: %s", error_message);
        exit(1);
    }
}



// show user's reserve
void show_user_reserve(sqlite3** db, User* user) {
    int rc;
    char query[MAX_QUERY_SIZE];
    char* error_message;
    sprintf(query, "SELECT * FROM Reserve WHERE user_id = %d;", user->user_id);
    rc = sqlite3_exec(*db, query, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "show_user_reserve error: %s", error_message);
        exit(1);
    }
}




#endif