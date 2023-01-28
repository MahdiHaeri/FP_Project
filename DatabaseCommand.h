#ifndef DATABASECOMMAND_H
#define DATABASECOMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// #include <sqlite3.h>
#include "User.h"
#include "Reserve.h"
#include "Food.h"
#include "Self.h"
#include "Database_mysql.h"
#include "Controller.h"
#include "TimeLimit.h"
#include "News.h"
#include "MealPlan.h"

void handle_student_login_menu();
void handle_admin_login_menu();  


#define MAX_QUERY_SIZE 1000
#define MAX_ARRAY_SIZE 100
#define LOGIN 1
#define LOGOUT 0

typedef long long int llint;

User* current_user;
llint* current_time;

llint get_current_time() {
    return 0;
}

void get_line(char* line) {
    fgets(line, MAX_ARRAY_SIZE, stdin);
    line[strlen(line) - 1] = '\0';
}

// ----------------- Show -----------------

void show_students_table_command() {
    if (!select_all_students()) {
        printf("There is no student!\n");
    }
}

void show_news_table_command() {
    if (!select_all_news()) {
        printf("There is no news!\n");
    }
}

void show_foods_table_command() {
    if (!select_all_foods()) {
        printf("There is no food!\n");
    }
}

void show_selfs_table_command() {
    if (!select_all_selfs()) {
        printf("There is no self!\n");
    }
}

void show_meal_plans_table_command() {
    if (!select_all_meal_plans()) {
        printf("There is no meal plan!\n");
    }
}

void show_admins_table_command() {
    if (!select_all_admins()) {
        printf("There is no admin!\n");
    }
}

void show_profile_command() {
    if (!select_user_by_id(current_user)) {
        printf("There is no user with id %d!\n", current_user->user_id);
        return;
    }
}

void show_reserve_command() {
    if (!select_reserve_by_user_id(current_user)) {
        printf("There is no reserve for this user!\n");
    }
}

// ----------------- User -----------------

void register_user_command(char* user_type, char* user_status) {
    // define variables
    char name[MAX_ARRAY_SIZE];
    char family[MAX_ARRAY_SIZE];
    int user_id;
    char password[MAX_ARRAY_SIZE];
    char nation_id_code[MAX_ARRAY_SIZE];
    long long int birth_date;
    char gender[MAX_ARRAY_SIZE];
    char login_status[MAX_ARRAY_SIZE] = "logout";
    int balance = 0;

    // get input
    printf("Enter your name: ");
    getchar();
    get_line(name);
    printf("Enter your family: ");
    get_line(family);
    printf("Enter your user id: ");
    scanf("%d", &user_id);
    printf("Enter your password: ");
    scanf(" %s", password);
    printf("Enter your nation id code: ");
    scanf(" %s", nation_id_code);
    printf("Enter your birth date: ");
    scanf("%lld", &birth_date);
    printf("Enter your gender: ");
    scanf(" %s", gender);
    
    // create user
    User new_user;
    new_user.name = name;
    new_user.family = family;
    new_user.user_id = user_id;
    new_user.password = password;
    new_user.nation_id_code = nation_id_code;
    new_user.birthdate = birth_date;
    new_user.gender = gender;
    new_user.type = user_type;
    new_user.status = user_status;
    new_user.login_logout = login_status;
    new_user.balance = balance;
    
    // insert user to database
    insert_user(&new_user);
}

void login_user_command() {
    User* user = (User*)malloc(sizeof(User));
    user_constructor(user);
    printf("Enter your user id: ");
    scanf("%d", &user->user_id);
    printf("Enter your password: ");
    scanf(" %s", user->password);


    if (select_user_by_id_and_password(user)) {
        printf("User found!\n");
    } else {
        printf("User not found, your user id or password is not correct!\n");
        return;
    }

    if (strcmp(user->status, "active") != 0) {
        printf("Your account is not active!\n");
    } else {
        if (strcmp(user->login_logout, "login") == 0) {
            printf("You are already logged in!\n");
            return;
        } else {
            current_user = user;
            user->login_logout = "login";
            login_user(user);
            if (strcmp(user->type, "student") == 0) {
                printf("Welcome student!\n");
                handle_student_login_menu();
            } else if (strcmp(user->type, "admin") == 0) {
                printf("Welcome admin!\n");
                handle_admin_login_menu();
            }
        }
    }
}

void logout_user_command() {
    if (strcmp(current_user->login_logout, "logout") == 0) {
        printf("You are already logged out!\n");
    } else {
        current_user->login_logout = "logout";
        logout_user(current_user);
        current_user = NULL;
    }
}

