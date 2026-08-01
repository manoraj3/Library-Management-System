#include<stdio.h>
#include<string.h>
#include"struct.h"

/* helper: find book title by id */
static char* book_title(int id)
{
	struct book *ptr = bhead;
	while(ptr != 0)
	{
		if(ptr->id == id)
			return ptr->title;
		ptr = ptr->next;
	}
	return "Unknown";
}

void list_issued()
{
	struct issue *ptr = ihead;

	if(ptr == 0)
	{
		printf("\n\t\t\t\t No issue records found\n");
		return;
	}

	printf("\n\t\t\t\t+-----------------------------------------------------------------------------------------------+\n");
	printf("\t\t\t\t| IssID | BkID | Title            | UsrID | User Name  |Issue        |Due          |Status      |\n");
	printf("\t\t\t\t|-----------------------------------------------------------------------------------------------|\n");

	while(ptr != 0)
	{
		char *status = ptr->is_returned ? "Returned" : "Active  ";

		printf("\t\t\t\t| %-5d | %-4d | %-16.16s | %-5d | %-10.10s | %-11s | %-11s | %-10s |\n",
			ptr->issue_id,
			ptr->book_id,
			book_title(ptr->book_id),
			ptr->user_id,
			ptr->user_name,
			ptr->issue_date,
			ptr->due_date,
			status);

        	printf("\t\t\t\t|-----------------------------------------------------------------------------------------------|\n");
		
		ptr = ptr->next;
	}
}
