#include <stdio.h>
#include <string.h>
#include "book_management.h"
#include <stdlib.h>
#include "user.h"
#include "books.h"

int store_books(FILE *file){
    int i, j;
    char content[100];
    char a;
    while(1){
        memset(content,'\0',sizeof content);
        printf("Please enter title: ");
        while(1){
            fgets(content, 90, stdin);
for(i = 0; content[i] != '\n' && i < strlen(content); i++);
	if(i == strlen(content)) while(getchar()!='\n');
            removenewline(content);
            if(strlen(content) <= 50 && strlen(content) >= 1) break;
            else printf("Title is invalid, please limit them to 50 characters!\n\nPlease enter title: ");
        }
        fprintf(file, "%s\n", content);
        printf("Please enter author: ");
        while(1){
            fgets(content, 90, stdin);
for(i = 0; content[i] != '\n' && i < strlen(content); i++);
	if(i == strlen(content)) while(getchar()!='\n');
            removenewline(content);
            if(strlen(content) <= 50 && strlen(content) >= 1) break;
            else printf("Author is invalid, please limit them to 50 characters!\n\nPlease enter author: ");
        }
        fprintf(file, "%s\n", content);
        i = typeoption(2022, "Please enter year: ");
        fprintf(file, "%d\n", i);
        printf("Enter book's copies: ");
        while(1){
            j = 0;
            scanf("%d",&i);
            while(getchar() != '\n') j++;
            if(i <= 0 || j > 0) printf("Please enter correct copies (need to be at least 1)!\nEnter book's copies: ");
            else break;
        }
        fprintf(file, "%d\n", i);
        printf("Do you want to add another book?(Enter any key to continue and n to end)!\n");
        scanf("%c", &a);
	if(a != '\n') while(getchar()!='\n');
        if(a=='n') break;
    }
    return 0;
}

int load_books(FILE *file){
    Book *p, *h;
    p = bookfirst;
    char content[100];
	while(fgets(content,90, file) != NULL){
        fgets(content,90, file);
        fgets(content,90, file);
        fgets(content,90, file);
		Book * q = (Book*) malloc(sizeof q);
      	p ->next = q;
		h = p;
		p = q;
		q = NULL;
	}
    rewind(file);
    p = bookfirst;
    h = bookfirst;
    while(fgets(content,90, file) != NULL){
        removenewline(content);
        p->title = (char *) malloc(sizeof content);
        strcpy(p->title, content);
        fgets(content, 90, file);
        removenewline(content);
        p->authors = (char*) malloc(sizeof content);
        strcpy(p->authors, content);
        fgets(content, 90, file);
        removenewline(content);
        p->year = atoi(content);
        fgets(content, 90, file);
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
    while (p){
        if(strcmp(book.title,p->title) == 0 && strcmp(book.authors, p->authors) == 0) {
        	if(p->copies == book.copies) return 1;
        	else if(p->year == book.year){
        		char a;
        		char b[1000];
        		memset(b, '\0', sizeof b);
        		printf("Please confirm whether to modify copies(enter any key to exit and enter y to confirm)!");
        		scanf("%c",&a);
        		fgets(b, 900, stdin);
        		if(a == 'y' && strlen(b) == 1) {
        			FILE *fp;
        			p->copies = book.copies;
        			fp = fopen(bookfilename,"w");
        			p = bookfirst;
        			while(p){
        				fprintf(fp, "%s\n%s\n%d\n%d\n", p->title, p->authors, p->year, p->copies);
    					p = p -> next;
        			}
    				fclose(fp);
        			return 0;
        		}
        		else return -1;
        	}
        }
        p = p->next;
    }
    FILE *fp;
    fp = fopen(bookfilename,"a");
    fprintf(fp, "%s\n%s\n%d\n%d\n", book.title, book.authors, book.year, book.copies);
    fclose(fp);
    return 0;
}

int remove_book(Book book){
    int i = 1, j = 1;
    Book *p = bookfirst;
    Book *h, *k, *q;
    while (p){
        if(strcmp(book.title,p->title) == 0 && strcmp(book.authors, p->authors) == 0) break;
        p = p->next;
        i++;
    }
    if(!p) return 0;
    p = bookfirst;
    h = (Book*)malloc(sizeof h);
    k = h;
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
    h = k;
    p = bookfirst;
    while (p){
        if(j == i){
            p = p->next;
            j++;
            continue;
        }
        k->title = (char*) malloc(200);
        k->authors = (char*) malloc(200);
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
    int i = 0;
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
    while(1){
        if(!p || !m) break;
        if(strcmp(p->title, title) == 0){
            m->title = (char*)malloc(sizeof p->title);
            strcpy(m->title,p->title);
            m->authors = (char*)malloc(sizeof p->authors);
            strcpy(m->authors,p->authors);
            m->year = p->year;
            m->copies = p->copies;
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
    int i = 0;
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
    while(1){
        if(!p || !m) break;
        if(strcmp(p->authors, author) == 0){
            m->title = (char*)malloc(100);
            strcpy(m->title,p->title);
            m->authors = (char*)malloc(100);
            strcpy(m->authors,p->authors);
            m->year = p->year;
            m->copies = p->copies;
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
    int i = 0;
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
    while(1){
        if(!p || !m) break;
        if(p->year == year){
            m->title = (char*)malloc(100);
            strcpy(m->title,p->title);
            m->authors = (char*)malloc(100);
            strcpy(m->authors,p->authors);
            m->year = p->year;
            m->copies = p->copies;
            m = m->next;
        }
        p = p->next;
    }
    if(i == 0) j.list = NULL;
    j.length = i;
    return j;
}

