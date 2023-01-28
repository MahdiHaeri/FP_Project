#include <stdio.h>
#include <stdlib.h>
// #include <sqlite3.h>
#include <string.h>
#include "Controller.h"
#include "View.h"
#include "User.h"
#include "Reserve.h"
#include "Food.h"
#include "Self.h"
#include "DatabaseCommand.h"
#include "Database_mysql.h"


int main(int argc, char const *argv[]) {
    // init database
    init_database();
    User user = {"admin", "admin", 1, "admin", "admin", 0, "admin", "admin", "active", "logout", 0};
    insert_user(&user);
    printf("Welcome to the restaurant reservation system\n");
    handle_main_menu();
    return 0;
}
