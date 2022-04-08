#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "books.h"
#include "user.h"
#include "book_management.h"

//Initialize the library system
void initlibrary(user *userfirst, char *books, char *users, FILE *fp){
int i;
    user* user2 = (user*)malloc(sizeof user2);
    if((fp = fopen(books, "r")) != NULL) load_books(fp);
    else {
        char content[15];
        printf("Please enter the administrator account to initialize the library!\n");
        printf("Please enter administrator username: ");
        while(1){
            fgets(content, 10, stdin);
for(i = 0; content[i] != '\n' && i < strlen(content); i++);
	if(i == strlen(content)) while(getchar()!='\n');
            removenewline(content);
            if(strcmp("librarian", content) != 0){
                printf("Please enter the correct administrator username: ");
            }else break;
        }
        printf("Please enter administrator password: ");
        while(1){
            fgets(content, 10, stdin);
for(i = 0; content[i] != '\n' && i < strlen(content); i++);
	if(i == strlen(content)) while(getchar()!='\n');
            removenewline(content);
            if(strcmp("librarian", content) != 0){
                printf("Please enter the correct administrator password: ");
            }else break;
        }
        printf("Log in successfully!\n");
        fp = fopen(books, "w");
        store_books(fp);
        fclose(fp);
fp = fopen(books, "r");
        load_books(fp);
    }
    if((fp = fopen(users, "r")) ==NULL){
        fp = fopen(users, "w");
        fprintf(fp,"librarian\nlibrarian\nlibrarian\n");
        fclose(fp);
fp = fopen(users, "r");
        userfirst = loaduser(userfirst, fp);
        fclose(fp);
    }else if((user2 = loaduser(userfirst, fp)) == NULL) {
        user2 = (user*)malloc(sizeof user2);
        fclose(fp);
        fp = fopen(users, "w");
        fprintf(fp, "librarian\nlibrarian\nlibrarian\n");
        fclose(fp);
        fp = fopen(users, "r");
        userfirst = loaduser(userfirst, fp);
fclose(fp);
    }else{
        userfirst = loaduser(userfirst, fp);
    }
}

//Remove the trailing \n and \r
void removenewline(char *content){
    int i;
    for(i = 0; i < strlen(content); i++){
        if(content[i]=='\r' || content[i] == '\n'){
            content[i] = '\0';
            break;
        }
    }
}

//Check whether the input is valid
int checkcontent(char *content){
	int i;
	if(strlen(content) > 8 || strlen(content) < 1) return 0;
	for(i = 0; i < strlen(content); i++){
		if(content[i] < '0' || (content[i] > '9' && content[i] < 'A') ||(content[i] > 'Z' && content[i] < 'a') || content[i] > 'z') return 0;
	}
	return 1;
}

//Menu display and input
int typeoption(int num, char *choices){
	int i, j, option;
    printf("%s", choices);
    while(1){
        j = 0;
        i = scanf("%d", &option);
        while(getchar() != '\n') j++;
        fflush(stdin);
        if(i != 1 || option <= 0 || option > num || j > 0) {
            printf("\nSorry, the option you entered was invalid, please try again.\n");
            printf("%s", choices);
            continue;
        }else return option;
    }
}

//display all books
void displayall(){
    Book *p;
    int i, k, idlen = 2, titlelen = 5, authorlen = 7, j = 1;
    p = bookfirst;
    while(p){
        k = 0;
        i = j;
        while(i > 0){
            i /= 10;
            k++;
        }
        if(k > idlen) idlen = k;
        if(titlelen < strlen(p->title)) titlelen = strlen(p->title);
        if(authorlen < strlen(p->authors)) authorlen = strlen(p->authors);
        p = p->next;
        j++;
    }
    j = 1;
    p = bookfirst;
    printf("%-*s    %-*s    %-*s    Year    Copies\n",idlen, "Id", titlelen, "Title", authorlen, "Authors");
    while(p){
        printf("%-*d    %-*s    %-*s    %-4d    %d\n",idlen, j, titlelen, p->title, authorlen, p->authors,p->year,p->copies);
        p = p->next;
        j++;
    }
}

