#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"struct.h"

void add_book();
void del_book();
void view_books();
void edit_book();
void issue_book();
void return_book();
void list_issued();
void save_books();
void sort_books();
void search_book();

/* global head pointers */
struct book  *bhead = 0;
struct issue *ihead = 0;

/* global ID counters, kept in sync with data loaded from disk */
int book_count  = 0;
int issue_count = 0;

char ch;

int main()
{
	/* load previously saved books & issue records from disk, if any */
	load_data();

menu:
	system("clear");

	printf("\t\t\t\t\t\t ____________________________________\n");
	printf("\t\t\t\t\t\t|                                    |\n");
	printf("\t\t\t\t\t\t|  **** LIBRARY MANAGEMENT MENU **** |\n");
	printf("\t\t\t\t\t\t|____________________________________|\n");
	printf("\t\t\t\t\t\t|      |                             |\n");
	printf("\t\t\t\t\t\t| A/a  |   Add New Book              |\n");
	printf("\t\t\t\t\t\t|______|_____________________________|\n");
	printf("\t\t\t\t\t\t| D/d  |   Remove a Book             |\n");
	printf("\t\t\t\t\t\t|______|_____________________________|\n");
	printf("\t\t\t\t\t\t| S/s  |   Show All Books            |\n");
	printf("\t\t\t\t\t\t|______|_____________________________|\n");
	printf("\t\t\t\t\t\t| U/u  |   Update Book details       |\n");
	printf("\t\t\t\t\t\t|______|_____________________________|\n");
	printf("\t\t\t\t\t\t| I/i  |   Issue a Book              |\n");
	printf("\t\t\t\t\t\t|______|_____________________________|\n");
	printf("\t\t\t\t\t\t| R/r  |   Return a Book             |\n");
	printf("\t\t\t\t\t\t|______|_____________________________|\n");
	printf("\t\t\t\t\t\t| L/l  |   List Issued Books         |\n");
	printf("\t\t\t\t\t\t|______|_____________________________|\n");
	printf("\t\t\t\t\t\t| T/t  |   Sort Books                |\n");
	printf("\t\t\t\t\t\t|______|_____________________________|\n");
	printf("\t\t\t\t\t\t| F/f  |   Search a Book             |\n");
	printf("\t\t\t\t\t\t|______|_____________________________|\n");
	printf("\t\t\t\t\t\t| V/v  |   Save to File              |\n");
	printf("\t\t\t\t\t\t|______|_____________________________|\n");
	printf("\t\t\t\t\t\t| E/e  |   Exit                      |\n");
	printf("\t\t\t\t\t\t|______|_____________________________|\n");

label:
	printf("\nEnter a corresponding upper or lower case letter for the menu function: ");
	scanf(" %c",&ch);

	switch(ch)
	{
		case'A':
		case'a':
			add_book();
			goto cases;

		case'D':
		case'd':
			del_book();
			goto cases;

		case'S':
		case's':
			view_books();
			goto cases;

		case'U':
		case'u':
			edit_book();
			goto cases;

		case'I':
		case'i':
			issue_book();
			goto cases;

		case'R':
		case'r':
			return_book();
			goto cases;

		case'L':
		case'l':
			list_issued();
			goto cases;

		case'T':
		case't':
			sort_books();
			goto cases;

		case'F':
		case'f':
			search_book();
			goto cases;

		case'V':
		case'v':
			save_books();
			goto cases;

		case'E':
		case'e':
			save_data();
			printf("\nGoodbye!\n\n");
			return 0;

		default:
			printf("\nEnter valid input\n");
			goto label;
	}

cases:
	printf("\nDo you want to go back to menu(if yes enter 'y' (or) exit - enter 'e'): ");
	scanf(" %c",&ch);
	if(ch == 'y')
		goto menu;
	else if(ch == 'e')
	{
		save_data();
		printf("\nGoodbye!\n\n");
		return 0;
	}
	else
	{
		printf("\nEnter valid input\n");
		goto cases;
	}
}
