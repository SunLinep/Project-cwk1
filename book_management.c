#include <stdio.h>
#include <string.h>
#include "book_management.h"
#include <stdlib.h>
#include "user.h"

int store_books(FILE *file){
    int i;
    char content[100];
    char a;
    while(1){
        memset(content,'\0',sizeof content);
        printf("\nEnter book's title: ");
        gets(content);
        fprintf(file, "%s\n", content);
        memset(content,'\0',sizeof content);
        printf("Enter book's author: ");
        gets(content);
        fprintf(file, "%s\n", content);
        printf("Enter book's year: ");
        scanf("%d",&i);
        fprintf(file, "%d\n", i);
        printf("Enter book's copies: ");
        scanf("%d",&i);
        getchar();
        fprintf(file, "%d\n", i);
        printf("Do you want to add books?(y/n) ");
        scanf("%c", &a);
        if(a=='n') break;
    }
    return 0;
}

int load_books(FILE *file){
    Book *p, *h;
    p = bookfirst;
    char content[100];
    int j = 0, i = 1;
	while(fgets(content,200, file) != NULL){
        fgets(content,200, file);
        fgets(content,200, file);
        fgets(content,200, file);
		Book * q = (Book*) malloc(sizeof q);
      	p ->next = q;
		h = p;
		p = q;
		q = NULL;
	}
    rewind(file);
    rewind(file);
    p = bookfirst;
    h = bookfirst;
    while(fgets(content,200, file) != NULL){
        while(content[j] != '\0'&& content[j] !='\n') j++;
        content[j] = '\0';
        j = 0;
        p->title = (char *) malloc(sizeof content);
        strcpy(p->title, content);
        fgets(content, 200, file);
        while(content[j] != '\0'&& content[j] !='\n') j++;
        content[j] = '\0';
        j = 0;
        p->authors = (char*) malloc(sizeof content);
        strcpy(p->authors, content);
        fgets(content, 200, file);
        while(content[j] != '\0'&& content[j] !='\n') j++;
        content[j] = '\0';
        j = 0;
        p->year = atoi(content);
        fgets(content, 200, file);
        while(content[j] != '\0'&& content[j] !='\n') j++;
        content[j] = '\0';
        j = 0;
        p->copies = atoi(content);
        h = p;
        p = p->next;
        h->id = i++;
    }
    h -> next = NULL;
    return 0;
}

int add_book(Book book);

int remove_book(Book book);

BookList find_book_by_title (const char *title){
    Book *p = bookfirst;
    int i = 0, h = 0;
    BookList j;
    Book* q = (Book *) malloc(sizeof q);
    j.list = q;
    q = NULL;
    while(1){
        if(!p) break;
        if(strcmp(p->title, title) == 0){
            i++;
            if(i > 1){
                Book* q = (Book *) malloc(sizeof q);
                j.list->next = q;
                q = NULL;
            }
        }
        p = p->next;
    }
    p = bookfirst;
    Book* m = j.list;
    while(1){
        if(!p || !m) break;
        if(strcmp(p->title, title) == 0){
            m->title = (char*)malloc(sizeof p->title);
            strcpy(m->title,p->title);
            m->authors = (char*)malloc(sizeof p->authors);
            strcpy(m->authors,p->authors);
            m->year = p->year;
            m->copies = p->copies;
            m->id = p->id;
            m = m->next;
        }
        p = p->next;
    }
    if(i == 0) j.list = NULL;
    j.length = i;
    return j;
}

BookList find_book_by_author (const char *author){
    Book *p = bookfirst;
    int i = 0, h = 0;
    BookList j;
    Book* q = (Book *) malloc(sizeof q);
    j.list = q;
    q = NULL;
    while(1){
        if(!p) break;
        if(strcmp(p->authors, author) == 0){
            i++;
            if(i > 1){
                Book* q = (Book *) malloc(sizeof q);
                j.list->next = q;
                q = NULL;
            }
        }
        p = p->next;
    }
    p = bookfirst;
    Book* m = j.list;
    Book* x = j.list;
    while(1){
        if(!p || !m) break;
        if(strcmp(p->authors, author) == 0){
            m->title = (char*)malloc(sizeof p->title);
            strcpy(m->title,p->title);
            m->authors = (char*)malloc(sizeof p->authors);
            strcpy(m->authors,p->authors);
            m->year = p->year;
            m->copies = p->copies;
            m->id = p->id;
            x = m;
            m = m->next;
        }
        p = p->next;
    }
    x->next = NULL;
    if(i == 0) j.list = NULL;
    j.length = i;
    return j;
}

BookList find_book_by_year (unsigned int year){
    Book *p = bookfirst;
    int i = 0, h = 0;
    BookList j;
    Book* q = (Book *) malloc(sizeof q);
    j.list = q;
    q = NULL;
    while(1){
        if(!p) break;
        if(p->year ==year){
            i++;
            if(i > 1){
                Book* q = (Book *) malloc(sizeof q);
                j.list->next = q;
                q = NULL;
            }
        }
        p = p->next;
    }
    p = bookfirst;
    Book* m = j.list;
    while(1){
        if(!p || !m) break;
        if(p->year ==year){
            m->title = (char*)malloc(sizeof p->title);
            strcpy(m->title,p->title);
            m->authors = (char*)malloc(sizeof p->authors);
            strcpy(m->authors,p->authors);
            m->year = p->year;
            m->copies = p->copies;
            m->id = p->id;
            m = m->next;
        }
        p = p->next;
    }
    if(i == 0) j.list = NULL;
    j.length = i;
    return j;
}