//display borrowed books
void displayborrowed(user* user1){
	Book *p;
	user *q = user1;
    int h = 0, i, k, idlen = 2, titlelen = 5, authorlen = 7, j = 1;
    p = bookfirst;
    while(p){
    	if(q->borrowed[h] == j){
        k = 0;
        i = j;
        while(i > 0){
            i /= 10;
            k++;
        }
        if(k > idlen) idlen = k;
        if(titlelen < strlen(p->title)) titlelen = strlen(p->title);
        if(authorlen < strlen(p->authors)) authorlen = strlen(p->authors);
        h++;
        }
        p = p->next;
        j++;
    }
    if(h == 0) return;
    h = 0;
    j = 1;
    p = bookfirst;
    printf("%-*s    %-*s    %-*s    Year    Copies\n",idlen, "Id", titlelen, "Title", authorlen, "Authors");
    while(p){
    	if(q->borrowed[h] == j){
        printf("%-*d    %-*s    %-*s    %-4d    %d\n",idlen, j, titlelen, p->title, authorlen, p->authors,p->year,p->copies);
        h++;
        }
        p = p->next;
        j++;
    }
}

//display searched books
void displaysearch(BookList books){
	Book *p, *q;
    int i, k, h = 0, idlen = 2, titlelen = 5, authorlen = 7, j = 1;
    p = bookfirst;
    q = books.list;
    while(p){
	if(strcmp(p->authors, q->authors) == 0 && strcmp(p->title, q->title) == 0){
		k = 0;
       	i = j;
        	while(i > 0){
           	 	i /= 10;
            	k++;
       		 }
       	if(k > idlen) idlen = k;
        	if(titlelen < strlen(q->title)) titlelen = strlen(q->title);
        	if(authorlen < strlen(q->authors)) authorlen = strlen(q->authors);
        	if(h == books.length-1) break;
       	h++;
        	q = q->next;
	}
        p = p->next;
        j++;
    }
    j = 1;
    h = 0;
    p = bookfirst;
    q = books.list;
    printf("%-*s    %-*s    %-*s    Year    Copies\n",idlen, "Id", titlelen, "Title", authorlen, "Authors");
    while(p){
    	if(strcmp(p->authors, q->authors) == 0 && strcmp(p->title, q->title) == 0){
        printf("%-*d    %-*s    %-*s    %-4d    %d\n",idlen, j, titlelen, p->title, authorlen, p->authors,p->year,p->copies);
        if(h == books.length-1) break;
        h++;
        q = q->next;
        }
        p = p->next;
        j++;
    }
}

//search books
int search(void){
    int option;
    option = typeoption(4, "Please choose an option:\n1) Find books by title\n2) Find books by authors\n3) Find books by year\n4) Return to previous menu\n Option: ");
    printf("\nLoading search menu...\n");
    if(option == 1){
        char title[100];
        printf("Please enter title: ");
        while(1){
            fgets(title, 90, stdin);
            removenewline(title);
            if(strlen(title) <= 50 && strlen(title) >= 1) break;
            else printf("Title is invalid, please limit them to 50 characters!\n\nPlease enter title: ");
        }
        BookList first = find_book_by_title (title);
        if(first.list == NULL) return 2;
        displaysearch(first);
    }
    else if(option == 2){
        char author[100];
        printf("Please enter author: ");
        while(1){
            fgets(author, 90, stdin);
            removenewline(author);
            if(strlen(author) <= 50 && strlen(author) >= 1) break;
            else printf("Author is invalid, please limit them to 50 characters!\n\nPlease enter author: ");
        }
        BookList first = find_book_by_author(author);
        if(first.list == NULL) return 2;
        displaysearch(first);
    }
    else if(option == 3){
        int year;
        year = typeoption(2022, "Please enter year: ");
        BookList first = find_book_by_year (year);
        if(first.list == NULL) return 2;
        displaysearch(first);
    }
    else if (option == 4){
        return 0;
    }
    return 1;
}

