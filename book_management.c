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
        fgets(content, 90, stdin);
        getchar();
        fprintf(file, "%s\n", content);
        memset(content,'\0',sizeof content);
        printf("Enter book's author: ");
        fgets(content, 90, stdin);
        getchar();
        fprintf(file, "%s\n", content);
        printf("Enter book's year: ");
        scanf("%d",&i);
        fprintf(file, "%d\n", i);
        printf("Enter book's copies: ");
        scanf("%d",&i);
        getchar();
        fprintf(file, "%d\n", i);
        printf("Do you want to add another book?(Enter any key to continue and n to end)!\n");
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
    p = bookfirst;
    h = bookfirst;
    while(fgets(content,200, file) != NULL){
        removenewline(content);
        p->title = (char *) malloc(sizeof content);
        strcpy(p->title, content);
        fgets(content, 200, file);
        removenewline(content);
        p->authors = (char*) malloc(sizeof content);
        strcpy(p->authors, content);
        fgets(content, 200, file);
        removenewline(content);
        p->year = atoi(content);
        fgets(content, 200, file);
        removenewline(content);
        p->copies = atoi(content);
        h = p;
        p = p->next;
    }
    h -> next = NULL;
    return 0;
}

int add_book(Book book){
    Book *p = bookfirst;
    Book *q = (Book *) malloc(sizeof q);
    q->title = (char*) malloc(sizeof book.title);
    q->authors = (char*) malloc(sizeof book.authors);
    strcpy(q->title,book.title);
    strcpy(q->authors,book.authors);
    q->year = book.year;
    q->copies = book.copies;
    q->next = NULL;
    FILE *fp;
    while (p){
        if(strcmp(book.title,p->title) == 0 && strcmp(book.authors, p->authors) == 0) return 1;
        if(p->next == NULL){
            p->next = q;
            break;
        }
        p = p->next;
    }
    fp = fopen("book.txt","a");
    fprintf(fp, "%s\n%s\n%d\n%d\n", book.title, book.authors, book.year, book.copies);
    fclose(fp);
    return 0;
}

int remove_book(Book book){
    int i = 1, j = 1;
    Book *p = bookfirst;
    Book *h, *k, *q;
    while (p){
        if(strcmp(book.title,p->title) == 0 && strcmp(book.authors, p->authors) == 0) {
            break;
        }
        p = p->next;
        i++;
    }
    if(!p) return 0;
    p = bookfirst;
    h = (Book*)malloc(sizeof h);
    k = h;
    q = h;
    while(p->next){
        q = h;
        h->next = (Book*)malloc(sizeof h->next);
        h = h->next;
        p = p->next;
        if(!p->next){
            q->next = NULL;
            break;
        }
    }
//    for(j = 0; j < i; j++){
//        h = (Book*)malloc(sizeof h);
//        if(j == i-1){
//            h->next = NULL;
//            break;
//        }
//        h = h->next;
//    }
    h = k;
    p = bookfirst;
    while (p){
        if(j == i){
            p = p->next;
            j++;
            continue;
        }
        k->title = (char*) malloc(sizeof p->title);
        k->authors = (char*) malloc(sizeof p->authors);
        strcpy(k->title, p->title);
        strcpy(k->authors, p->authors);
        k->year = p->year;
        k->copies = p->copies;
        k = k->next;
        p = p->next;
        j++;
    }
    bookfirst = h;
    return 1;
}

BookList find_book_by_title (const char *title){
    Book *p = bookfirst;
    int i = 0, h = 0;
    BookList j;
    Book* q = (Book *) malloc(sizeof q);
    j.list = q;
    Book* m = j.list;
    q = NULL;
    while(1){
        if(!p) break;
        if(strcmp(p->title, title) == 0){
            i++;
            if(i > 1){
                q = (Book *) malloc(sizeof q);
                m->next = q;
                q = NULL;
                m = m->next;
            }
        }
        p = p->next;
    }
    p = bookfirst;
    m = j.list;
    Book* x = j.list;
    while(1){
        if(!p || !m) break;
        if(strcmp(p->title, title) == 0){
            m->title = (char*)malloc(sizeof p->title);
            strcpy(m->title,p->title);
            m->authors = (char*)malloc(sizeof p->authors);
            strcpy(m->authors,p->authors);
            m->year = p->year;
            m->copies = p->copies;
            x = m;
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
    Book* m = j.list;
    q = NULL;
    while(1){
        if(!p) break;
        if(strcmp(p->authors, author) == 0){
            i++;
            if(i > 1){
                q = (Book *) malloc(sizeof q);
                m->next = q;
                q = NULL;
                m = m->next;
            }
        }
        p = p->next;
    }
    p = bookfirst;
    m = j.list;
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
            x = m;
            m = m->next;
        }
        p = p->next;
    }
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
    Book* m = j.list;
    q = NULL;
    while(1){
        if(!p) break;
        if(p->year == year){
            i++;
            if(i > 1){
                q = (Book *) malloc(sizeof q);
                m->next = q;
                q = NULL;
                m = m->next;
            }
        }
        p = p->next;
    }
    p = bookfirst;
    m = j.list;
    Book* x = j.list;
    while(1){
        if(!p || !m) break;
        if(p->year == year){
            m->title = (char*)malloc(sizeof p->title);
            strcpy(m->title,p->title);
            m->authors = (char*)malloc(sizeof p->authors);
            strcpy(m->authors,p->authors);
            m->year = p->year;
            m->copies = p->copies;
            x = m;
            m = m->next;
        }
        p = p->next;
    }
    if(i == 0) j.list = NULL;
    j.length = i;
    return j;
}
