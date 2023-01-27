#ifndef TIME_LIMIT_H
#define TIME_LIMIT_H

#include <stdio.h>

typedef struct TimeLimit TimeLimit;

struct TimeLimit {
    long long int start_time;
    long long int end_time;
};

#endif