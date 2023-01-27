#ifndef TIME_LIMIT_H
#define TIME_LIMIT_H

#include <stdio.h>

typedef struct TimeLimit TimeLimit;

struct TimeLimit {
    long long int time_start;
    long long int time_end;
};

#endif