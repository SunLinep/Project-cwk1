#include <stdio.h>
#include <string.h>

typedef struct allbooks{
	char id[100];
	char year[5];
	char copies[100];
	char title[100];
	char authors[100];
	struct allbooks *next;
}bklist;

typedef struct users{
	char username[100];
	char password[100];
}user;

int main(int argc, char **argv){
	char *bookfilename = "bookfile.txt";
	char *userfilename = "users.txt";
	loaduserlist(userfilename);
	loadbooklist(bookfilename);
	return 0;
}

\\注册账号并存在文件里,返回0说明账号已经存在
int register(user *use, char *userfile);{
	FILE *usersfp;
	usersfe = fopen(userfile, "w");
	char username[100];
	char password[100];
	printf("\nPlease enter a username: ");
	scanf("%s",username);
	printf("\nPlease enter a password: ");
	scanf("%s",password);
	user * register = (user*)malloc(sizeof register);
	register = use;
	fprintf(usersfp,"%s\t%s\n",register->username,register->password);
	if(strcmp(register->username, username) == 0) return 0;
	while(register->next != NULL){
		register = register->next;
		fprintf(usersfp,"%s\t%s\n",register->username,register->password);
		if(strcmp(register->username, username) == 0) return 0;
	}
	user * lastuser = (user*)malloc(sizeof lastuser);
	register->next = lastuser;
	lastuser->next = NULL;
	stpcpy(lastuser->username,username);
	strcpy(lastuser->password,password);
	fprintf(usersfp,"%s\t%s\n",lastuser->username,lastuser->password);
	register->next = lastuser->next;
	lastuser = lastuser->next;
	free(register);
	free(lastuser);
	fclose(usersfp);
}

\\加载users文件内容为链表，返回0说明无users文件，返回-1说明该文件为空文件，返回1说明加载成功
int loaduserlist(char *userfile){
	int i = 0;
	FILE * users;
	char content[200];
	user * userfirst = (user*)malloc(sizeof user);
	memset(content, '\0', sizeof(content));
	const char s[2] = "\t";
	if((users = fopen(userfile, "r")) == NULL){
		strcpy(userfirst->username, "librarian");
		strcpy(userfirst->password, "librarian");
		userfirst->next = NULL;
		return 0;
	}else{
		if(fgets(content, 200, users) == NULL){
			strcpy(userfirst->username, "librarian");
			strcpy(userfirst->password, "librarian");
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
	return 1;
}

\\加载bookfile文件内容为链表，返回0说明无bookfile文件，返回-1说明该文件为空文件，返回1说明加载成功
int loadbooklist(char *bookfile){
	int i = 0;
	FILE * book;
	char content[405];
	bklist * bookfirst = (bklist*)malloc(sizeof bklist);
	memset(content, '\0', sizeof(content));
	const char s[2] = "\t";
	if((book = fopen(bookfile, "r")) == NULL){
		return 0;
	}else{
		if(fgets(content, 405, book) == NULL){
			return -1;
		}else{
			bklist * p = (bklist*)malloc(sizeof bklist);
			p = bookfirst;
			p->next = NULL;
			do{
				while (content[i] != '\n') i++;
				content[i] = '\0';
				p->id = strtok(content, s);
				p->year = strtok(NULL, s);
				p->copies = strtok(NULL, s);
				p->title = strtok(NULL, s);
				p->authors = strtok(NULL, s);
				bklist * l= (bklist*)malloc(sizeof bklist);
				l->next = p->next;
				p->next = L;
				p = l;
			}while(fgets(content, 405, book) != NULL)
		}
	}
	return 1;
}


\\主菜单
void mainmenu(void){
	int option;
	printf("\nPlease choose an option:\n1) Register an accoun\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:")
	while(scanf("%d",&option) != 1){
		if(option >=1 && option <= 5) break;
		printf("\nSorry, the option you entered was invalid, please try again.\n");
		printf("\nPlease choose an option:\n1) Register an accoun\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\n Option:")
		fflush(stdin);
	}
	switch(option){
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
	}
}

