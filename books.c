#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "books.h"
#include "user.h"
#include "book_management.h"

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
        if(authorlen < strlen(p->title)) authorlen = strlen(p->authors);
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
        if(authorlen < strlen(p->title)) authorlen = strlen(p->authors);
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

int search(void){
    int option, i, j;
    printf("Please choose an option:\n1) Find books by title\n2) Find books by authors\n3) Find books by year\n4) Return to previous menu\n Option: ");
    do{
        i = scanf("%d", &option);
        if(i != 1 && option != 1 && option != 2 && option != 3 && option != 4) {
            printf("\nSorry, the option you entered was invalid, please try again.\n");
            printf("Please choose an option:\n1) Find books by title\n2) Find books by authors\n3) Find books by year\n4) Return to previous menu\n Option: ");
            fflush(stdin);
            continue;
        }else {
            if(option == 1 || option == 2 || option == 3 || option == 4) break;
            else{
                printf("\nSorry, the option you entered was invalid, please try again.\n");
                printf("Please choose an option:\n1) Find books by title\n2) Find books by authors\n3) Find books by year\n4) Return to previous menu\n Option: ");
                fflush(stdin);
                continue;
            }
        }
    }while(1);
    printf("\nLoading search menu...\n");
    if(option == 1){
        char title[100];
        printf("Please enter title: ");
        scanf("%s",title);
        BookList first = find_book_by_title (title);
        if(first.list == NULL) return 2;
        Book *p = first.list;
        Book *h = bookfirst;
        for(i = 0,j = 1; i < first.length && p && h; j++){
            if(strcmp(p->authors, h->authors) == 0 && strcmp(p->title,h->title) == 0){
                printf("%d\t%s\t%s\t%d\t%d\n", j, p->title, p->authors, p->year, p->copies);
                if(i == first.length-1) p -> next =NULL;
                p = p->next;
                i++;
            }
            h = h->next;
        }
    }
    else if(option == 2){
        char author[100];
        printf("Please enter author: ");
        scanf("%s",author);
        BookList first = find_book_by_author(author);
        if(first.list == NULL) return 2;
        Book *p = first.list;
        Book *h = bookfirst;
        for(i = 0,j = 1; i < first.length && p && h; j++){
            if(strcmp(p->authors, h->authors) == 0 && strcmp(p->title,h->title) == 0){
                printf("%d\t%s\t%s\t%d\t%d\n", j, p->title, p->authors, p->year, p->copies);
                if(i == first.length-1) p -> next =NULL;
                p = p->next;
                i++;
            }
            h = h->next;
        }
    }
    else if(option == 3){
        int year;
        printf("Please enter year: ");
        scanf("%d",&year);
        BookList first = find_book_by_year (year);
        if(first.list == NULL) return 2;
        Book *p = first.list;
        Book *h = bookfirst;
        for(i = 0,j = 1; i < first.length && p && h; j++){
            if(strcmp(p->authors, h->authors) == 0 && strcmp(p->title,h->title) == 0){
                printf("%d\t%s\t%s\t%d\t%d\n", j, p->title, p->authors, p->year, p->copies);
                if(i == first.length-1) p -> next =NULL;
                p = p->next;
                i++;
            }
            h = h->next;
        }
    }
    else if (option == 4){
        return 0;
    }
    return 1;
}
