#ifndef RESERVE_H
#define RESERVE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "User.h"
#include "MealPlan.h"

typedef struct Reserve Reserve;

// char query[MAX_QUERY_SIZE] = "CREATE TABLE 'Reserve' (" \
// "'reserve_id'	INTEGER NOT NULL," \
// "'self_id'	INTEGER NOT NULL," \
// "'date'	INTEGER," \
// "'meal'	INTEGER," \
// "'food_id'	INTEGER NOT NULL," \
// "PRIMARY KEY('reserve_id' AUTOINCREMENT)";

struct Reserve {
    int reserve_id;
    User* user;
    MealPlan* meal_plan;
    long long int date;
    char* status;
    User* agent;
};

#endif