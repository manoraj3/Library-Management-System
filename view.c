#include<stdio.h>
#include"struct.h"

void print_book(int, char*, char*, int);

void view_books()
{
	if(bhead != 0)
	{
		struct book *ptr = bhead;

		printf("\t\t\t\t+------------------------------------------------------------+\n");
		printf("\t\t\t\t|  ID       |       Title          |      Author      | Qty  |\n");
		printf("\t\t\t\t|------------------------------------------------------------|\n");

		while(ptr != 0)
		{
			print_book(ptr->id, ptr->title, ptr->author, ptr->qty);
			ptr = ptr->next;
		}
	}
	else
		printf("\n\t\t\t\t No book records found\n");
}
