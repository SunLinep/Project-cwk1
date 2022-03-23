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
    q = user1;
	fp = fopen("user.txt","w");
    while(q){
        fprintf(fp,"%s\n%s\n",q->username,q->password);
        q = q->next;
    }
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
