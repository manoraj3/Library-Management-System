#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<unistd.h>
#include"struct.h"

void print_book(int, char*, char*, int);
void sortbyTitle();
void sortbyQty();

void sort_books()
{
	char choice;

	printf("\t\t\t\t\t\t _____________________________________\n");
	printf("\t\t\t\t\t\t|                                     |\n");
	printf("\t\t\t\t\t\t|             Sorting Menu            |\n");
	printf("\t\t\t\t\t\t|_____________________________________|\n");
	printf("\t\t\t\t\t\t|      |                              |\n");
	printf("\t\t\t\t\t\t| T/t  |   Sort by Title              |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");
	printf("\t\t\t\t\t\t| Q/q  |   Sort by Quantity           |\n");
	printf("\t\t\t\t\t\t|______|______________________________|\n");

label:
	printf("\nEnter choice: ");
	scanf(" %c",&choice);

	switch(choice)
	{
		case'T':
		case't':
			sortbyTitle();
			break;

		case'Q':
		case'q':
			sortbyQty();
			break;

		default:
			printf("\nEnter valid input\n");
			goto label;
	}
}

void sortbyTitle()
{
	struct book *ptr = bhead;
	unsigned char ch = 'a';

	if(bhead == 0)
	{
		printf("\nNo data found\n");
		return;
	}

	printf("\t\t\t\t+------------------------------------------------------------+\n");
	printf("\t\t\t\t|  ID       |       Title          |      Author      | Qty  |\n");
	printf("\t\t\t\t|------------------------------------------------------------|\n");

	while(ch <= 'z')
	{
		ptr = bhead;
		while(ptr != 0)
		{
			if((strncasecmp(ptr->title, (char*)&ch, 1)) == 0)
				print_book(ptr->id, ptr->title, ptr->author, ptr->qty);
			ptr = ptr->next;
		}
		ch++;
	}

	printf("\nRecords sorted by Title successfully\n");
}

void sortbyQty()
{
	struct book *ptr = bhead;
	int maxq = 0;

	if(bhead == 0)
	{
		printf("\nNo data found\n");
		return;
	}

	/* find max qty */
	while(ptr != 0)
	{
		if(ptr->qty > maxq)
			maxq = ptr->qty;
		ptr = ptr->next;
	}

	printf("\t\t\t\t+------------------------------------------------------------+\n");
	printf("\t\t\t\t|  ID       |       Title          |      Author      | Qty  |\n");
	printf("\t\t\t\t|------------------------------------------------------------|\n");

	/* print highest qty first */
	while(maxq >= 0)
	{
		ptr = bhead;
		while(ptr != 0)
		{
			if(ptr->qty == maxq)
				print_book(ptr->id, ptr->title, ptr->author, ptr->qty);
			ptr = ptr->next;
		}
		maxq--;
	}

	printf("\nRecords sorted by Quantity successfully\n");
}
