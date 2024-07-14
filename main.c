/*
NAME:G.AJAY KUMAR REDDY
DATE:10/4/2023
DESCRIPTION:INVERTED SEARCH PROJECT IN DATA STRUCTURES
SAMPLE I/P:
SAMPLE O/P:
 */
#include<stdio.h>
#include"search.h"


int main(int argc,char *argv[]) // Main function taking command line arguments
{

    flist *head = NULL;// Declare a pointer to the first node of a linked list
    int opt;
    int flag=0;

    if(argc > 1)  // Check if command line arguments are provided
    {

	if(check_validate_cmd(argv,argc,&head) == success) // Validate command line arguments
	{
	    puts("validation of command line arguments checked succesffully.");
	}
	else
	{
	    puts("ERROR,in the command line arguments.");
	}
	print_list(head); // Print the contents of the linked list

	Main_node *index[27] = {NULL};

	while(1)
	{
	    printf("1.create a database.\n2.display database\n3.search.\n4.save\n5.update the data database\n6.exit\n");

	    printf("enter the option:");
	    scanf("%d",&opt);
	    switch(opt) // Switch case for different menu options
	    {
		case 1:
		    create_database(&head,index);
		    // Create a database
		    flag=1;
		    printf("database was created successfully.\n");
		    break;
		case 2:
		    display(index); // Display the database
		    break;
		case 3:
		    char find[100];
		    printf("enter the word you want to search:");
		    scanf("%s",find); // Read the word to be searched
		    if(search_database(index,find,27) == success)
		    {
			printf("serach database sucessfully completed.\n");
		    }
		    break;
		case 4:
		    if(save_database(index) == success);// Save the database
		    {
			printf("database saved sucessfully.\n");
		    }
		    break;
		case 5:
		    if(flag == 0)
		    {
		    if(update_database(index,&head) == success)  // Update the database
		    {
			printf("\n update database successfully completed.\n");
		    }
		    else
		    {
			printf("update database unsuccessful.\n");

		    }
		    }
		    else
		    {
			printf("ERROR:UPDATE CAN'T DONE AFTER CREATE DATABASE\n.");
		    }
		    break;
		case 6:
		    exit(0);
		    break;
	    }
	}
    }
    else
    {
	puts("enter the file name in command line.");// Prompt to enter file name if no command line argument is provided
    } 
}   

