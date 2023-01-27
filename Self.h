#ifndef SELF_H
#define SELF_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "TimeLimit.h"

typedef struct Self Self;

// char query[MAX_QUERY_SIZE] = "CREATE TABLE 'Reserve' (" \
// "'reserve_id'	INTEGER NOT NULL," \
// "'self_id'	INTEGER NOT NULL," \
// "'date'	INTEGER," \
// "'meal'	INTEGER," \
// "'food_id'	INTEGER NOT NULL," \
// "PRIMARY KEY('reserve_id' AUTOINCREMENT)";

struct Self {
    int self_id;
    char* name;
    char* location;
    int capacity;
    char* type; // boyish or girlish
    char* meal; // lunch or dinner
    TimeLimit lunch_time_limit;
    TimeLimit dinner_time_limit;
    bool is_open;
};

#endif