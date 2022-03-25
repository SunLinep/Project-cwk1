#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"
#include "user.h"
#include "book_management.h"

int mainmenu(user *userfirst);

int librarianmenu(void);

int usermenu(char* name, user* user1);

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
        i = login(userfirst, name, pass);
        if(i == 0){
            printf("\nThe entered username is incorrect\n!");
            return 1;
        }else if(i == 1){
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
            while(librarianmenu() == 1);
            return 1;
        }else if(i == 3) {
            printf("\nThe entered password is incorrect!\n");
            return 1;
        }
        else if(i == 2){
fp = fopen("book.txt", "r");
            load_books(fp);
            while(usermenu(name,userfirst) == 1);
            return 1;
        }
    }
    else if(option == 3){
        fp = fopen("book.txt", "r");
        load_books(fp);
        fclose(fp);
        int h;
        while(1){
            h = search();
            if(h == 1){
                printf("The query is successful\n");
            }else if(h == 2){
                printf("There is no book\n");
            }else break;
        }
        return 1;
    }
    else if (option == 4){
        fp = fopen("book.txt","r");
        load_books(fp);
        fclose(fp);
        displayall();
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
        getchar();
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
    if(option == 1){
        char content[100];
        Book addbook;
        printf("\nEnter book's title: ");
        gets(content);
        addbook.title = (char *) malloc(sizeof content);
        strcpy(addbook.title, content);
        printf("Enter book's author: ");
        gets(content);
        addbook.authors = (char *) malloc(sizeof content);
        strcpy(addbook.authors, content);
        printf("Enter book's year: ");
        scanf("%d",&i);
        addbook.year = i;
        printf("Enter book's copies: ");
        scanf("%d",&i);
        addbook.copies = i;
        getchar();
        i = add_book(addbook);
        if(i==1){
            printf("\nSorry, the book already exists\n");
        }else if(i == 0){
            printf("Add book successfully\n");
        }
    }
    else if(option == 2){
        int a, h = 1;
        char content[100];
        Book *q = bookfirst;
        Book removebook;
        printf("\nEnter book's id: ");
        scanf("%d",&a);
        while(q){
            if(h == a){
                removebook.title = (char *) malloc(sizeof q->title);
                strcpy(removebook.title, q->title);
                removebook.authors = (char *) malloc(sizeof q->authors);
                strcpy(removebook.authors, q->authors);
                break;
            }
            q = q->next;
            h++;
        }
        i = remove_book(removebook);
        if(i==0){
            printf("\nSorry, this book doesn't exist\n");
        }else{
            q = bookfirst;
            fp = fopen("book.txt","w");
            while(q){
                printf("%s\n%s\n%d\n%d\n",q->title,q->authors,q->year,q->copies);
                fprintf(fp,"%s\n%s\n%d\n%d\n",q->title,q->authors,q->year,q->copies);
                q = q->next;
            }
            fclose(fp);
            printf("The book has been successfully deleted");
        }
    }
    else if(option == 3){
        fp = fopen("book.txt", "r");
        load_books(fp);
        int h;
        while(1){
            h = search();
            if(h == 1){
                printf("The query is successful\n");
            }else if(h == 2){
                printf("There is no book\n");
            }else break;
        }
        return 1;
    }
    else if (option == 4){
        fp = fopen("book.txt","r");
        load_books(fp);
        displayall();
        return 1;
    }
    else if(option == 5){
        printf("\nLogging out...\n");
        return 0;
    }
    return 1;
}

int usermenu(char* name, user* user1){
    FILE* fp;
    int option, i;
    printf("\n(logged in as: %s)\nPlease choose an option:\n1) Borrow a book\n2) Return a book\n3) Search for books\n4) Display all books\n5) log out\n Option:",name);
    do{
        i = scanf("%d", &option);
        getchar();
        if(i != 1 && option != 1 && option != 2 && option != 3 && option != 4 && option != 5) {
            printf("\nSorry, the option you entered was invalid, please try again.\n");
            printf("\n(logged in as: %s)\nPlease choose an option:\n1) Borrow a book\n2) Return a book\n3) Search for books\n4) Display all books\n5) log out\n Option:",name);
            fflush(stdin);
            continue;
        }else {
            if(option == 1 || option == 2 || option == 3 || option == 4 || option == 5) break;
            else{
                printf("\nSorry, the option you entered was invalid, please try again.\n");
                printf("\n(logged in as: %s)\nPlease choose an option:\n1) Borrow a book\n2) Return a book\n3) Search for books\n4) Display all books\n5) log out\n Option:",name);
                fflush(stdin);
                continue;
            }
        }
    }while(1);
    if(option == 1){
        printf("Enter the ID number of book you wish to borrow: ");
        int a, i = 1;
        scanf("%d",&a);
        Book *h = (Book*) malloc(sizeof h);
        Book *q = bookfirst;
        while(i != a){
            q = q->next;
            i++;
        }
        h->title = (char*) malloc(sizeof q->title);
        h->authors = (char *) malloc(sizeof q->authors);
	strcpy(h->title, q->title);
	strcpy(h->authors, q->authors);
        a = borrow(name, user1, h);
        if(a == 1) {
            printf("There is no such book in the library\n");
        }else if(a == 2){
            printf("You have borrowed the book\n");
        }else if(a == 3){
            printf("This book has been checked out\n");
        }else if(a == 0){
            printf("You have successfully borrowed the book!\n");
        }
        return  1;
    }
    else if(option == 2);
    else if(option == 3){
        fp = fopen("book.txt", "r");
        load_books(fp);
        int h;
        while(1){
            h = search();
            if(h == 1){
                printf("The query is successful\n");
            }else if(h == 2){
                printf("There is no book\n");
            }else break;
        }
        return 1;
    }
    else if (option == 4){
        fp = fopen("book.txt","r");
        load_books(fp);
        displayall();
        return 1;
    }
    else if(option == 5) {
        printf("\nLogging out...\n");
        return 0;
    }
    return 1;
}
