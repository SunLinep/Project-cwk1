#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "book_mangement.h"

Book * bookfirst = (Book*)malloc(sizeof Book);
bookfirst->next = NULL;

int store_books(FILE *file){
	if(bookfirst->id != 1)
}

\\-1说明该文件为空文件
int load_books(FILE *file){
	int i = 0;
	char *content;
	const char s[2] = "\t";
	if(fgets(content,1000,file) == NULL){
		return -1;
	}else{
		Book * p = (Book*)malloc(sizeof Book);
		p = bookfirst;
		do{
			while (content[i] != '\n') i++;
			content[i] = '\0';
			p->id = atoi(strtok(content, s));
			p->title = strtok(NULL, s);
			p->authors = strtok(NULL, s);
			p->year = atoi(strtok(NULL, s));
			p->copies = atoi(strtok(NULL, s));
			Book * l= (Book*)malloc(sizeof Book);
			l->next = p->next;
			p->next = l;
			p = l;
			memset(content, '\0', sizeof(content));
		}while(fgets(content, 405, book) != NULL)
		l = l->next;
		free(p);
		free(l);
	}
	return 0;
}

int add_book(Book book){
	int i = 1;
	Book * p = (Book*)malloc(sizeof Book);
	p = bookfirst;
	while(p->next != NULL){
		i++;
		p = p->next;
	}
	p->next = book;
	book->next = NULL;
	book->id = ++i;
	p = book->next;
	free(p);
	return 0;
}

int remove_book(Book book){
	Book * p = (Book*)malloc(sizeof Book);
	p = bookfirst;
	while(p->next != book){
		p = p->next;
	}
	p->next = book->next
	book->next = NULL;
	p = p->next;
	while(p != NULL){
		p->id--;
		p = p->next;
	}
	free(p);
	free(book);
	return 0;
}

BookList find_book_by_title (const char *title){
	int i = 0;
	Book * p = (Book*)malloc(sizeof Book);
	Book * h = (Book*)malloc(sizeof Book);
	Book * (l->list) = (Book*)malloc(sizeof Book);
	BookList * l = (BookList*)malloc(sizeof BookList);
	p = bookfirst;
	while(p != NULL){
		if(strcmp(p->title, title) == 0){
			l->list->id = p->id;
			l->list->year = p->year;
			l->list->copies = p->copies;
			l->list->title = p->title;
			l->list->authors = p->authors;
			h = l->list->next;
			p = p->next;
			i++;
			break;
		}
		p = p->next;
	}
	while(p != NULL){
		if(strcmp(p->title, title) == 0){
			h->id = p->id;
			h->year = p->year;
			h->copies = p->copies;
			h->title = p->title;
			h->authors = p->authors;
			h = h->next;
			i++;
		}
		p = p->next;
	}
	h = NULL;
	free(h);
	l->length=i;
	return l;
}

BookList find_book_by_author (const char *author){
	int i = 0;
	Book * p = (Book*)malloc(sizeof Book);
	Book * h = (Book*)malloc(sizeof Book);
	Book * (l->list) = (Book*)malloc(sizeof Book);
	BookList * l = (BookList*)malloc(sizeof BookList);
	p = bookfirst;
	while(p != NULL){
		if(strcmp(p->author, author) == 0){
			l->list->id = p->id;
			l->list->year = p->year;
			l->list->copies = p->copies;
			l->list->title = p->title;
			l->list->authors = p->authors;
			h = l->list->next;
			p = p->next;
			i++;
			break;
		}
		p = p->next;
	}
	while(p != NULL){
		if(strcmp(p->author, author) == 0){
			h->id = p->id;
			h->year = p->year;
			h->copies = p->copies;
			h->title = p->title;
			h->authors = p->authors;
			h = h->next;
			i++;
		}
		p = p->next;
	}
	h = NULL;
	free(h);
	l->length=i;
	return l;
}

BookList find_book_by_year (unsigned int year){
	int i = 0;
	Book * p = (Book*)malloc(sizeof Book);
	Book * h = (Book*)malloc(sizeof Book);
	Book * (l->list) = (Book*)malloc(sizeof Book);
	BookList * l = (BookList*)malloc(sizeof BookList);
	p = bookfirst;
	while(p != NULL){
		if(p->year == year){
			l->list->id = p->id;
			l->list->year = p->year;
			l->list->copies = p->copies;
			l->list->title = p->title;
			l->list->authors = p->authors;
			h = l->list->next;
			p = p->next;
			i++;
			break;
		}
		p = p->next;
	}
	while(p != NULL){
		if(p->year == year){
			h->id = p->id;
			h->year = p->year;
			h->copies = p->copies;
			h->title = p->title;
			h->authors = p->authors;
			h = h->next;
			i++;
		}
		p = p->next;
	}
	h = NULL;
	free(h);
	l->length=i;
	return l;
}