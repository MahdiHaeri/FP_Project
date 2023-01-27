#ifndef MEALFOODCONNECTOR_H
#define MEALFOODCONNECTOR_H


#include "Meal.h"
#include "Food.h"


typedef struct MealFoodConnector MealFoodConnector;

struct MealFoodConnector {
    int connector_id;
    Meal* meal;
    Food* food;
};

#endif