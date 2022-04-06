#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"
#include "user.h"
#include "book_management.h"

int mainmenu(user *userfirst);

int librarianmenu(user* userfirst);

int usermenu(char* name, user* user1);

int main(void){
    user *user1 = (user*)malloc(sizeof user1);
    user1->next = NULL;
	bookfirst = (Book*)malloc(sizeof bookfirst);
    while(mainmenu(user1) == 1);
    return 0;
}

int mainmenu(user *userfirst){
    FILE *fp = NULL;
    user* user2;
    int option, i;
    initlibrary(userfirst, "book.txt", "user.txt", fp);
    option = typeoption(5, "\nPlease choose an option:\n1) Register an account\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:");
    if(option == 1){
        if((user2= regist(userfirst)) == NULL){
            printf("\nSorry, registration unsuccessful, the username you entered already exists\n");
            fp = fopen("user.txt", "r");
            userfirst = loaduser(userfirst, fp);
            fclose(fp);
        }else{
            userfirst = user2;
            printf("\nRegistered library account successfully!\n");
        }
    }
    else if(option == 2){
        char name[15];
        char pass[15];
        char a;
        printf("\nPlease enter a username: ");
        fgets(name, 12, stdin);
        removenewline(name);
        printf("Please enter a password: ");
        fgets(pass, 12, stdin);
        removenewline(pass);
        i = login(userfirst, name, pass);
        if(i == 0) printf("\nThe entered username or password is incorrect!\n");
        else if(i == 1){
            if((fp = fopen("book.txt", "r")) == NULL){
                fp = fopen("book.txt", "w");
                printf("\nLibrary file does not exist, please start creating!\n");
                store_books(fp);
                printf("Successfully created\n");
                fclose(fp);
            }else{
                a = fgetc(fp);
                if(a == EOF){
                    fclose(fp);
                    fp = fopen("book.txt", "w");
                    printf("\nLibrary files are empty, please start creating!\n");
                    store_books(fp);
                    printf("Successfully created\n");
                    fclose(fp);
                }
            }
            while(librarianmenu(userfirst) == 1);
        }else if(i == 2) while(usermenu(name,userfirst) == 1);
    }
    else if(option == 3){
        int h;
        while(1){
            h = search();
            if(h == 1) printf("The query is successful\n");
            else if(h == 2) printf("There is no book\n");
            else break;
        }
    }
    else if (option == 4) displayall();
    else if(option == 5) return 0;
    return 1;
}

int librarianmenu(user* userfirst){
    FILE*fp;
    int option, i, j;
	option = typeoption(5, "\n(logged in as: librarian)\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:");
    if(option == 1){
        char content[100], j, k;
        Book addbook;
        printf("\nEnter book's title: ");
        while(1){
            fgets(content, 90, stdin);
            while(getchar()!='\n');
            removenewline(content);
            if(strlen(content) <= 50 && strlen(content) >= 1) break;
            else printf("Title is too long, please limit them to 50 characters!\n\nEnter book's title: ");
        }
        addbook.title = (char *) malloc(sizeof content);
        strcpy(addbook.title, content);
        printf("\nEnter book's author: ");
        while(1){
            fgets(content, 90, stdin);
            while(getchar()!='\n');
            removenewline(content);
            if(strlen(content) <= 50 && strlen(content) >= 1) break;
            else printf("Author is too long, please limit them to 50 characters!\n\nEnter book's author:");
        }
        addbook.authors = (char *) malloc(sizeof content);
        strcpy(addbook.authors, content);
        i = typeoption(2022, "Enter book's year: ");
        addbook.year = i;
        printf("Enter book's copies: ");
        while(1){
            j = 0;
            scanf("%d",&i);
            while(getchar() != '\n') j++;
            if(i <= 0 || j > 0) printf("Please enter correct copies (need to be at least 1)!\nEnter book's copies: ");
            else break;
        }
        addbook.copies = i;
        i = add_book(addbook);
        if(i == 1) printf("\nSorry, the book already exists\n");
        else if(i == 0) printf("Add book successfully\n");
    }
    else if(option == 2){
        int a, h = 1, k = 0;
        Book *q = bookfirst;
        Book removebook;
        user *p = userfirst;
        displayall();
        while(p){
            k++;
            p = p->next;
        }
        a = typeoption(k, "Enter book's id: ");
        p = userfirst;
        while(p){
        	k = 0;
        	while(k < 4) {
        		if(p->borrowed[k] == a){
        			printf("Some copies of the book is on loan and cannot be removed\n");
        			return 1;
        		}
        		k++;
        	}
        	p = p->next;
        }
        while(1){
            if(h == a){
                removebook.title = (char *) malloc(sizeof q->title);
                strcpy(removebook.title, q->title);
                removebook.authors = (char *) malloc(sizeof q->authors);
                strcpy(removebook.authors, q->authors);
                break;
            }
            q = q->next;
            h++;
        }
        i = remove_book(removebook);
        if(i==0) printf("\nSorry, this book doesn't exist\n");
        else{
            q = bookfirst;
            fp = fopen("book.txt","w");
            while(q){
                fprintf(fp,"%s\n%s\n%d\n%d\n",q->title,q->authors,q->year,q->copies);
                q = q->next;
            }
            fclose(fp);
            p = userfirst;
            fp = fopen("borrow.txt", "w");
            for(p = userfirst, h = 0; p; p = p->next, h = 0){
                while(p->borrowed[h] != -1) h++;
                if(h == 0) continue;
                k = 0;
                while(k < 4) {
                    if(p->borrowed[k] > a){
                        p->borrowed[k]--;
                    }
                    k++;
                }
                fprintf(fp,"%s\n%d\n",p->username,h);
                k = 0;
                while(p->borrowed[k] != -1 && k < h){
                    fprintf(fp,"%d\n",p->borrowed[k]);
                    k++;
                }
            }
            fclose(fp);
            printf("The book has been successfully deleted");
        }
    }
    else if(option == 3){
        int h;
        while(1){
            h = search();
            if(h == 1) printf("The query is successful\n");
            else if(h == 2) printf("There is no book\n");
            else break;
        }
    }
    else if (option == 4) displayall();
    else if(option == 5){
        printf("\nLogging out...\n");
        return 0;
    }
    return 1;
}

