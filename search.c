#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<unistd.h>
#include"struct.h"

void print_book(int, char*, char*, int);

int sflag = 0;

void show_search(struct book *ptr)
{
	if(sflag == 0)
	{
		printf("\t\t\t\t+------------------------------------------------------------+\n");
		printf("\t\t\t\t|  ID       |       Title          |      Author      | Qty  |\n");
		printf("\t\t\t\t|------------------------------------------------------------|\n");
	}
	sflag = 1;
	print_book(ptr->id, ptr->title, ptr->author, ptr->qty);
}

void search_by_id()
{
	int num;
	struct book *ptr = bhead;

	printf("\nEnter Book ID to search: ");
	scanf("%d",&num);

	while(ptr != 0)
	{
		if(ptr->id == num)
		{
			show_search(ptr);
			return;
		}
		ptr = ptr->next;
	}
	printf("\nNo book found with ID %d\n", num);
	sleep(2);
}

void search_by_title()
{
	char t[50];
	struct book *ptr = bhead;

	sflag = 0;
	printf("\nEnter title to search: ");
	scanf(" %[^\n]", t);

	while(ptr != 0)
	{
		if(strcasecmp(ptr->title, t) == 0)
			show_search(ptr);
		ptr = ptr->next;
	}
	if(sflag == 0)
		printf("\nNo book found with title '%s'\n", t);
}

void search_by_author()
{
	char a[50];
	struct book *ptr = bhead;

	sflag = 0;
	printf("\nEnter author name to search: ");
	scanf(" %[^\n]", a);

	while(ptr != 0)
	{
		if(strcasecmp(ptr->author, a) == 0)
			show_search(ptr);
		ptr = ptr->next;
	}
	if(sflag == 0)
		printf("\nNo book found by author '%s'\n", a);
}

void search_book()
{
	char choice;
	sflag = 0;

menu:
	system("clear");

	printf("\t\t\t\t\t\t _____________________________________\n");
	printf("\t\t\t\t\t\t|                                     |\n");
	printf("\t\t\t\t\t\t|             Search Menu             |\n");
	printf("\t\t\t\t\t\t|_____________________________________|\n");
	printf("\t\t\t\t\t\t|      |                              |\n");
	printf("\t\t\t\t\t\t| I/i  |   Search by Book ID          |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");
	printf("\t\t\t\t\t\t| T/t  |   Search by Title            |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");
	printf("\t\t\t\t\t\t| A/a  |   Search by Author           |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");

	printf("\nEnter your choice: ");
	scanf(" %c",&choice);

	switch(choice)
	{
		case'I':
		case'i':
			search_by_id();
			break;

		case'T':
		case't':
			search_by_title();
			break;

		case'A':
		case'a':
			search_by_author();
			break;

		default:
			printf("\nEnter valid input\n");
			sleep(2);
			goto menu;
	}
}
