#include <stdio.h>
#include "book_management.h"

typedef struct users{
	char username[100];
	char password[100];
}user;

Book * bookfirst = (Book*)malloc(sizeof Book);
bookfirst->next = NULL;
User * firstuser = (user*)malloc(sizeof User);
firstuser->username =  "librarian";
firstuser->password = "librarian";
firstuser->next = NULL;
char *bookfilename = "bookfile.txt";
char *userfilename = "users.txt";

int mainMenu(){
	int option;
	loaduserlist(userfilename);
	printf("\nPlease choose an option:\n1) Register an accoun\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:")
	while(scanf("%d",&option) != 1){
		if(option >=1 && option <= 5) break;
		printf("\nSorry, the option you entered was invalid, please try again.\n");
		printf("\nPlease choose an option:\n1) Register an accoun\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:")
		fflush(stdin);
	}
	switch(option){
		case 1:
			register(userfilename);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			displayBooks(bookfilename);
			break;
		case 5:
			break;
	}
}

void searchbook(int user){
	int option;
	printf("\nPlease choose an option:\n1)Find books by title\n2)Find Books by author\n3)Find books by year\n4)Return to previous menu\n Option:")
	while(scanf("%d",&option) != 1){
		if(option >=1 && option <= 4) break;
		printf("\nSorry, the option you entered was invalid, please try again.\n");
		printf("\nPlease choose an option:\n1)Find books by title\n2)Find Books by author\n3)Find books by year\n4)Return to previous menu\n Option:")
		fflush(stdin);
	}
	switch(option){
		case 1:
			char *q;
			char *tle = "Title";
			char *aut = "Authors";
			printf("Please enter title: ");
			scanf("%s",q);
			BookList*p = (BookList*)malloc(sizeof Booklist);
			Book*a = (Book*)malloc(sizeof Booklist);
			p = find_book_by_title(q);
			a = p->list;
			printf("ID\t%50c%50cyear\tcopies",tle,aut);
			while(p->length > 0){
				printf("%d\t%50c%50c%d\t%d",a->id,a->title,a->authors,a->year,a->copies);
				a = a->next;
			}
			searchbook(user);
			break;
		case 2:
			char *q;
			char *tle = "Title";
			char *aut = "Authors";
			printf("Please enter author: ");
			scanf("%s",q);
			BookList*p = (BookList*)malloc(sizeof Booklist);
			Book*a = (Book*)malloc(sizeof Booklist);
			p = find_book_by_author(q);
			a = p->list;
			printf("ID\t%50c%50cyear\tcopies",tle,aut);
			while(p->length > 0){
				printf("%d\t%50c%50c%d\t%d",a->id,a->title,a->authors,a->year,a->copies);
				a = a->next;
			}
			searchbook(user);
			break;
		case 3:
			int q;
			char *tle = "Title";
			char *aut = "Authors";
			printf("Please enter year: ");
			scanf("%d",q);
			BookList*p = (BookList*)malloc(sizeof Booklist);
			Book*a = (Book*)malloc(sizeof Booklist);
			p = find_book_by_year(q);
			a = p->list;
			printf("ID\t%50c%50cyear\tcopies",tle,aut);
			while(p->length > 0){
				printf("%d\t%50c%50c%d\t%d",a->id,a->title,a->authors,a->year,a->copies);
				a = a->next;
			}
			searchbook(user);
			break;
		case 4:
		printf("Returning to previous menu...");
			if(user){
				login_librarian();
			}else{
				login_user();
			}
			break;
	}
}

void login_librarian(void){
	int option;
	printf("\n(logged in as: librarian)\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:")
	while(scanf("%d",&option) != 1){
		if(option >=1 && option <= 5) break;
		printf("\nSorry, the option you entered was invalid, please try again.\n");
		printf("\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:")
		fflush(stdin);
	}
	switch(option){
		case 1:
			Book *p = (Book*)malloc(sizeof Book);
			p->next = NULL;
			printf("Enter the title of the book you wish to add: ");
			scanf("%s",p->title);
			getchar();
			printf("Enter the author of the book you wish to add:");
			scanf("%s",p->authors);
			getchar();
			printf("Enter the year that the book you wish to add was released: ");
			scanf("%d",p->year);
			getchar();
			printf("Enter the number of copies of the book that you wish to add: ");
			scanf("%d",p->copies);
			if(add_book(p)){
				printf("Sorry, you attempted to add an invalid book, please try agagin\n");
			}else{
				printf("Book was successfully added");
			}
			free(p);
			break;
		case 2:
			Book *p = (Book*)malloc(sizeof Book);
			p->next = NULL;
			printf("Enter the title of the book you wish to add: ");
			scanf("%s",p->title);
			getchar();
			printf("Enter the author of the book you wish to add:");
			scanf("%s",p->authors);
			getchar();
			if(remove_book(p)){
				printf("Sorry, you attempted to remove an invalid book, please try agagin\n");
			}else{
				printf("Book was successfully removed");
			}
			break;
		case 3:
			printf("\nLoading search menu...\n");
			searchbook(1);
			break;
		case 4:
			displayBooks(bookfilename);
			break;
		case 5:
			printf("Logging out...");
			mainMenu();
			break;
	}
	login_librarian(void);
}

