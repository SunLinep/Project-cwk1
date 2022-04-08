#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"
#include "user.h"
#include "book_management.h"

int mainmenu(user *userfirst);

int librarianmenu(user* userfirst);

int usermenu(char* name, user* user1);

int main(int argc, char** argv){
    char content[265];
    bookfilename = NULL;
    userfilename = NULL;
    //Detect command line arguments
    memset(content, '\0', sizeof content);
    int i = 1, j = 1, k = 0;
    while(i < argc){
        if(k == 0){
            if((strlen(argv[i])) > 259) {
                printf("The maximum word length of the file name is exceeded");
                break;
            }
            strcpy(content, argv[i]);
            k = 1;
        }else{
            if((strlen(content) + strlen(argv[i]) + 2)> 259){
                printf("The maximum word length of the file name is exceeded");
                break;
            }
            strcat(content, " ");
            strcat(content, argv[i]);
        }
        if(strlen(content) < 4){
            i++;
            continue;
        }
        if(content[strlen(content) - 1] != 't' || content[strlen(content) - 2] != 'x' || content[strlen(content) - 3] != 't' || content[strlen(content) - 4] != '.'){
            i++;
            continue;
        }else{
            if(j == 1){
                bookfilename = (char*) malloc(strlen(content)+1);
                strcpy(bookfilename, content);
                j++;
            }else if(j == 2){
                userfilename = (char*) malloc(strlen(content)+1);
                strcpy(userfilename, content);
                j++;
            }else if(j == 3){
                printf("Invalid input has been ignored!\n");
                break;
            }
            memset(content, '\0', sizeof content);
            k = 0;
        }
        i++;
    }
    if(!bookfilename){
        printf("\nPlease enter a valid bookfilename(ending with.txt): ");
        while(1){
            fgets(content, 265, stdin);
for(i = 0; content[i] != '\n' && i < strlen(content); i++);
	if(i == strlen(content)) while(getchar()!='\n');
            removenewline(content);
            if(strlen(content) < 4){
                printf("\nPlease re-enter a valid bookfilename(ending with.txt): ");
                continue;
            }else if(content[strlen(content) - 1] == 't' && content[strlen(content) - 2] == 'x' && content[strlen(content) - 3] == 't' && content[strlen(content) - 4] == '.'){
                bookfilename = (char*) malloc(strlen(content)+1);
                strcpy(bookfilename, content);
                break;
            }else printf("\nPlease re-enter a valid bookfilename(ending with.txt): ");
        }
    }
    if(!userfilename){
        printf("\nPlease enter a valid userfilename(ending with.txt): ");
        while(1){
            fgets(content, 265, stdin);
for(i = 0; content[i] != '\n' && i < strlen(content); i++);
	if(i == strlen(content)) while(getchar()!='\n');
            removenewline(content);
            if(content[strlen(content) - 1] == 't' && content[strlen(content) - 2] == 'x' && content[strlen(content) - 3] == 't' && content[strlen(content) - 4] == '.'){
                userfilename = (char*) malloc(strlen(content)+1);
                strcpy(userfilename, content);
                break;
            }
            else printf("\nPlease re-enter a valid userfilename(ending with.txt): ");
        }
    }
    user *user1 = (user*)malloc(sizeof user1);
    user1->next = NULL;
	bookfirst = (Book*)malloc(sizeof bookfirst);
    while(mainmenu(user1) == 1);
    return 0;
}

//Main menu and related options
int mainmenu(user *userfirst){
    FILE *fp = NULL;
    user* user2;
    int option, i;
    initlibrary(userfirst, bookfilename, userfilename, fp);
    option = typeoption(5, "\nPlease choose an option:\n1) Register an account\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:");
    if(option == 1){
        if((user2= regist(userfirst)) == NULL){
            printf("\nSorry, registration unsuccessful, the username you entered already exists\n");
            fp = fopen(userfilename, "r");
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
for(i = 0; name[i] != '\n' && i < strlen(name); i++);
	if(i == strlen(name)) while(getchar()!='\n');
        removenewline(name);
        printf("Please enter a password: ");
        fgets(pass, 12, stdin);
for(i = 0; pass[i] != '\n' && i < strlen(pass); i++);
	if(i == strlen(pass)) while(getchar()!='\n');
        removenewline(pass);
        i = login(userfirst, name, pass);
        if(i == 0) printf("\nThe entered username or password is incorrect!\n");
        else if(i == 1){
            if((fp = fopen(bookfilename, "r")) == NULL){
                fp = fopen(bookfilename, "w");
                printf("\nLibrary file does not exist, please start creating!\n");
                store_books(fp);
                printf("Successfully created\n");
                fclose(fp);
            }else{
                a = fgetc(fp);
                if(a == EOF){
                    fclose(fp);
                    fp = fopen(bookfilename, "w");
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

//Administrator menu and related options
int librarianmenu(user* userfirst){
    FILE*fp;
        fp = fopen(bookfilename, "r");
        load_books(fp);
    int option, i;
	option = typeoption(5, "\n(logged in as: librarian)\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:");
    if(option == 1){
        char content[100], j;
        Book addbook;
        printf("\nEnter book's title: ");
        while(1){
            fgets(content, 90, stdin);
for(i = 0; content[i] != '\n' && i < strlen(content); i++);
	if(i == strlen(content)) while(getchar()!='\n');
            removenewline(content);
            if(strlen(content) <= 50 && strlen(content) >= 1) break;
            else printf("\nPlease enter correct title: ");
        }
        addbook.title = (char *) malloc(sizeof content);
        strcpy(addbook.title, content);
        printf("\nEnter book's author: ");
        while(1){
            fgets(content, 90, stdin);
for(i = 0; content[i] != '\n' && i < strlen(content); i++);
	if(i == strlen(content)) while(getchar()!='\n');
            removenewline(content);
            if(strlen(content) <= 50 && strlen(content) >= 1) break;
            else printf("\nPlease enter correct authors: ");
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
        else if(i == 0) {
        printf("Add book successfully\n");
        }
    }
    else if(option == 2){
        int a, h = 1, k = 0;
        Book removebook;
        user *p = userfirst;
        displayall();
        Book *q = bookfirst;
        while(q){
            k++;
            q = q->next;
        }
if(k == 1){
	printf("There was only one book left and it could not be deleted\n");
	return 1;
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
	q = bookfirst;
        while(1){
            if(h == a){
                removebook.title = (char *) malloc(200);
                removebook.authors = (char *) malloc(200);
                strcpy(removebook.title, q->title);
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
            fp = fopen(bookfilename,"w");
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

//user menu and related options
int usermenu(char* name, user* user1){
    FILE* fp;
    int option;
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
        a = typeoption(b, "Enter the ID number of book you wish to borrow: ");
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
        fp = fopen(bookfilename, "w");
        q = bookfirst;
        while(q){
            fprintf(fp,"%s\n%s\n%d\n%d\n",q->title,q->authors,q->year,q->copies);
            q = q->next;
        }
        fclose(fp);
        printf("Success comes\n");
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
        fp = fopen(bookfilename, "w");
        q = bookfirst;
        while(q){
            fprintf(fp,"%s\n%s\n%d\n%d\n",q->title,q->authors,q->year,q->copies);
            q = q->next;
        }
        fclose(fp);
        printf("Return the book success\n");
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
    else if(option == 5) {
        printf("\nLogging out...\n");
        return 0;
    }
    return 1;
}