int usermenu(char* name, user* user1){
    FILE* fp;
    int option, i;
    char menu[200] = "\n(logged in as: ";
    strcat(menu, name);
    strcat(menu, ")\nPlease choose an option:\n1) Borrow a book\n2) Return a book\n3) Search for books\n4) Display all books\n5) log out\n Option:");
	option = typeoption(5, menu);
    if(option == 1){
        user *p = user1;
        Book *q = bookfirst;
        int a, num = 0,  b = 1, k, h;
        while (p){
            if(strcmp(p->username, name) == 0) break;
            p = p->next;
        }
        displayborrowed(p);
        while(p->borrowed[num] != -1) num++;
        while(q){
            b++;
            q = q->next;
        }
        printf("Enter the ID number of book you wish to borrow: ");
        scanf("%d",&a);
        for(k = 0; k < 4; k++){
            if(p->borrowed[k] == a){
                printf("You have borrowed the book\n");
                return 1;
            }
        }
        if(a>=b || a<=0) {
            printf("Sorry, the option you entered was invalid\n");
            return 1;
        }
        if(num == 4) {
            printf("You have borrowed four books, you can't borrow any more\n");
            return 1;
        }
        q = bookfirst;
        b = a;
        while(b > 1){
            q = q->next;
            b--;
        }
        if(q->copies == 0){
            printf("This book has been checked out\n");
            return 1;
        }
        b = 0;
        while (p->borrowed[b] != -1) b++;
        p->borrowed[b] = a;
        b= 3;
        while(b > 0){
            if(p->borrowed[b] < p->borrowed[b-1] && p->borrowed[b]!=-1){
                h = p->borrowed[b-1];
                p->borrowed[b-1] = p->borrowed[b];
                p->borrowed[b] = h;
            }
            b--;
        }
        q = bookfirst;
        b = a;
        while(b > 1){
            q = q->next;
            b--;
        }
        q->copies--;
        fp = fopen("borrow.txt", "w");
        p = user1;
        for(num = 0; p; p = p->next, num = 0){
            while(p->borrowed[num] != -1) num++;
            if(num == 0) continue;
            fprintf(fp,"%s\n%d\n",p->username,num);
            b = 0;
            while(p->borrowed[b] != -1 && b < num){
                fprintf(fp,"%d\n",p->borrowed[b]);
                b++;
            }
        }
        fclose(fp);
        fp = fopen("book.txt", "w");
        q = bookfirst;
        while(q){
            fprintf(fp,"%s\n%s\n%d\n%d\n",q->title,q->authors,q->year,q->copies);
            q = q->next;
        }
        fclose(fp);
        printf("Success comes\n");
        return  1;
    }
    else if(option == 2){
        user *p = user1;
        Book *q = bookfirst;
        int a,num = 0, b = 0;
        while (p){
            if(strcmp(p->username, name) == 0) break;
            p = p->next;
        }
        displayborrowed(p);
        while(p->borrowed[num] != -1) num++;
        printf("Enter the ID number of book you wish to return: ");
        scanf("%d",&a);
        while(p->borrowed[b] != a){
            b++;
            if(b > 4) break;
        }
        if(b > 4) {
            printf("You haven't borrowed this book\n");
            return 1;
        }
        num--;
        p->borrowed[b] = -1;
        b = 0;
        while(b < 3){
            if(p->borrowed[b] == -1){
                p->borrowed[b] = p->borrowed[b+1];
                p->borrowed[b+1] =-1;
            }
            b++;
        }
        b = 1;
        q = bookfirst;
        while(b < a){
            q = q->next;
            b++;
        }
        q->copies++;
        fp = fopen("borrow.txt", "w");
        for(p = user1, num = 0; p; p = p->next, num = 0){
            while(p->borrowed[num] != -1) num++;
            if(num == 0) continue;
            fprintf(fp,"%s\n%d\n",p->username,num);
            b = 0;
            while(p->borrowed[b] != -1 && b < num){
                fprintf(fp,"%d\n",p->borrowed[b]);
                b++;
            }
        }
        fclose(fp);
        fp = fopen("book.txt", "w");
        q = bookfirst;
        while(q){
            fprintf(fp,"%s\n%s\n%d\n%d\n",q->title,q->authors,q->year,q->copies);
            q = q->next;
        }
        fclose(fp);
        printf("Return the book success\n");
        return 1;
    }
    else if(option == 3){
        fp = fopen("book.txt", "r");
        load_books(fp);
        int h;
        while(1){
            h = search();
            if(h == 1){
                printf("The query is successful\n");
            }else if(h == 2){
                printf("There is no book\n");
            }else break;
        }
        return 1;
    }
    else if (option == 4){
        fp = fopen("book.txt","r");
        load_books(fp);
        displayall();
        return 1;
    }
    else if(option == 5) {
        printf("\nLogging out...\n");
        return 0;
    }
    return 1;
}