void delete_user_command() {
    int user_id;
    printf("Which one of the user you want to delete?\n");
    printf("Enter user id : ");
    scanf("%d", &user_id);
    printf("Are you sure you want to delete user with id %d? (y/n): ", user_id);
    char answer;
    scanf(" %c", &answer);
    if (answer == 'n') {
        return;
    }
    User user;
    user.user_id = user_id;
    delete_user(&user);
}

void change_pass_with_admi_command() {
    int user_id;
    char new_password[MAX_ARRAY_SIZE];
    printf("Whose password do you want to change?\n");
    printf("Enter user id: ");
    scanf("%d", &user_id);
    printf("Please enter new password for user with id %d: ", user_id);
    scanf(" %s", new_password);

    User user;
    user.user_id = user_id;
    change_user_password(&user, new_password);
}

void change_current_user_password_command() {
    char old_password[MAX_ARRAY_SIZE];
    char new_password[MAX_ARRAY_SIZE];
    printf("Please enter your old password: ");
    scanf(" %s", old_password);
    if (strcmp(old_password, current_user->password) != 0) {
        printf("Your old password is not correct!\n");
        return;
    }
    printf("Please enter your new password: ");
    scanf(" %s", new_password);
    change_user_password(current_user, new_password);
    strcpy(current_user->password, new_password);
}

void approve_user_command() {
    select_deactive_users();
    int user_id;
    printf("Whose User do you want to approve?\n");
    printf("Enter User id: ");
    scanf("%d", &user_id);

    User user;
    user.user_id = user_id;
    approve_user(&user);
}

void deactivate_user_command() {
    int user_id;
    printf("Whose User do you want to deactive?\n");
    printf("Enter User id: ");
    scanf("%d", &user_id);

    User user;
    user.user_id = user_id;
    deactivate_user(&user);
}

void charge_user_account_with_admin_command() {
    int user_id;
    int amount;
    printf("Whose User do you want to charge?\n");
    printf("Enter User id: ");
    scanf("%d", &user_id);
    printf("Enter amount: ");
    scanf("%d", &amount);

    User user;
    user.user_id = user_id;
    charge_user_account(&user, amount);
}

void charge_current_user_account_command() {
    int amount;
    char card_number[MAX_ARRAY_SIZE];
    char card_password[MAX_ARRAY_SIZE];
    printf("Enter amount: ");
    scanf("%d", &amount);
    printf("Enter card number: ");
    scanf(" %s", card_number);
    printf("Enter card password: ");
    scanf(" %s", card_password);

    charge_user_account(current_user, amount);
    current_user->balance += amount;
}

// ----------------- Food -----------------

void define_food_command() {
    int food_id;
    char name[MAX_ARRAY_SIZE];
    int price;
    char type[MAX_ARRAY_SIZE];

    printf("Enter food id: ");
    scanf("%d", &food_id);
    printf("Enter food name: ");
    getchar();
    get_line(name);
    printf("Enter food price: ");
    scanf("%d", &price);
    printf("Enter food type: ");
    scanf(" %s", type);

    Food food;
    food.food_id = food_id;
    food.name = name;
    food.price = price;
    food.type = type;

    insert_food(&food);
}

void delete_food_command() {
    int food_id;
    printf("Which one of the food you want to delete?\n");
    printf("Enter food id : ");
    scanf("%d", &food_id);
    printf("Are you sure you want to delete food with id %d? (y/n): ", food_id);
    char answer;
    scanf(" %c", &answer);
    if (answer == 'n') {
        return;
    }
    Food food;
    food.food_id = food_id;
    delete_food(&food);
}

void change_food_price_command() {
    int food_id;
    int new_price;
    printf("Which one of the food you want to change price?\n");
    printf("Enter food id : ");
    scanf("%d", &food_id);
    printf("Enter new price: ");
    scanf("%d", &new_price);

    Food food;
    food.food_id = food_id;
    change_food_price(&food, new_price);
}

void send_charge_command() {
    int user_id;
    int amount;


    printf("Whose user do you want send charge?\n");
    printf("Enter user id: ");
    scanf("%d", &user_id);
    if (user_id == current_user->user_id) {
        printf("You can't send charge to yourself!\n");
        return;
    }

    User user;
    user.user_id = user_id;
    
    if (!select_public_info_of_user(&user)) {
        printf("User with id %d doesn't exist!\n", user_id);
        return;
    }

    printf("Enter amount: ");
    scanf("%d", &amount);
    if (amount > current_user->balance) {
        printf("You don't have enough money!\n");
        return;
    }

    charge_user_account(&user, amount);
    charge_user_account(current_user, -amount);
    current_user->balance -= amount;
}

