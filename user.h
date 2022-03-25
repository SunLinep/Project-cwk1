#ifndef MAIN_C_USER_H
#define MAIN_C_USER_H
#include "book_management.h"
#include <stdio.h>

extern Book *bookfirst;

typedef struct User{
    char *username;
    char *password;
    struct _BookList *borrowed;
    struct User *next;
}user;

user *loaduser(user * user1, FILE* fp);

user *regist(user * user1);

int login(user* user1, char*name, char*pass);

int borrow(char* name, user* user1, Book*book);

#endif
