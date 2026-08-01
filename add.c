#include<stdio.h>
#include<stdlib.h>
#include"struct.h"

void add_book()
{
	char ch;
	do
	{
		struct book *temp;
		temp = (struct book*)malloc(sizeof(struct book));
		temp->next = 0;

		temp->id = ++book_count;

		printf("\nEnter the title: ");
		scanf(" %[^\n]", temp->title);

		printf("\nEnter the author: ");
		scanf(" %[^\n]", temp->author);

qty:
		printf("\nEnter the quantity: ");
		while(scanf("%d", &temp->qty) != 1)
		{
			scanf(" %*s");
			printf("\nEnter valid input\n");
			goto qty;
		}
		if(temp->qty < 0)
		{
			printf("\nQuantity cannot be negative\n");
			goto qty;
		}

		/* append to end of list */
		if(bhead == 0)
			bhead = temp;
		else
		{
			struct book *last = bhead;
			while(last->next != 0)
				last = last->next;
			last->next = temp;
		}

		/* persist immediately so the record survives a restart */
		save_books_data();

		printf("\n\t\t\t\tBook added with ID: %d\n", temp->id);

label:
		printf("\nDo you want to add another book(if yes enter 'y' or if no enter 'n'): ");
		scanf(" %c",&ch);
		if(ch == 'y')
			continue;
		else if(ch == 'n')
			break;
		else
		{
			printf("\nEnter valid input\n");
			goto label;
		}

	}while(1);
}