// ----------------- Self -----------------

void define_self_command() {
    int self_id;
    char name[MAX_ARRAY_SIZE];
    char location[MAX_ARRAY_SIZE];
    int capacity;
    char type[MAX_ARRAY_SIZE]; // boyish, girlish
    char meal[MAX_ARRAY_SIZE]; // lunch, dinner
    TimeLimit lunch_time_limit;
    TimeLimit dinner_time_limit;
    bool is_open = true;

    printf("Enter self id: ");
    scanf("%d", &self_id);
    printf("Enter self name: ");
    getchar();
    get_line(name);
    printf("Enter self location: ");
    get_line(location);
    printf("Enter self capacity: ");
    scanf("%d", &capacity);
    printf("Enter self type: ");
    scanf(" %s", type);
    printf("Enter self meal: ");
    scanf(" %s", meal);
    printf("Enter self lunch time limit: ");
    scanf("%lld %lld", &lunch_time_limit.start_time, &lunch_time_limit.end_time);
    printf("Enter self dinner time limit: ");
    scanf("%lld %lld", &dinner_time_limit.start_time, &dinner_time_limit.end_time);

    Self self;
    self.self_id = self_id;
    self.name = name;
    self.location = location;
    self.capacity = capacity;
    self.type = type;
    self.meal = meal;
    self.lunch_time_limit = lunch_time_limit;
    self.dinner_time_limit = dinner_time_limit;
    self.is_open = is_open;
    
    insert_self(&self);
}

void delete_self_command() {
    int self_id;
    printf("Which one of the self you want to delete?\n");
    printf("Enter self id : ");
    scanf("%d", &self_id);
    printf("Are you sure you want to delete self with id %d? (y/n): ", self_id);
    char answer;
    scanf(" %c", &answer);
    if (answer == 'n') {
        return;
    }
    Self self;
    self.self_id = self_id;
    delete_self(&self);
}

// ----------------- News -----------------

// add new news
void add_news_command() {
    char title[MAX_ARRAY_SIZE];
    char content[MAX_ARRAY_SIZE];
    TimeLimit time_limit;
    time_limit.start_time = get_current_time();

    printf("Enter news title: ");

    // get rid of newline
    getchar();
    get_line(title);    
    // get rid of newline
    printf("Enter news content: ");
    get_line(content);

    printf("Enter news end date: ");
    scanf("%lld", &time_limit.end_time);

    if (time_limit.end_time < time_limit.start_time) {
        printf("End date must be greater than start date!\n");
        return;
    }
    
    News news;
    news.title = title;
    news.content = content;
    news.time_limit = time_limit;
    news.user = current_user;

    insert_news(&news);
}

// delete news
void delete_news_command() {
    int news_id;
    printf("Which one of the news you want to delete?\n");
    printf("Enter news id : ");
    scanf("%d", &news_id);
    printf("Are you sure you want to delete news with id %d? (y/n): ", news_id);
    char answer;
    scanf(" %c", &answer);
    if (answer == 'n') {
        return;
    }
    News news;
    news.news_id = news_id;
    delete_news(&news);
}

// ----------------- meal plan -----------------

void define_meal_plan_command() {
    if (!select_all_selfs()) {
        printf("There is no self!\n");
        printf("Please define self first!\n");
        return;
    }

    if (!select_all_foods()) {
        printf("There is no food!\n");
        printf("Please define food first!\n");
        return;
    }

    int self_id;
    int food_id;
    long long int date;
    int count;
    
    printf("Enter self id: ");
    scanf("%d", &self_id);
    Self self;
    self.self_id = self_id;
    if (!select_self_by_id(&self)) {
        printf("There is no self with id %d!\n", self_id);
        return;
    }
    printf("Enter food id: ");
    scanf("%d", &food_id);
    Food food;
    food.food_id = food_id;
    if (!select_food_by_id(&food)) {
        printf("There is no food with id %d!\n", food_id);
        return;
    }
    printf("Enter date: ");
    scanf("%lld", &date);
    printf("Enter count: ");
    scanf("%d", &count);
    if (count < 0) {
        printf("Count must be greater than 0!\n");
        return;
    }

    MealPlan meal_plan;
    meal_plan.self = &self;
    meal_plan.food = &food;
    meal_plan.date = date;
    meal_plan.count = count;

    insert_meal_plan(&meal_plan);
}

