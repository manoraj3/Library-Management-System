#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include"struct.h"

/* fill buf with today as DD-MM-YYYY */
static void today(char *buf)
{
	time_t t = time(0);
	struct tm *tm = localtime(&t);
	strftime(buf, 12, "%d-%m-%Y", tm);
}

/* compute day difference: date2 - date1 (positive = late) */
static int day_diff(const char *date1, const char *date2)
{
	struct tm t1={0}, t2={0};
	int d,m,y;
	sscanf(date1,"%d-%d-%d",&d,&m,&y);
	t1.tm_mday=d; t1.tm_mon=m-1; t1.tm_year=y-1900; t1.tm_isdst=-1;
	sscanf(date2,"%d-%d-%d",&d,&m,&y);
	t2.tm_mday=d; t2.tm_mon=m-1; t2.tm_year=y-1900; t2.tm_isdst=-1;
	double diff = difftime(mktime(&t2), mktime(&t1));
	return (int)(diff / 86400.0);
}

void return_book()
{
	int bid, uid;
	struct issue *iptr = ihead;
	struct book  *bptr = bhead;

	printf("\nEnter Book ID : ");
	scanf("%d",&bid);
	printf("\nEnter User ID : ");
	scanf("%d",&uid);

	/* find active issue record */
	while(iptr != 0)
	{
		if(iptr->book_id == bid && iptr->user_id == uid && iptr->is_returned == 0)
			break;
		iptr = iptr->next;
	}

	if(iptr == 0)
	{
		printf("\nNo active issue found for Book ID %d and User ID %d\n", bid, uid);
		sleep(2);
		return;
	}

	/* mark returned */
	today(iptr->return_date);
	iptr->is_returned = 1;

	/* restore qty */
	while(bptr != 0)
	{
		if(bptr->id == bid)
		{
			bptr->qty++;
			break;
		}
		bptr = bptr->next;
	}

	/* late fee */
	int late = day_diff(iptr->due_date, iptr->return_date);
	float fee = 0;
	if(late > 0)
		fee = late * 2.0f;

	printf("\n\t\t\t\tReturn Processed Successfully\n");
	printf("\t\t\t\tIssue ID    : %d\n", iptr->issue_id);
	printf("\t\t\t\tUser        : %s (ID: %d)\n", iptr->user_name, iptr->user_id);
	printf("\t\t\t\tIssue Date  : %s\n", iptr->issue_date);
	printf("\t\t\t\tDue Date    : %s\n", iptr->due_date);
	printf("\t\t\t\tReturn Date : %s\n", iptr->return_date);

	if(late > 0)
		printf("\t\t\t\tLate by %d day(s). Fine: Rs. %.2f\n", late, fee);
	else
		printf("\t\t\t\tReturned on time. No fine.\n");
}
