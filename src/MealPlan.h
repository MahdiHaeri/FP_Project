#ifndef MEALPLAN_H
#define MEALPLAN_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "Food.h"
#include "Self.h"

typedef struct MealPlan MealPlan;

struct MealPlan {
    int meal_plan_id;
    Food* food;
    Self* self;
    long long int date;
    int count;
};

#endif