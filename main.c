#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_management.h"

typedef struct users{
	char username[100];
	char password[100];
    struct users *next;
}User;

extern Book * bookfirst;
User * userfirst;
char *bookfilename = "bookfile.txt";
char *userfilename = "users.txt";

void loaduserlist(char *userfile);

void displayBooks(char *bookfile);

void registeruser(char *userfile);

int mainMenu();

void searchbook(char *user);

void login_librarian(void);

void login_user(char *name);

void login(User *user);

int main(void){
    bookfirst = (Book*)malloc(sizeof bookfirst);
    bookfirst->next = NULL;
    userfirst = (User*) malloc(sizeof userfirst);
    strcpy(userfirst->username ,"librarian");
    strcpy( userfirst->password ,"librarian");
    userfirst->next = NULL;
	mainMenu();
	return 0;
}

void loaduserlist(char *userfile){
    int i = 0;
    FILE * users;
    char content[200];
    memset(content, '\0', sizeof(content));
    const char s[2] = "\t";
    if((users = fopen(userfile, "r")) == NULL){
        users = fopen(userfile, "w");
        fprintf(users, "%s\t%s", userfirst->username, userfirst->password);
        fclose(users);
    }else{
        if(fgets(content, 200, users) == NULL){
            strcpy(userfirst->username, "librarian");
            strcpy(userfirst->password, "librarian");
            userfirst->next = NULL;
            return;
        }else{
            User * q = (User*)malloc(sizeof q);
            q = userfirst;
            q->next = NULL;
            do{
                while (content[i] != '\n') i++;
                content[i] = '\0';
                strcpy(q->username, strtok(content, s));
                strcpy(q->password, strtok(NULL, s));
                User * h= (User*)malloc(sizeof h);
                h->next = q->next;
                q->next = h;
                q = h;
                free(h);
            }while(fgets(content, 200, users) != NULL);
        }
    }
    fclose(users);
}

void displayBooks(char *bookfile){
    FILE *bookfp;
    char *tle = "Title";
    char *aut = "Authors";
    Book *p = (Book*)malloc(sizeof p);
    p = bookfirst;
    if((bookfp = fopen(bookfile,"r")) != NULL){
        if(!load_books(bookfp)){
            printf("ID\t%50c%50cyear\tcopies",tle,aut);
            while(p){
                printf("%d\t%50c%50c%d\t%d",p->id,p->title,p->authors,p->year,p->copies);
                p = p->next;
            }
        }else{
            printf("There are no books in the library");
        }
    }
    mainMenu();
}

void registeruser(char *userfile){
    int i = 1;
    FILE *usersfp;
    usersfp = fopen(userfile, "w");
    char username[100];
    char password[100];
    printf("\nPlease enter a username: ");
    scanf("%s",username);
    printf("\nPlease enter a password: ");
    scanf("%s",password);
    User * regist = (User*)malloc(sizeof regist);
    regist = userfirst;
    while(regist != NULL){
        fprintf(usersfp,"%s\t%s\n",regist->username,regist->password);
        if(strcmp(regist->username, username) == 0){
            i = 0;
            printf("Sorry, registration unsuccessful, the username you entered already exists");
        }
        regist = regist->next;
    }
    if(i){
        strcpy(regist->username, username);
        strcpy(regist->password, password);
        printf("Registered library account successfully!");
    }
    free(regist);
    fclose(usersfp);
}

int mainMenu(){
    int option;
    loaduserlist(userfilename);
    printf("\nPlease choose an option:\n1) Register an accoun\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:");
    while(scanf("%d",&option) != 1){
        if(option >=1 && option <= 5) break;
        printf("\nSorry, the option you entered was invalid, please try again.\n");
        printf("\nPlease choose an option:\n1) Register an accoun\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:");
        fflush(stdin);
    }
    switch(option){
        case 1:
            registeruser(userfilename);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            displayBooks(bookfilename);
            break;
        case 5:
            break;
    }
}

