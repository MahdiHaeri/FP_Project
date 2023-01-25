#ifndef FOOD_H
#define FOOD_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct Food Food;

// char query[MAX_QUERY_SIZE] = "CREATE TABLE 'Reserve' (" \
// "'reserve_id'	INTEGER NOT NULL," \
// "'self_id'	INTEGER NOT NULL," \
// "'date'	INTEGER," \
// "'meal'	INTEGER," \
// "'food_id'	INTEGER NOT NULL," \
// "PRIMARY KEY('reserve_id' AUTOINCREMENT)";

struct Food {
    int food_id;
    char* name;
    char* type;
    int price;
};

#endif