#ifndef MEALPLAN_H
#define MEALPLAN_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct MealPlan MealPlan;

struct MealPlan {
    int meal_plan_id;
    int user_id;
    int food_id;
    int meal;
    long long int date;
    int price;
};

#endif