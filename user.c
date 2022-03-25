#include "user.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "book_management.h"

Book *bookfirst;

user *loaduser(user * user1, FILE* fp){
    user* q;
    user* h;
    q = user1;
    char content[100];
    int j = 0;
    rewind(fp);
    char a = fgetc(fp);
    if(a == EOF){
        user1->username = (char*) malloc(sizeof "librarian");
        strcpy(user1->username,"librarian");
        user1->password = (char*) malloc(sizeof "librarian");
        strcpy(user1->password, "librarian");
        return NULL;
    }
    rewind(fp);
    while(fgets(content, 200, fp) != NULL){
        fgets(content, 200, fp);
        while(content[j] != '\0'&& content[j] !='\n') j++;
        content[j] = '\0';
        j = 0;
        q->username = (char*) malloc(sizeof content);
        strcpy(q->username, content);
        fgets(content, 200, fp);
        while(content[j] != '\0'&& content[j] !='\n') j++;
        content[j] = '\0';
        j = 0;
        q->password = (char*) malloc(sizeof content);
        strcpy(q->password, content);
        q->borrowed = NULL;
        user* p =(user*) malloc(sizeof p);
        h = q;
        q->next = p;
        q = p;
        p = NULL;
    }
    h -> next = NULL;
    return user1;
}

user *regist(user * user1){
    FILE *fp;
    user* q;
    q = user1;
    char username[100];
    char password[100];
    char name[100];
    printf("\nPlease enter a name: ");
    scanf("%s",name);
    getchar();
    printf("\nPlease enter a username: ");
    scanf("%s",username);
    getchar();
    printf("Please enter a password: ");
    scanf("%s",password);
    while(1){
        if(!q) break;
        if(strcmp(username, q->username) == 0){
            return NULL;
        }
        if(!q->next) break;
        q = q->next;
    }
    user *p = (user*) malloc(sizeof p);
    p->username = (char*) malloc(sizeof username);
    p->password = (char*) malloc(sizeof password);
    strcpy(p->username, username);
    strcpy(p->password, password);
    p->next = NULL;
    q->next = p;
	fp = fopen("user.txt","a");
fprintf(fp,"%s\n%s\n%s\n",name,p->username,p->password);
    fclose(fp);
    return user1;
}

int login(user* user1, char*name, char*pass){
    user *p;
    p = user1;
    while(1){
        if(p == NULL){
            break;
        }
        if(strcmp(name, p->username) == 0){
            if(strcmp(pass, p->password) == 0){
                if(strcmp(name, "librarian") == 0){
                    return 1;
                }
                return 2;
            }
        }
        p = p->next;
    }
    return 0;
}

int borrow(char* name, user* user1, Book*book){
    user* p = user1;
    Book *q = bookfirst;
    while(1){
if(q==NULL) break;
        if(strcmp(q->title, book->title) == 0 && strcmp(q->authors, book->authors) == 0){
            break;
        }
	q = q->next;
    }
    if(q == NULL) return 1;
    while(p){
        if(strcmp(name, p->username) == 0) {
        break;
	}
        p = p->next;
    }

if(p->borrowed == NULL)printf("1\n");
    if(p->borrowed == NULL) {
        p->borrowed = (BookList*) malloc(sizeof p->borrowed);
        p->borrowed->list = (Book*) malloc(sizeof p->borrowed->list);
        p->borrowed->list->title = (char*) malloc(100 * sizeof (char));
        p->borrowed->list->authors = (char*) malloc(100 * sizeof (char));
        strcpy(p->borrowed->list->title,book->authors);
        strcpy(p->borrowed->list->authors,book->title);
        p->borrowed->list->next = NULL;
        p->borrowed->length = 0;
    }else{
        Book* h = p->borrowed->list;
        while(h){
            if(strcmp(h->authors,book->authors) == 0 && strcmp(h->title,book->title) == 0){
                return 2;//已经借了这本书
            }
            h = h->next;
        }
        if(q->copies<1) return 3;//这本书已经被借空了
        h = p->borrowed->list;
        while(h->next);
        h->next = (Book*) malloc(sizeof h->next);
        h = h->next;
        strcpy(h->authors,book->authors);
        strcpy(h->title,book->title);
        q->copies--;
    }
    return 0;
}
