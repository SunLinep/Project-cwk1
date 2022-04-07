#include "user.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "book_management.h"
#include "books.h"

Book *bookfirst;//The head node of book

//Loading User Information
user *loaduser(user * user1, FILE* fp){
    user* q;
    user* h;
    FILE* file;
    q = user1;
    char content[100];
    int j = 0, i, k;
    rewind(fp);
    char a = fgetc(fp);
    if(a == EOF){
        user1->username = (char*) malloc(20);
        strcpy(user1->username,"librarian");
        user1->password = (char*) malloc(20);
        strcpy(user1->password, "librarian");
        return NULL;
    }
    rewind(fp);
    while(fgets(content, 200, fp) != NULL){
        fgets(content, 200, fp);
        while(content[j] != '\0'&& content[j] !='\n' && content[j] !='\r') j++;
        content[j] = '\0';
        j = 0;
        q->username = (char*) malloc(sizeof content);
        strcpy(q->username, content);
        fgets(content, 200, fp);
        while(content[j] != '\0'&& content[j] !='\n' && content[j] !='\r') j++;
        content[j] = '\0';
        j = 0;
        q->password = (char*) malloc(sizeof content);
        strcpy(q->password, content);
        q->borrowed = (int *) malloc(10 *sizeof (int));
        for(i = 0; i < 10; i++) q->borrowed[i] = -1;
        user* p =(user*) malloc(sizeof p);
        h = q;
        q->next = p;
        q = p;
        p = NULL;
    }
    h -> next = NULL;
    if((file = fopen("borrow.txt", "r")) != NULL){
    	while(fgets(content, 200, file)!=NULL){
    		while(content[j] != '\0'&& content[j] !='\n' && content[j] !='\r') j++;
        	content[j] = '\0';
        	j= 0;
    		q = user1;
    		while(q){
    			if(strcmp(q->username, content) == 0) break;
    			q = q->next;
    		}
    		fgets(content,200, file);
    		while(content[j] != '\0'&& content[j] !='\n' && content[j] !='\r') j++;
        	content[j] = '\0';
        	j = 0;
        	i = atoi(content);
        	k = 0;
        	while(i > 0){
        		fgets(content,200, file);
        		while(content[j] != '\0'&& content[j] !='\n' && content[j] !='\r') j++;
        		content[j] = '\0';
        		j = 0;
        		q->borrowed[k] = atoi(content);
        		k++;
        		i--;
        	}
    	}
	fclose(file);
    }
    return user1;
}

//User registration
user *regist(user * user1){
    FILE *fp;
    user* q;
    q = user1;
    char username[15];
    char password[15];
    char name[15];
    printf("\nPlease enter a name: ");
    while(1){
        fgets(name, 10, stdin);
        removenewline(name);
        if(checkcontent(name) == 0){
            printf("\nThe format is wrong. The length should be four to eight characters and contains no illegal characters!\n");
            printf("\nPlease enter a corrcet username: ");
            continue;
        }else break;
    }
    printf("Please enter a username: ");
    while(1){
        fgets(username, 10, stdin);
        removenewline(username);
        if(checkcontent(username) == 0){
            printf("\nThe format is wrong. The length should be four to eight characters and contains no illegal characters!\n");
            printf("\nPlease enter a corrcet username: ");
            continue;
        }else break;
    }
    printf("Please enter a password: ");
    while(1){
        fgets(password, 10, stdin);
        removenewline(password);
        if(checkcontent(password) == 0){
            printf("The format is wrong. The length should be four to eight characters and contains no illegal characters!\n");
            printf("\nPlease enter a corrcet password: ");
            continue;
        }else break;
    }
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
    fp = fopen(userfilename,"a");
    fprintf(fp,"%s\n%s\n%s\n",name,p->username,p->password);
    fclose(fp);
    return user1;
}

//The user login
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
