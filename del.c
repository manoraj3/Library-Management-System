#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"struct.h"

void view_books();
void print_book(int, char*, char*, int);
void id_del();
void title_del();
void show_book(struct book *);

char dch;
int  dflag = 0;

void del_book()
{
	dflag = 0;

menu:
	system("clear");

	printf("\t\t\t\t\t\t _____________________________________\n");
	printf("\t\t\t\t\t\t|                                     |\n");
	printf("\t\t\t\t\t\t|             Delete Menu             |\n");
	printf("\t\t\t\t\t\t|_____________________________________|\n");
	printf("\t\t\t\t\t\t|      |                              |\n");
	printf("\t\t\t\t\t\t| I/i  |   Delete by Book ID          |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");
	printf("\t\t\t\t\t\t| T/t  |   Delete by Title            |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");

	printf("\nEnter your choice 'I/i' or 'T/t': ");
	scanf(" %c",&dch);

	switch(dch)
	{
		case'I':
		case'i':
			id_del();
			break;

		case'T':
		case't':
			title_del();
			view_books();
			break;

		default:
			printf("\nEnter valid input\n");
			sleep(2);
			goto menu;
	}
}

void show_book(struct book *ptr)
{
	if(dflag == 0)
	{
		printf("\t\t\t\t+------------------------------------------------------------+\n");
		printf("\t\t\t\t|  ID       |       Title          |      Author      | Qty  |\n");
		printf("\t\t\t\t|------------------------------------------------------------|\n");
	}
	dflag = 1;
	print_book(ptr->id, ptr->title, ptr->author, ptr->qty);
}

void id_del()
{
	int num;
	char op;
	struct book *temp, *prev, *temp1;
	temp = prev = temp1 = bhead;
	dflag = 0;
	printf("\nEnter Book ID to delete: ");
	scanf("%d",&num);

	/* first find and show it */
	while(temp1 != 0)
	{
		if(temp1->id == num)
		{
			show_book(temp1);
			break;
		}
		temp1 = temp1->next;
	}
	if(temp1 == 0)
	{
		printf("\nNo book found with ID %d\n", num);
		sleep(2);
		return;
	}

g:
	printf("\nDo you want to delete this record(if yes enter 'y' or no enter 'n'): ");
	scanf(" %c",&op);
	if(op == 'y')
		goto go;
	else if(op == 'n')
		return;
	else
	{
		printf("\nEnter valid input\n");
		goto g;
	}

go:
	temp = prev = bhead;
	while(temp != 0)
	{
		if(temp->id == num)
		{
			if(temp == bhead)
				bhead = temp->next;
			else
				prev->next = temp->next;
			free(temp);
			break;
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
	printf("\nDeleted successfully...\n");
}

/* search by title, then call id_del for confirmation */
void title_del()
{
	char t[50];
	struct book *temp = bhead;

	printf("\nEnter title to delete: ");
	scanf(" %[^\n]", t);

	while(temp != 0)
	{
		if(strcmp(temp->title, t) == 0)
			show_book(temp);
		temp = temp->next;
	}

	if(dflag == 0)
	{
		printf("\nNo book found with title '%s'\n", t);
		sleep(2);
		return;
	}

	id_del();
}
