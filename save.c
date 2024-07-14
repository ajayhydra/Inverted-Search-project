/*
NAME:
DATE:
DESCRIPTION:
SAMPLE I/P:
SAMPLE O/P:
*/

#include "search.h"
#include <stdio.h>
#include<stdio_ext.h>

int save_database(Main_node **index)
{
    char file[20];
    char choice;
    //read the backup file from user
    printf("Enter the file name\n");
    scanf("%s",file);

    //open the file
    FILE *fptr = fopen(file, "w");
    if(fptr != NULL)
    {
	//move the pointer
	fseek(fptr, 0 ,SEEK_END);
	if(fptr != 0)
	{
	    printf("can I overwrite the content (y/n)\n");
	    __fpurge(stdin);
	    scanf("%c",&choice);
	    if(choice == 'n')
	    {
		return failure;
	    }
	}
    }
    for(int key=0; key<27; key++)
    {
	Main_node *temp = index[key];

	if(temp == NULL)
	    continue;
	//iterate till temp not equals null and save the database
	while(temp != NULL)
	{
	    fprintf(fptr, "%s" , "#");
	    fprintf(fptr, "%d;" , key);//print index
	    fprintf(fptr, "%s;" , temp->word);//print word
	    fprintf(fptr, "%d;" , temp->filecount);//printing file count
	    sub_node *stemp = temp->s_link; //travese the sub node
	    while(stemp != NULL)
	    {
		fprintf(fptr,"%s;",stemp->file);//printing file name
		fprintf(fptr,"%d;",stemp->wordcount); //print word count
		stemp = stemp->link;
	    }

	    temp = temp->m_link;
	    fprintf(fptr, "%s" , "#");
	    fprintf(fptr, "%s" , "\n");
	}
    }
    fclose(fptr);//close the file
    return success;
}

