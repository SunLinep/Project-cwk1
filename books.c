#include<stdio.h>
#include<stdlib.h>
#include "books.h"
#include "book_management.h"

int displayall(Book * bookfirst){
    Book *h;
    h = bookfirst;
int i = 1;
    while(1){
        if(!h) break;
//        h->id = i++;
        printf("%d\t%s\t%s\t%d\t%d\n",h->id,h->title,h->authors,h->year,h->copies);
        h = h->next;
    }
    return 1;
}

int search(void){
    int option, i;
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
        for(i = 0; i < first.length; i++){
            printf("%d\t%s\t%s\t%d\t%d\n", p->id, p->title, p->authors, p->year, p->copies);
        }
    }
    else if(option == 2){
        char author[100];
        printf("Please enter author: ");
        scanf("%s",author);
        BookList first = find_book_by_author(author);
        if(first.list == NULL) return 2;
        Book *p = first.list;
        for(i = 0; i < first.length; i++){
            printf("%d\t%s\t%s\t%d\t%d\n", p->id, p->title, p->authors, p->year, p->copies);
            p = p->next;
        }
        free(p);
    }
    else if(option == 3){
        int year;
        printf("Please enter year: ");
        scanf("%d",&year);
        BookList first = find_book_by_year (year);
        if(first.list == NULL) return 2;
        Book *p = first.list;
        for(i = 0; i < first.length; i++){
            printf("%d\t%s\t%s\t%d\t%d\n", p->id, p->title, p->authors, p->year, p->copies);
        }
    }
    else if (option == 4){
        return 0;
    }
    return 1;
}