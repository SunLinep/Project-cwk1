#include "book_management.h"
#include "user.h"

#ifndef MAIN_C_BOOKS_H
#define MAIN_C_BOOKS_H

void initlibrary(user *userfirst, char *books, char *users, FILE *fp);

void removenewline(char *content);

int checkcontent(char *content);

int typeoption(int num, char *choices);

void displayall(void);

void displayborrowed(user* user1);

void displaysearch(BookList books);

int search(void);

#endif
