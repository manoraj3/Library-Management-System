#include<stdio.h>
#include<string.h>
#include"struct.h"

void view_books();

FILE *fp;
static char sflag = 0, sf;
void print_file(int id, char *title, char *author,int qty) 	
{
	short int tlen = strlen(title);
	short int alen = strlen(author);
	short int c;
	if(qty<=9)
		c = 1;
	else if(qty>=10 && qty<=99)
		c = 2;
	else if(qty>=100 && qty<=999)
		c = 3;
	else if (qty>=1000 && qty<=9999)
		c = 4;
	
 
	fprintf(fp,"\t\t\t\t|%d",id);
	for(int i=0;i<10;i++)
		fprintf(fp," ");
	fprintf(fp,"|");

	fprintf(fp,"%s",title);
	for(int i=0;i<22-tlen;i++)
		fprintf(fp," ");
	fprintf(fp,"|");

	fprintf(fp,"%s",author);
	for(int i=0;i<18-alen;i++)
		fprintf(fp," ");
	fprintf(fp,"|");

	fprintf(fp,"%d",qty);
	for(int i=0;i<6-c;i++)
		fprintf(fp," ");
	fprintf(fp,"|");

	fprintf(fp,"\n\t\t\t\t+");
	for(int i=0;i<60;i++)
		fprintf(fp,"-");
	fprintf(fp,"+\n");
}

void save_books()
{
	view_books();

	struct book *ptr = bhead;

	fp = fopen("library_data.txt","w");
	if(fp == 0)
	{
		printf("\nCannot open file for saving\n");
		return;
	}

label:
	printf("\nSave and exit ( enter 'y' )\nExit without saving ( enter 'n' )\nEnter your choice: ");
	scanf(" %c",&sf);

	if(sf == 'y')
	{
		fprintf(fp,"\t\t\t\t+------------------------------------------------------------+\n");
		fprintf(fp,"\t\t\t\t|  ID       |       Title          |      Author      | Qty  |\n");
		fprintf(fp,"\t\t\t\t|------------------------------------------------------------|\n");

		while(ptr != 0)
		{
			sflag = 1;
			print_file(ptr->id, ptr->title, ptr->author, ptr->qty);
			ptr = ptr->next;
		}

		fclose(fp);

		if(sflag == 1)
			printf("\nData saved successfully to 'library_data.txt'\n");
		else
			printf("\nNo records found. Nothing saved.\n");
	}
	else if(sf == 'n')
	{
		fclose(fp);
		printf("\nNo data has been saved\n");
	}
	else
	{
		printf("\nEnter valid input\n");
		goto label;
	}
}
