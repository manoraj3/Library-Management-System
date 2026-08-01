#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"struct.h"

#define BOOK_FILE  "books.dat"
#define ISSUE_FILE "issues.dat"

/*
 * Loads every book and issue record from disk into the linked lists.
 * Call this ONCE, right at the start of main(), before the menu loop.
 * If the files don't exist yet (first ever run) it just leaves the
 * lists empty, which is fine.
 */
void load_data(void)
{
	FILE *fp;
	struct book  *b, *blast = 0;
	struct issue *i, *ilast = 0;

	bhead = 0;
	ihead = 0;
	book_count  = 0;
	issue_count = 0;

	/* ---- books ---- */
	fp = fopen(BOOK_FILE, "rb");
	if(fp != 0)
	{
		struct book tmp;
		while(fread(&tmp, sizeof(struct book), 1, fp) == 1)
		{
			b = (struct book*)malloc(sizeof(struct book));
			*b = tmp;
			b->next = 0;

			if(bhead == 0)
				bhead = b;
			else
				blast->next = b;
			blast = b;

			if(b->id > book_count)
				book_count = b->id;
		}
		fclose(fp);
	}

	/* ---- issue records ---- */
	fp = fopen(ISSUE_FILE, "rb");
	if(fp != 0)
	{
		struct issue tmp;
		while(fread(&tmp, sizeof(struct issue), 1, fp) == 1)
		{
			i = (struct issue*)malloc(sizeof(struct issue));
			*i = tmp;
			i->next = 0;

			if(ihead == 0)
				ihead = i;
			else
				ilast->next = i;
			ilast = i;

			if(i->issue_id > issue_count)
				issue_count = i->issue_id;
		}
		fclose(fp);
	}
}

/* Overwrite books.dat with the current in-memory list */
void save_books_data(void)
{
	FILE *fp = fopen(BOOK_FILE, "wb");
	struct book *ptr = bhead;

	if(fp == 0)
	{
		printf("\nWarning: could not save book data to disk\n");
		return;
	}

	while(ptr != 0)
	{
		fwrite(ptr, sizeof(struct book), 1, fp);
		ptr = ptr->next;
	}
	fclose(fp);
}

/* Overwrite issues.dat with the current in-memory list */
void save_issues_data(void)
{
	FILE *fp = fopen(ISSUE_FILE, "wb");
	struct issue *ptr = ihead;

	if(fp == 0)
	{
		printf("\nWarning: could not save issue data to disk\n");
		return;
	}

	while(ptr != 0)
	{
		fwrite(ptr, sizeof(struct issue), 1, fp);
		ptr = ptr->next;
	}
	fclose(fp);
}

/* Save everything (used before exit as a safety net) */
void save_data(void)
{
	save_books_data();
	save_issues_data();
}
