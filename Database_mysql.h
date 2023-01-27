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
#include "TimeLimit.h"
#include "News.h"
#include "Meal.h"
#include "MealFoodConnector.h"
#include "MealPlan.h"

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
	"name	TEXT NOT NULL,"\
	"type	TEXT NOT NULL,"\
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
    "is_open     BOOLEAN," \
    "PRIMARY KEY(self_id));";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void create_reserve_table() {
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS Reserve (" \
    "reserve_id	INTEGER NOT NULL AUTO_INCREMENT," \
    "user_id	INTEGER NOT NULL," \
    "meal_plan_id	INTEGER NOT NULL," \
    "date	INTEGER," \
    "status	TEXT," \
    "agent_id	INTEGER," \
    "UNIQUE INDEX(user_id, meal_plan_id)," \
    "PRIMARY KEY(reserve_id));";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void create_news_table() {
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS News (" \
    "news_id	INTEGER NOT NULL AUTO_INCREMENT," \
    "title	TEXT," \
    "content	TEXT," \
    "start_date	INTEGER," \
    "end_date	INTEGER," \
    "author_id	INTEGER," \
    "PRIMARY KEY(news_id));";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void create_meal_plan_table() {
    char query[MAX_QUERY_SIZE] = "CREATE TABLE IF NOT EXISTS MealPlan (" \
    "meal_plan_id	INTEGER NOT NULL AUTO_INCREMENT," \
    "self_id	INTEGER NOT NULL," \
    "food_id	INTEGER NOT NULL," \
    "date	INTEGER," \
    "count	INTEGER," \
    "PRIMARY KEY(meal_plan_id));";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}


void create_tables() {
    create_user_table();
    create_food_table();
    create_Self_table();
    create_reserve_table();
    create_news_table();
    create_meal_plan_table();
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

// ------------------ Self ------------------ //

// insert self to database
void insert_self(Self* self) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "INSERT INTO Self VALUES (%d, '%s', '%s', %d, '%s', '%s', %lld, %lld, %lld, %lld, %d);",
            self->self_id,
            self->name,
            self->location,
            self->capacity,
            self->type,
            self->meal,
            self->lunch_time_limit.start_time,
            self->lunch_time_limit.end_time,
            self->dinner_time_limit.start_time,
            self->dinner_time_limit.end_time,
            self->is_open);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void delete_self(Self* self) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "DELETE FROM Self WHERE self_id = %d;", self->self_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// ------------------ News ------------------ //

void insert_news(News* news) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "INSERT INTO News VALUES (%s, '%s', '%s', %lld, %lld, %d)",
            "NULL",
            news->title,
            news->content,
            news->time_limit.start_time,
            news->time_limit.end_time,
            news->user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void delete_news(News* news) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "DELETE FROM News WHERE news_id = %d;", news->news_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// ------------------ Meal ------------------ //

void insert_meal(Meal* meal) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "INSERT INTO Meal VALUES (%s, '%s')",
            "NULL",
            meal->name);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void delete_meal(Meal* meal) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "DELETE FROM Meal WHERE meal_id = %d;", meal->meal_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// ------------------ meal food connector ------------------ //

void insert_meal_food_connector(MealFoodConnector* meal_food_connector) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "INSERT INTO MealFoodConnector VALUES (%s, %d, %d);",
            "NULL",
            meal_food_connector->meal->meal_id,
            meal_food_connector->food->food_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void delete_meal_food_connector(MealFoodConnector* meal_food_connector) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "DELETE FROM MealFoodConnector WHERE meal_food_connector_id = %d;", meal_food_connector->connector_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// ------------------ Meal Plan ------------------ //

void insert_meal_plan(MealPlan* meal_plan) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "INSERT INTO MealPlan VALUES (%s, %d, %d, %lld, %d)",
            "NULL",
            meal_plan->self->self_id,
            meal_plan->food->food_id,
            meal_plan->date,
            meal_plan->count);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

void delete_meal_plan(MealPlan* meal_plan) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "DELETE FROM MealPlan WHERE meal_plan_id = %d;", meal_plan->meal_plan_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

bool select_meal_plan_by_id(MealPlan* meal_plan) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "SELECT * FROM MealPlan WHERE meal_plan_id = %d;", meal_plan->meal_plan_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        // meal_plan->self = select_self_by_id(atoi(row[1]));
        // meal_plan->food = select_food_by_id(atoi(row[2]));
        meal_plan->date = atoll(row[3]);
        meal_plan->count = atoi(row[4]);
        return true;
    }
    return false;
}

void update_meal_plan_count(MealPlan* meal_plan) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "UPDATE MealPlan SET count = %d WHERE meal_plan_id = %d;",
            meal_plan->count,
            meal_plan->meal_plan_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}


// ------------------ Reserve ------------------ //
void insert_reserve(Reserve* reserve) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "INSERT IGNORE INTO Reserve VALUES (%s, %d, %d, %lld, '%s', %s);",
            "NULL",
            reserve->user->user_id,
            reserve->meal_plan->meal_plan_id,
            reserve->date,
            reserve->status,
            "NULL");
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// cancel reserve
void delete_reserve(Reserve* reserve) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "DELETE FROM Reserve WHERE reserve_id = %d;", reserve->reserve_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
}

// ------------------ Selects ------------------ //

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

void select_deactive_users() {
    char query[MAX_QUERY_SIZE] = "SELECT * FROM User WHERE status = 'deactive';";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    print_select_result(*result);
}

bool select_public_info_of_user(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "SELECT user_id, name, family, balance, gender FROM User WHERE user_id = %d;", user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_all_foods() {
    char query[MAX_QUERY_SIZE] = "SELECT * FROM Food;";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_all_meals() {
    char query[MAX_QUERY_SIZE] = "SELECT * FROM Meal;";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_all_selfs() {
    char query[MAX_QUERY_SIZE] = "SELECT * FROM Self;";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_self_by_id(Self* self) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "SELECT * FROM Self WHERE self_id = %d;", self->self_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_food_by_id(Food* food) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "SELECT * FROM Food WHERE food_id = %d;", food->food_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_all_students() {
    char query[MAX_QUERY_SIZE] = "SELECT * FROM User WHERE type = 'student';";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_all_admins() {
    char query[MAX_QUERY_SIZE] = "SELECT * FROM User WHERE type = 'admin';";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_user_by_id(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "SELECT * FROM User WHERE user_id = %d;", user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_all_news() {
    char query[MAX_QUERY_SIZE] = "SELECT * FROM News;";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_all_meal_plans() {
    char query[MAX_QUERY_SIZE] = "SELECT * FROM MealPlan;";
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_selfs_with_same_genser(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "SELECT * FROM Self WHERE type Like '%c%%';", user->gender[0]);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_self_meal_plans_to_student(Self* self) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "SELECT MealPlan.meal_plan_id, Food.name, Food.price, MealPlan.count, Food.type FROM MealPlan JOIN Food ON MealPlan.food_id = Food.food_id WHERE MealPlan.self_id = %d;", self->self_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

bool select_reserve_by_user_id(User* user) {
    char query[MAX_QUERY_SIZE];
    sprintf(query, "SELECT * FROM Reserve WHERE user_id = %d;", user->user_id);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    if (mysql_num_rows(result) == 0) {
        return false;
    }
    print_select_result(*result);
    return true;
}

#endif