void searchbook(char *user){
    int option;
    printf("\nPlease choose an option:\n1)Find books by title\n2)Find Books by author\n3)Find books by year\n4)Return to previous menu\n Option:");
    while(scanf("%d",&option) != 1){
        if(option >=1 && option <= 4) break;
        printf("\nSorry, the option you entered was invalid, please try again.\n");
        printf("\nPlease choose an option:\n1)Find books by title\n2)Find Books by author\n3)Find books by year\n4)Return to previous menu\n Option:");
        fflush(stdin);
    }
    if(option == 1){
        char *q;
        char *tle = "Title";
        char *aut = "Authors";
        printf("Please enter title: ");
        scanf("%s",q);
        BookList p;
        BookList *h = &p;
        Book*a = (Book*)malloc(sizeof a);
        p = find_book_by_title(q);
        a = h->list;
        printf("ID\t%50c%50cyear\tcopies",tle,aut);
        while(h->length > 0){
            printf("%d\t%50c%50c%d\t%d",a->id,a->title,a->authors,a->year,a->copies);
            a = a->next;
        }
        searchbook(user);
    }else if(option == 2){
        char *q;
        char *tle = "Title";
        char *aut = "Authors";
        printf("Please enter author: ");
        scanf("%s",q);
        BookList p;
        BookList *h = &p;
        Book*a = (Book*)malloc(sizeof a);
        p = find_book_by_author(q);
        a = h->list;
        printf("ID\t%50c%50cyear\tcopies",tle,aut);
        while(h->length > 0){
            printf("%d\t%50c%50c%d\t%d",a->id,a->title,a->authors,a->year,a->copies);
            a = a->next;
        }
        searchbook(user);
    }else if(option == 3) {
        int q;
        char *tle = "Title";
        char *aut = "Authors";
        printf("Please enter year: ");
        scanf("%d",q);
        BookList p;
        BookList *h = &p;
        Book*a = (Book*)malloc(sizeof a);
        p = find_book_by_year(q);
        a = h->list;
        printf("ID\t%50c%50cyear\tcopies",tle,aut);
        while(h->length > 0){
            printf("%d\t%50c%50c%d\t%d",a->id,a->title,a->authors,a->year,a->copies);
            a = a->next;
        }
        searchbook(user);
    }else if(option == 4) {
        printf("Returning to previous menu...");
        if (strcmp(user, "librarian") == 0) {
            login_librarian();
        }else {
            login_user(user);
        }
    }
}

void login_librarian(void){
    int option;
    printf("\n(logged in as: librarian)\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:");
    while(scanf("%d",&option) != 1){
        if(option >=1 && option <= 5) break;
        printf("\nSorry, the option you entered was invalid, please try again.\n");
        printf("\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:");
        fflush(stdin);
    }
    if(option == 1) {
        Book p;
        p.next = NULL;
        printf("Enter the title of the book you wish to add: ");
        scanf("%s", p.title);
        getchar();
        printf("Enter the author of the book you wish to add:");
        scanf("%s", p.authors);
        getchar();
        printf("Enter the year that the book you wish to add was released: ");
        scanf("%d", p.year);
        getchar();
        printf("Enter the number of copies of the book that you wish to add: ");
        scanf("%d", p.copies);
        if (add_book(p)) {
            printf("Sorry, you attempted to add an invalid book, please try agagin\n");
        } else {
            printf("Book was successfully added");
        }
    }else if(option == 2) {
        Book p;
        p.next = NULL;
        printf("Enter the title of the book you wish to add: ");
        scanf("%s", p.title);
        getchar();
        printf("Enter the author of the book you wish to add:");
        scanf("%s", p.authors);
        getchar();
        if (remove_book(p)) {
            printf("Sorry, you attempted to remove an invalid book, please try agagin\n");
        } else {
            printf("Book was successfully removed");
        }
    }else if(option == 3) {
        printf("\nLoading search menu...\n");
        searchbook("librarian");
    }else if(option == 4) {
        displayBooks(bookfilename);
    }else if(option == 5) {
        printf("Logging out...");
        mainMenu();
    }
    login_librarian();
}

void login_user(char *name){
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
    else if(option == 3) {
        printf("\nLoading search menu...\n");
        searchbook(name);
    }else if(option == 4) {
        displayBooks(bookfilename);
    }else if(option == 5) {
        printf("Logging out...");
        mainMenu();
    }
    login_user(name);
}

void login(User *user){
    char username[100];
    char password[100];
    printf("\nPlease enter a username: ");
    scanf("%s",username);
    printf("\nPlease enter a password: ");
    scanf("%s",password);
    User * users = (User*)malloc(sizeof users);
    users = userfirst;
    if(strcmp(username, "librarian") == 0 && strcmp(password, "librarian") == 0){
        login_librarian();
    }else{
        while(users != NULL){
            if(strcmp(users->username, username) == 0 && strcmp(users->password, password) == 0){
                login_user(users->username);
            }
            users = users->next;
        }
    }
    free(users);
}