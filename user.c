#include "user.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "book_management.h"

Book *bookfirst;

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
        user1->username = (char*) malloc(sizeof "librarian");
        strcpy(user1->username,"librarian");
        user1->password = (char*) malloc(sizeof "librarian");
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
    }
    fclose(file);
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
	int i = 0;
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

//int borrow(char* name, user* user1, Book*book){
//    FILE*fp;
//    user *p = user1;
//    Book *q = bookfirst;
//    Book *a;
//    int i;
//    while(1){
//        if(q==NULL) break;
//        if(strcmp(q->title, book->title) == 0 && strcmp(q->authors, book->authors) == 0){
//            break;
//        }
//        q = q->next;
//    }
//    if(q == NULL) return 1;
//if(q->copies<1) return 3;//这本书已经被借空了
//    while(p){
//        if(strcmp(name, p->username) == 0) {
//        break;
//	}
//        p = p->next;
//    }
//    if(p->borrowed == NULL) {
//        p->borrowed = (BookList*) malloc(sizeof p->borrowed);
//        p->borrowed->list = (Book*) malloc(sizeof p->borrowed->list);
//        p->borrowed->list->title = (char*) malloc(100 * sizeof (char));
//        p->borrowed->list->authors = (char*) malloc(100 * sizeof (char));
//        p->borrowed->length = 0;
//        strcpy(p->borrowed->list->title,book->title);
//        strcpy(p->borrowed->list->authors,book->authors);
//        p->borrowed->length = 1;
//	q->copies--;
//    }else{
//        Book* h = p->borrowed->list;
//i = p->borrowed->length;
//if(i == 3) return 4;
//        while(i>0){
//            if(strcmp(h->authors,book->authors) == 0 && strcmp(h->title,book->title) == 0){
//                return 2;//已经借了这本书
//            }
//            h = h->next;
//i--;
//        }
//        h = p->borrowed->list;
//i = p->borrowed->length;
//        while(i>1){
//	h = h->next;
//i--;
//}
//        Book *k = h;
//        char title[100];
//        char authors[100];
//        strcpy(title,h->title);
//        strcpy(authors,h->authors);
//        h->next = (Book*) malloc(sizeof h->next);
//        strcpy(k->title,title);
//        strcpy(k->title,authors);
//        h = h->next;
//        h->title = (char*) malloc(sizeof book->title);
//	h->authors = (char*) malloc(sizeof book->authors);
//        strcpy(h->title,book->title);
//        strcpy(h->authors,book->authors);
//        p->borrowed->length++;
//        q->copies--;
//    }
//p = user1;
//while(p){
//        if(p->borrowed != NULL)break;
//	p = p->next;
//}
//    fp = fopen("borrow.txt","w");
//    while(1){
//    if(p == NULL) break;
//    if(p->borrowed == NULL){
//    	p = p->next;
//    	continue;
//    }
//    fprintf(fp,"%s\n%d\n",p->username,p->borrowed->length);
//        a = p->borrowed->list;
//        i = p->borrowed->length;
//        while (i > 0){
//               fprintf(fp,"%s\n%s\n",a->title,a->authors);
//			a = a->next;
//	i--;
//	}
//        p = p->next;
//    }
//    fclose(fp);
//    fp = fopen("book.txt","w");
//    q = bookfirst;
//    while(q){
//        fprintf(fp,"%s\n%s\n%d\n%d\n", q->title, q->authors, q->year, q->copies);
//        q = q->next;
//    }
//    fclose(fp);
//    return 0;
//}
//
//int returnbook(char* name, user* user1, Book*book){
//    FILE*fp;
//    user *p = user1;
//    Book *q = bookfirst;
//    Book *a;
//    int i;
//    while(1){
//        if(q==NULL) break;
//        if(strcmp(q->title, book->title) == 0 && strcmp(q->authors, book->authors) == 0){
//            break;
//        }
//        q = q->next;
//    }
//    if(q == NULL) return 1;//书库中没有这本书
//    while(p){
//        if(strcmp(name, p->username) == 0) {
//            break;
//        }
//        p = p->next;
//    }
//    if(p->borrowed == NULL) {
//        return 2;//没有借过这本书
//    }else{
//        int j = 0;
//        Book *b;
//        Book* h = p->borrowed->list;
//        b = h;
//        i = p->borrowed->length;
//        while(i>0){
//            if(strcmp(h->authors,book->authors) == 0 && strcmp(h->title,book->title) == 0){
//                if(j == 0) p->borrowed->list = p->borrowed->list->next;
//                else b->next = h->next;
//                break;
//            }
//            j++;
//            b = h;
//            h = h->next;
//            i--;
//        }
//        if(i == 0) return 2;
//        q = bookfirst;
//        while(1){
//            if(q==NULL) break;
//            if(strcmp(q->title, book->title) == 0 && strcmp(q->authors, book->authors) == 0){
//                q->copies++;
//                break;
//            }
//            q = q->next;
//        }
//    }
//    p = user1;
//    while(p){
//        if(p->borrowed != NULL)break;
//        p = p->next;
//    }
//    fp = fopen("borrow.txt","w");
//    while(1){
//        if(p == NULL) break;
//        if(p->borrowed == NULL){
//            p = p->next;
//            continue;
//        }
//        fprintf(fp,"%s\n%d\n",p->username,p->borrowed->length);
//        a = p->borrowed->list;
//        i = p->borrowed->length;
//        while (i > 0){
//            fprintf(fp,"%s\n%s\n",a->title,a->authors);
//            a = a->next;
//            i--;
//        }
//        p = p->next;
//    }
//    fclose(fp);
//    fp = fopen("book.txt","w");
//    q = bookfirst;
//    while(q){
//        fprintf(fp,"%s\n%s\n%d\n%d\n", q->title, q->authors, q->year, q->copies);
//        q = q->next;
//    }
//    fclose(fp);
//    return 0;
//}
