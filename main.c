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

void mainMenu(void);

void searchbook(char *user);

void login_librarian(void);

void login_user(char *name);

void login(void);

int main(void){
    bookfirst = (Book*)malloc(sizeof bookfirst);
    userfirst = (User*) malloc(sizeof userfirst);
    strcpy(userfirst->username ,"librarian");
    strcpy( userfirst->password ,"librarian");
    bookfirst->next = NULL;
    userfirst->next = NULL;
    mainMenu();
	return 0;
}

void loaduserlist(char *userfile){
    int i = 0;
    FILE * users;
    char content[200];
//    char username[100];
//    char password[100];
//    strcpy( username,userfirst->username);
//    strcpy(password ,userfirst->password);
    memset(content, '\0', sizeof(content));
    const char s[2] = "\t";
    if((users = fopen(userfile, "r")) == NULL){
        users = fopen(userfile, "w");
        setbuf(users,NULL);
        fprintf(users, "%s\n%s\n", userfirst->username, userfirst->password);
        fflush(users);
    }else{
        if(fgets(content, 200, users) == NULL){
            fclose(users);
            users = fopen(userfile, "w");
            setbuf(users,NULL);
            fprintf(users, "%s\n%s\n", userfirst->username, userfirst->password);
            fflush(users);
            fclose(users);
            return;
        }else{
            User * q;
            q = userfirst;
            do{
                while (content[i] != '\n'&& content[i] != '\0') i++;
                content[i] = '\0';
                strcpy(q->username, content);
                fgets(content, 200, users);
                strcpy(q->password, content);
                User *h = (User*) malloc(sizeof h);
                q->next = h;
                h->next = NULL;
                q = q->next;
                h = h->next;
                free(h);
            }while(fgets(content, 200, users) != NULL);
            q = NULL;
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
    usersfp = fopen(userfile, "r");
    char username[100];
    char password[100];
    char truename[100];
    printf("\nPlease enter a username: ");
    scanf("%s",username);
    getchar();
    printf("Please enter a password: ");
    scanf("%s",password);
    User * regist;
    regist = userfirst;
    while(regist != NULL){
        int j = 0;
        while (regist->username[j] != '\n') j++;
        strcpy(truename, regist->username);
        truename[j] = '\0';
        if(strcmp(truename, username) == 0){
            i = 0;
            printf("\nSorry, registration unsuccessful, the username you entered already exists\n");
            fclose(usersfp);
            mainMenu();
        }
        regist = regist->next;
    }
    regist = (User *)malloc(sizeof regist);
    strcpy(regist->username, username);
    strcpy(regist->password, password);
    regist->next = NULL;
    fclose(usersfp);
    fopen(userfile, "w");
    regist = userfirst;
    while(regist != NULL) {
        fprintf(usersfp, "%s\n%s\n", regist->username, regist->password);
        regist = regist->next;
    }
    printf("Registered library account successfully!");
    free(regist);
    fclose(usersfp);
    mainMenu();
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
        printf("Enter the author of the book you wish to add:");
        scanf("%s", p.authors);
        printf("Enter the year that the book you wish to add was released: ");
        scanf("%d", p.year);
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

void login(void){
    char name[100];
    char pass[100];
    char truename[100];
    char truepass[100];
    int i = 0;
    int j = 0;
    printf("\nPlease enter a username: ");
    scanf("%s",name);
    printf("Please enter a password: ");
    scanf("%s",pass);
    User *p;
    p = userfirst;
    for(i = 0; p->username[i]!='\n';i++);
    for(j = 0; p->password[j]!='\n';j++);
    strcpy(truename, p->username);
    strcpy(truepass, p->password);
    truename[i] = '\0';
    truepass[j] = '\0';
    if(strcmp(truename,name) == 0){
        if(strcmp(truepass,pass) == 0){
            login_librarian();
        }
        printf("\nThe entered password is incorrect!");
        mainMenu();
    }
    p = p->next;
    while(p != NULL){
        for(i = 0; p->username[i]!='\n';i++);
        for(j = 0; p->password[j]!='\n';j++);
        strcpy(truename, p->username);
        strcpy(truepass, p->password);
        truename[i] = '\0';
        truepass[j] = '\0';
        if(strcmp(p->username,name) == 0){
            if(strcmp(p->password,pass) == 0){
                login_user(name);
            }
            printf("\nThe entered password is incorrect!");
            mainMenu();
        }
        p = p->next;
    }
    printf("The user does not exist");
    mainMenu();
}

void mainMenu(void) {
    int option;
    loaduserlist(userfilename);
    printf("\nPlease choose an option:\n1) Register an accoun\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:");
    while(1){
        if (scanf("%d", &option) == 1)if (option >= 1 && option <= 5) break;
        printf("\nSorry, the option you entered was invalid, please try again.\n");
        printf("\nPlease choose an option:\n1) Register an accoun\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:");
        fflush(stdin);
    }
    if(option == 1) {
        registeruser(userfilename);
    }else if(option == 2) {
        login();
    }else if(option == 3);
    else if (option == 4){
        displayBooks(bookfilename);
    }else if(option == 5);
}
