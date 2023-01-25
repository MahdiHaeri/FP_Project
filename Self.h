#ifndef SELF_H
#define SELF_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

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
    char* type;
};

#endif