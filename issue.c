#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include"struct.h"

void print_book(int , char *, char *, int );
static int icount = 0;

/* fill buf with today as DD-MM-YYYY */
static void today(char *buf)
{
	time_t t = time(0);
	struct tm *tm = localtime(&t);
	strftime(buf, 12, "%d-%m-%Y", tm);
}


static void due_date(const char *date, char *result)
{
	struct tm t = {0};
	int d,m,y;
	sscanf(date,"%d-%d-%d",&d,&m,&y);
	t.tm_mday=d; t.tm_mon=m-1; t.tm_year=y-1900; t.tm_isdst=-1;
	time_t ts = mktime(&t);
	ts += 7*86400;
	struct tm *nt = localtime(&ts);
	strftime(result, 12, "%d-%m-%Y", nt);
}

void issue_book()
{
	int bid;
	struct book *bptr = bhead;

	printf("\nEnter Book ID to issue: ");
	scanf("%d",&bid);

	/* find the book */
	while(bptr != 0)
	{
		if(bptr->id == bid)
			break;
		bptr = bptr->next;
	}

	if(bptr == 0)
	{
		printf("\nNo book found with ID %d\n", bid);
		sleep(2);
		return;
	}

	if(bptr->qty <= 0)
	{
		printf("\nSorry, '%s' is out of stock (Qty = 0)\n", bptr->title);
		sleep(2);
		return;
	}

	
	printf("\n\t\t\t\tBook Found:\n");
	printf("\t\t\t\t+------------------------------------------------------------+\n");
	printf("\t\t\t\t|  ID       |       Title          |      Author      | Qty  |\n");
	printf("\t\t\t\t|------------------------------------------------------------|\n");

	print_book(bptr->id,bptr->title,bptr->author,bptr->qty);	

	struct issue *irec;
	irec = (struct issue*)malloc(sizeof(struct issue));
	irec->next = 0;

	irec->issue_id  = ++icount;
	irec->book_id   = bid;
	irec->is_returned = 0;
	irec->return_date[0] = '\0';

	printf("\nEnter User ID  : ");
	scanf("%d",&irec->user_id);

	printf("\nEnter User Name: ");
	scanf(" %[^\n]", irec->user_name);

	today(irec->issue_date);
	due_date(irec->issue_date, irec->due_date);

	bptr->qty--;

	if(ihead == 0)
		ihead = irec;
	else
	{
		struct issue *last = ihead;
		while(last->next != 0)
			last = last->next;
		last->next = irec;
	}

	printf("\n\t\t\t\tIssue Record Created:\n");
	printf("\t\t\t\tIssue ID   : %d\n", irec->issue_id);
	printf("\t\t\t\tBook       : %s\n", bptr->title);
	printf("\t\t\t\tUser       : %s (ID: %d)\n", irec->user_name, irec->user_id);
	printf("\t\t\t\tIssue Date : %s\n", irec->issue_date);
	printf("\t\t\t\tDue Date   : %s\n", irec->due_date);
	printf("\t\t\t\tRemaining  : %d\n", bptr->qty);
}
