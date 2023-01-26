#ifndef CALLBACK_H
#define CALLBACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"



int callback_get_student(void* _user, int argc, char** argv, char** azColName) {
    if (argc != 11) {
        fprintf(stderr, "callback_get_student error: argc != 11");
        exit(1);
    }
    
    User* user = (User*)_user;
    user->user_id = atoi(argv[0]);
    user->name = strdup(argv[1]);
    user->family = strdup(argv[2]);
    user->password = strdup(argv[3]);
    user->nation_id_code = strdup(argv[4]);
    user->birthdate = atoll(argv[5]);
    user->gender = strdup(argv[6]);
    user->type = strdup(argv[7]);
    user->status = strdup(argv[8]);
    user->login_logout = strdup(argv[9]);
    user->balance = atoi(argv[10]);
    return 0;
}

#endif