void delete_meal_plan_command() {
    int meal_plan_id;
    printf("Which one of the meal plan you want to delete?\n");
    printf("Enter meal plan id : ");
    scanf("%d", &meal_plan_id);
    char answer;
    scanf(" %c", &answer);
    printf("Are you sure you want to delete meal plan with id %d? (y/n): ", meal_plan_id);
    if (answer == 'n') {
        return;
    }
    MealPlan meal_plan;
    meal_plan.meal_plan_id = meal_plan_id;
    delete_meal_plan(&meal_plan);
}

// ----------------- Reserve In Self -----------------

void reserve_in_self_command() {
    if (!select_selfs_with_same_genser(current_user)) {
        printf("There is no suitable self!\n");
        return;
    }
    int self_id;
    printf("Enter self id: ");
    scanf("%d", &self_id);
    Self self;
    self.self_id = self_id;
    if (!select_self_by_id(&self)) {
        printf("There is no self with id %d!\n", self_id);
        return;
    }
    if (!select_self_meal_plans_to_student(&self)) {
        printf("There is no meal plan in this self!\n");
        return;
    }
    int meal_plan_id;
    printf("Enter meal plan id: ");
    scanf("%d", &meal_plan_id);
    MealPlan meal_plan;
    meal_plan.meal_plan_id = meal_plan_id;
    if (!select_meal_plan_by_id(&meal_plan)) {
        printf("There is no meal plan with id %d!\n", meal_plan_id);
        return;
    }
    // if (meal_plan.self->self_id != self.self_id) {
    //     printf("There is no meal plan with id %d in this self!\n", meal_plan_id);
    //     return;
    // }
    if (meal_plan.count == 0) {
        printf("There is no food in this meal plan!\n");
        return;
    }
    meal_plan.count--;
    update_meal_plan_count(&meal_plan);
    Reserve reserve_in_self;
    reserve_in_self.user = current_user;
    reserve_in_self.meal_plan = &meal_plan;
    reserve_in_self.date = get_current_time();
    reserve_in_self.status = "Not Taken";
    reserve_in_self.agent = NULL;
    insert_reserve(&reserve_in_self);
}

void take_reserve_command() {
    if (!select_reserve_by_user_id(current_user)) {
        printf("There is no reserve!\n");
        return;
    }
    int reserve_id;
    printf("Enter reserve id: ");
    scanf("%d", &reserve_id);
    Reserve reserve;
    reserve.reserve_id = reserve_id;
    if (!select_reserve_by_id(&reserve)) {
        printf("There is no reserve with id %d!\n", reserve_id);
        return;
    }
    if (strcmp(reserve.status, "Taken") == 0) {
        printf("This reserve is already taken!\n");
        return;
    }
    reserve.status = "Taken";
    update_reserve_status(&reserve);
}

void cancel_reserve_command() {
    if (!select_reserve_by_user_id(current_user)) {
        printf("There is no reserve!\n");
        return;
    }
    int reserve_id;
    printf("Enter reserve id: ");
    scanf("%d", &reserve_id);
    Reserve reserve;
    reserve.reserve_id = reserve_id;
    if (!select_reserve_by_id(&reserve)) {
        printf("There is no reserve with id %d!\n", reserve_id);
        return;
    }
    if (strcmp(reserve.status, "Taken") == 0) {
        printf("This reserve is already taken and can not be canceled!\n");
        return;
    }
    // reserve.meal_plan->count++;
    // update_meal_plan_count(reserve.meal_plan);
    delete_reserve(&reserve);
}

void define_agent_command() {
    if (!select_reserve_by_user_id(current_user)) {
        printf("There is no reserve!\n");
        return;
    }
    int reserve_id;
    printf("Enter reserve id: ");
    scanf("%d", &reserve_id);
    Reserve reserve;
    reserve.reserve_id = reserve_id;
    if (!select_reserve_by_id(&reserve)) {
        printf("There is no reserve with id %d!\n", reserve_id);
        return;
    }
    int user_id;
    printf("Enter agent user id: ");
    scanf("%d", &user_id);
    User user;
    user.user_id = user_id;
    if (!select_public_info_of_user(&user)) {
        printf("There is no user with id %d!\n", user_id);
        return;
    }
    if (user.user_id == current_user->user_id) {
        printf("You can not define yourself as agent!\n");
        return;
    }
    char answer;
    printf("Are you sure you want to define user with id %d as agent? (y/n): ", user_id);
    scanf(" %c", &answer);
    if (answer == 'n') {
        return;
    }
    reserve.agent = &user;
    update_reserve_agent(&reserve);
}

void reserve_food_report_command() {
    if (!select_all_reserves()) {
        printf("There is no reserve!\n");
        return;
    }
}
#endif