#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    // for (int i = 0; i < argc; i++) {
    //     printf("%-15s", azColName[i]);
    // }
    printf("\n----------------------------------\n");
    for (int i = 0; i < argc; i++) {
        printf("%-15s", argv[i]);
    } 
    printf("\n");
    return 0;
}

void open_database(sqlite3** db) {
    int rc;
    rc = sqlite3_open("./test.db", &(*db));
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
}

void create_student_table(sqlite3** db) {
    char* sqlite_error;
    char* sql;
    sql = "CREATE TABLE Student(" \
        "first_name NOT NULL," \
        "last_name NOT NULL," \
        "age" \
        ");";
    int rc;
    rc = sqlite3_exec(*db, sql, 0, 0, &sqlite_error);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL Error!: %s\n", sqlite_error);
        sqlite3_free(sqlite_error);
    } else {
        fprintf(stderr, "Create table successfully\n");
    }
}

void insert_student(sqlite3** db, char* first_name, char* last_name, int age) {
    char* sqlite_error;
    char sql[200];
    int rc;
    // INSERT INTO Student VALUES("ali", "najafi", 11);
    sprintf(sql, "INSERT INTO Student VALUES ('%s', '%s', %d);", first_name, last_name, age);
    rc = sqlite3_exec(*db, sql, NULL, NULL, &sqlite_error);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL Error!: %s\n", sqlite_error);
        sqlite3_free(sqlite_error);
    } else {
        fprintf(stderr, "insert student, first_name: %s, last_name: %s, age: %d", first_name, last_name, age);
    }
}

void select_all_student(sqlite3** db) {
    int rc;
    char* sql = "SELECT * FROM Student;";
    char* sqlite_error;
    rc = sqlite3_exec(*db, sql, callback, NULL, &sqlite_error);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL Error!: %s", sqlite_error);
        sqlite3_free(sqlite_error);
    } else {
        fprintf(stderr, "Select all student successfully");
    }
}

void update_age(sqlite3** db, char* first_name, char* last_name, int age) {
    char* sqlite_error;
    int rc;
    char sql[200];
    sprintf(sql, "UPDATE Student SET age = %d WHERE first_name = '%s' AND last_name = '%s';", age, first_name, last_name);
    rc = sqlite3_exec(*db, sql, callback, NULL, &sqlite_error);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL Error!: %s", sqlite_error);
        sqlite3_free(sqlite_error);
    } else {
        fprintf(stderr, "Select all student successfully");
    }
}

void incrase_age(sqlite3* db) {
    
}

int main(int argc, char const *argv[]) {
    sqlite3* db;

    open_database(&db);
    create_student_table(&db);
    char first_name[200];
    char last_name[200];
    int age;
    printf("please enter first name, last name, age: ");
    scanf("%s %s %d", first_name, last_name, &age);
    // printf("\n\n\n%s, %s, %d", first_name, last_name, age);
    // insert_student(&db, first_name, last_name, age);
    update_age(&db, first_name, last_name, age);
    sqlite3_close(db);
    return 0;
}
