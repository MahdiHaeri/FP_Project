#ifndef RESERVE_H
#define RESERVE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

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
    int self_id;
    long long int date;
    int meal;
    int food_id;
};

#endif