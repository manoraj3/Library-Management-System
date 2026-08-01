#include<stdio.h>
#include<string.h>
#include"struct.h"

/* prints one book row inside the table */
void print_book(int id, char *title, char *author, int qty)
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
	
 
	printf("\t\t\t\t|%d",id);
	for(int i=0;i<10;i++)
		printf(" ");
	printf("|");

	printf("%s",title);
	for(int i=0;i<22-tlen;i++)
		printf(" ");
	printf("|");

	printf("%s",author);
	for(int i=0;i<18-alen;i++)
		printf(" ");
	printf("|");

	printf("%d",qty);
	for(int i=0;i<6-c;i++)
		printf(" ");
	printf("|");

	printf("\n\t\t\t\t+");
	for(int i=0;i<60;i++)
		printf("-");
	printf("+\n");
}
