#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"struct.h"

void print_book(int, char*, char*, int);
void show_bk(struct book *);
void modify_fields(struct book **);
void modify_by_name();

int echeck = 0;

void edit_book()
{
	echeck = 0;
	char ch;
	int  num;
	struct book *temp = bhead;

menu:
	system("clear");

	printf("\t\t\t\t\t\t _____________________________________\n");
	printf("\t\t\t\t\t\t|                                     |\n");
	printf("\t\t\t\t\t\t|     Enter which record to search    |\n");
	printf("\t\t\t\t\t\t|          for modification           |\n");
	printf("\t\t\t\t\t\t|_____________________________________|\n");
	printf("\t\t\t\t\t\t|      |                              |\n");
	printf("\t\t\t\t\t\t| I/i  |   Search by Book ID          |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");
	printf("\t\t\t\t\t\t| T/t  |   Search by Title            |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");

	printf("\nEnter your choice: ");
	scanf(" %c",&ch);

	if((ch == 'i') || (ch == 'I'))
	{
		printf("\nEnter the Book ID: ");
		scanf("%d",&num);
		while(temp)
		{
			if(temp->id == num)
			{
				show_bk(temp);
				modify_fields(&temp);
				break;
			}
			temp = temp->next;
		}
		if(temp == 0)
		{
			printf("\nNo data found\n");
			sleep(3);
			return;
		}
	}
	else if((ch == 't') || (ch == 'T'))
	{
		char t[50];
		printf("\nEnter the title: ");
		scanf(" %[^\n]", t);

		while(temp != 0)
		{
			if(strcmp(temp->title, t) == 0)
				show_bk(temp);
			temp = temp->next;
		}
		modify_by_name();
	}
	else
	{
		printf("\nEnter valid input\n");
		sleep(2);
		goto menu;
	}
}

/* show one book row with header on first call */
void show_bk(struct book *ptr)
{
	if(echeck == 0)
	{
		printf("\t\t\t\t+------------------------------------------------------------+\n");
		printf("\t\t\t\t|  ID       |       Title          |      Author      | Qty  |\n");
		printf("\t\t\t\t|------------------------------------------------------------|\n");
	}
	echeck = 1;
	print_book(ptr->id, ptr->title, ptr->author, ptr->qty);
}

/* ask which field to modify, used after search by ID */
void modify_fields(struct book **ptr)
{
	char c;

	printf("\t\t\t\t\t\t _____________________________________\n");
	printf("\t\t\t\t\t\t|                                     |\n");
	printf("\t\t\t\t\t\t| Enter which field to modify         |\n");
	printf("\t\t\t\t\t\t|_____________________________________|\n");
	printf("\t\t\t\t\t\t|      |                              |\n");
	printf("\t\t\t\t\t\t| T/t  |   Title                      |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");
	printf("\t\t\t\t\t\t| A/a  |   Author                     |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");
	printf("\t\t\t\t\t\t| Q/q  |   Quantity                   |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");

	printf("\nEnter the choice: ");
	scanf(" %c",&c);

	if((c == 't') || (c == 'T'))
	{
		printf("\nEnter the new title: ");
		scanf(" %[^\n]", (*ptr)->title);
	}
	else if((c == 'a') || (c == 'A'))
	{
		printf("\nEnter the new author: ");
		scanf(" %[^\n]", (*ptr)->author);
	}
	else if((c == 'q') || (c == 'Q'))
	{
		printf("\nEnter the new quantity: ");
		scanf("%d", &(*ptr)->qty);
	}
	else
	{
		printf("\nEnter valid input\n");
		return;
	}

	printf("\n\t\t\t\tUpdated record\n");
	printf("\t\t\t\t+------------------------------------------------------------+\n");
	printf("\t\t\t\t|  ID       |       Title          |      Author      | Qty  |\n");
	printf("\t\t\t\t|------------------------------------------------------------|\n");
	print_book((*ptr)->id, (*ptr)->title, (*ptr)->author, (*ptr)->qty);
}

/* used after search by name: ask ID then modify */
void modify_by_name()
{
	int roll;
	struct book *ptr = bhead;
	echeck = 0;
	printf("\nEnter the Book ID for modification: ");
	scanf("%d",&roll);

	while(ptr)
	{
		if(ptr->id == roll)
		{
			show_bk(ptr);
			modify_fields(&ptr);
			return;
		}
		ptr = ptr->next;
	}
	printf("\nNo Data Found\n");
	sleep(2);
}
