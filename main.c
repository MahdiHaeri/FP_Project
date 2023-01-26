#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "Controller.h"
#include "View.h"
#include "User.h"
#include "Reserve.h"
#include "Food.h"
#include "Self.h"
#include "DatabaseCommand.h"
#include "Database.h"


int main(int argc, char const *argv[]) {
    // init database
    init_database();

    handel_main_menu();
    return 0;
}
