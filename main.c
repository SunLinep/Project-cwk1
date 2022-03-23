#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"
#include "user.h"
#include "book_management.h"

int mainmenu(user *userfirst);

int librarianmenu(void);

int usermenu(char* name);

int main(void){
    user *user1 = (user*)malloc(sizeof user1);
    user1->next = NULL;
	bookfirst = (Book*)malloc(sizeof bookfirst);
    while(mainmenu(user1) == 1);
    return 0;
}

int mainmenu(user *userfirst){
    FILE *fp;
    user* user2=(user*) malloc(sizeof user2);
    int option, i;
    if((fp = fopen("user.txt", "r")) ==NULL){
        fp = fopen("user.txt", "w");
        fprintf(fp,"librarian\nlibrarian\n");
        fclose(fp);
    }else if((user2 = loaduser(userfirst, fp)) == NULL) {
        user* user2=(user*) malloc(sizeof user2);
        fclose(fp);
        fp = fopen("user.txt", "w");
        fprintf(fp, "librarian\nlibrarian\n");
        fclose(fp);
        fp = fopen("user.txt", "r");
        userfirst = loaduser(userfirst, fp);
        fclose(fp);
    }else{
        userfirst = loaduser(userfirst, fp);
        fclose(fp);
    }
    printf("\nPlease choose an option:\n1) Register an account\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:");
    do{
        i = scanf("%d", &option);
        if(i != 1 && option != 1 && option != 2 && option != 3 && option != 4 && option != 5) {
            printf("\nSorry, the option you entered was invalid, please try again.\n");
            printf("\nPlease choose an option:\n1) Register an account\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:");
            fflush(stdin);
            continue;
        }else {
            if(option == 1 || option == 2 || option == 3 || option == 4 || option == 5) break;
            else{
                printf("\nSorry, the option you entered was invalid, please try again.\n");
                printf("\nPlease choose an option:\n1) Register an account\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:");
                fflush(stdin);
                continue;
            }
        }
    }while(1);
    if(option == 1){
        if((user2= regist(userfirst)) == NULL){
            user2=(user*) malloc(sizeof user2);
            printf("\nSorry, registration unsuccessful, the username you entered already exists\n");
            fp = fopen("user.txt", "r");
            userfirst = loaduser(userfirst, fp);
            fclose(fp);
        }else{
            userfirst = user2;
            printf("\nRegistered library account successfully!\n");
        }
        return 1;
    }
    else if(option == 2){
        char name[100];
        char pass[100];
        char a;
        printf("\nPlease enter a username: ");
        scanf("%s",name);
        getchar();
        printf("Please enter a password: ");
        scanf("%s",pass);
        getchar();
        if(login(userfirst, name, pass) == 0){
            printf("\nThe entered username is incorrect\n!");
            return 1;
        }else if(login(userfirst, name, pass) == 1){
            if((fp = fopen("book.txt", "r")) == NULL){
                fp = fopen("book.txt", "w");
                store_books(fp);
                fclose(fp);
            }else{
                a = fgetc(fp);
                if(a == EOF){
                    fclose(fp);
                    fp = fopen("book.txt", "w");
                    store_books(fp);
                    fclose(fp);
                }
            }
            fp = fopen("book.txt", "r");
            load_books(fp);
            fclose(fp);
            while(librarianmenu() == 1);
            return 1;
        }else if(login(userfirst, name, pass) == 3) {
            printf("\nThe entered password is incorrect!\n");
            return 1;
        }
        else if(login(userfirst, name, pass) == 2){
            while(usermenu(name) == 1);
            return 1;
        }
    }
    else if(option == 3){
        fp = fopen("book.txt", "r");
        load_books(fp);
        fclose(fp);
        while(search() == 1);
        return 1;
    }
    else if (option == 4){
        fp = fopen("book.txt","r");
        load_books(fp);
        fclose(fp);
        displayall(bookfirst);
        return 1;
    }
    else if(option == 5){
        return 0;
    }
}

int librarianmenu(void){
FILE*fp;
    int option, i;
    printf("\n(logged in as: librarian)\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:");
    do{
        i = scanf("%d", &option);
        if(i != 1 && option != 1 && option != 2 && option != 3 && option != 4 && option != 5) {
            printf("\nSorry, the option you entered was invalid, please try again.\n");
            printf("\n(logged in as: librarian)\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:");
            fflush(stdin);
            continue;
        }else {
            if(option == 1 || option == 2 || option == 3 || option == 4 || option == 5) break;
            else{
                printf("\nSorry, the option you entered was invalid, please try again.\n");
                printf("\n(logged in as: librarian)\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:");
                fflush(stdin);
                continue;
            }
        }
    }while(1);
    if(option == 1);
    else if(option == 2);
    else if(option == 3);
    else if (option == 4){
fp = fopen("book.txt","r");
load_books(fp);
fclose(fp);
        displayall(bookfirst);
    }
    else if(option == 5){
        printf("\nLogging out...\n");
        return 0;
    }
    return 1;
}

int usermenu(char* name){
    int option;
    printf("\n(logged in as: %s)\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:",name);
    while(scanf("%d",&option) != 1){
        if(option >=1 && option <= 5) break;
        printf("\nSorry, the option you entered was invalid, please try again.\n");
        printf("\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:");
        fflush(stdin);
    }
    if(option == 1);
    else if(option == 2);
    else if(option == 3);
    else if(option == 4);
    else if(option == 5) {
        printf("\nLogging out...\n");
        return 0;
    }
    return 1;
}
