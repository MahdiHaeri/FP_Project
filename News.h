#ifndef NEWS_H
#define NEWS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TimeLimit.h"

typedef struct News News;

struct News {
    int news_id;
    char *title;
    char *content;
    TimeLimit time_limit;
    User *user;
};

#endif