void login_user(char *name){
	int option;
	printf("\n(logged in as: %s)\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:",name);
	while(scanf("%d",&option) != 1){
		if(option >=1 && option <= 5) break;
		printf("\nSorry, the option you entered was invalid, please try again.\n");
		printf("\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) log out\n Option:")
		fflush(stdin);
	}
	switch(option){
		case 1:
			break;
		case 2:
			break;
		case 3:
			printf("\nLoading search menu...\n");
			searchbook(1);
			break;
		case 4:
			displayBooks(bookfilename);
			break;
		case 5:
			printf("Logging out...");
			mainMenu();
			break;
	}
	login_user(void);
}

void login(User *user){
	char username[100];
	char password[100];
	printf("\nPlease enter a username: ");
	scanf("%s",username);
	printf("\nPlease enter a password: ");
	scanf("%s",password);
	user * users = (user*)malloc(sizeof users);
	users = firstuser;
	if(strcmp(username, "librarian") == 0 && strcmp(password, "librarian") == 0){
		login_librarian();
	}else{
		while(users != NULL){
			if(strcmp(users->username, username) == 0 && strcmp(users->password, password) == 0){
				login_user(users->username);
			}
			users = users->next;	
		}
	}
	free(users);
}

void register(char *userfile);{
	int i = 1;
	FILE *usersfp;
	usersfe = fopen(userfile, "w");
	char username[100];
	char password[100];
	printf("\nPlease enter a username: ");
	scanf("%s",username);
	printf("\nPlease enter a password: ");
	scanf("%s",password);
	user * register = (user*)malloc(sizeof register);
	register = firstuser;
	while(register != NULL){
		fprintf(usersfp,"%s\t%s\n",register->username,register->password);
		if(strcmp(register->username, username) == 0){
			i = 0;
			printf("Sorry, registration unsuccessful, the username you entered already exists");
		}
		register = register->next;
	}
	if(i){
		strcpy(register->username, username);
		stpcpy(register->password, password);
		printf("Registered library account successfully!");
	}
	free(register);
	fclose(usersfp);
}

void loaduserlist(char *userfile){
	int i = 0;
	FILE * users;
	char content[200];
	memset(content, '\0', sizeof(content));
	const char s[2] = "\t";
	if((users = fopen(userfile, "r")) == NULL){
		users = fopen(userfile, "w");
		fprintf(users, "%s\t%s", firstuser->username, firstuser->password);
		fclose(users);
	}else{
		if(fgets(content, 200, users) == NULL){
			userfirst->username = "librarian");
			userfirst->password = "librarian");
			userfirst->next = NULL;
			return -1;
		}else{
			user * q = (user*)malloc(sizeof user);
			q = userfirst;
			q->next = NULL;
			do{
				while (content[i] != '\n') i++;
				content[i] = '\0';
				q->username = strtok(content, s);
				p->password = strtok(NULL, s);
				user * h= (user*)malloc(sizeof user);
				h->next = q->next;
				q->next = h;
				q = h;
				free(h);
			}while(fgets(content, 200, users) != NULL)
		}
	}
	fclose(users);
}

void displayBooks(char *bookfile){
	FILE *bookfp;
	char *tle = "Title";
	char *aut = "Authors";
	Book *p = (Book*)malloc(sizeof Book);
	p = bookfirst;
	if((bookfp = fopen(bookfiile,"r")) != NULL){
		if(!load_books(FILE *file)){
			printf("ID\t%50c%50cyear\tcopies",tle,aut);
			while(p){
				printf("%d\t%50c%50c%d\t%d",p->id,p->title,p->authors,p->year,p->copies);
				p = p->next;
			}
		}else{
			printf("There are no books in the library");
		}
	}
	mainMenu();
}

int main(void){
	mainMenu();
	return 0;
}