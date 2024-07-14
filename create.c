/*
NAME:
DATE:
DESCRIPTION:
SAMPLE I/P:
SAMPLE O/P:
 */


#include"search.h"

// Function to determine the index of a given string based on its first character
int check_index(char *str)
{
    int index = 0;
    if(str[0] >= 65 && str[0] <= 90)
    {
	index = str[0] + 32;// Convert uppercase to lowercase
    }
    else if(str[0] >= 97 && str[0] <= 122)
    {
	index = str[0] + 0; // Convert lowercase to ASCII value
    }
    else
    {
	index = 26;
    }


    return index;

}

// Function to create the database
int create_database(flist **head, Main_node **index)
{
    flist *temp = *head;// Initialize a temporary pointer to traverse the linked list of filenames

    while (temp != NULL) // Traverse through each filename in the linked list
    {
	FILE *fptr = fopen(temp->data, "r");
	if (fptr == NULL)
	{
	    perror("Error opening file");
	    return failure;
	}

	char string[100];

	 // Read each word from the file until end of file is reached
	while (fscanf(fptr, "%s", string) != EOF)
	{
	    int res = check_index(string);// Get the index of the word

	    if (index[res - 'a'] == NULL)
	    {

		 // Create a new main node and initialize it
		Main_node *new = malloc(sizeof(Main_node));
		if (new == NULL)
		{
		    perror("Memory allocation failed");
		    fclose(fptr);
		    return failure;
		}
		strcpy(new->word, string); // Copy the word to the main node
		new->m_link = NULL;
		new->s_link = NULL;
		new->filecount = 1;// Set file count to 1 as it's the first occurrence


		// Create a new sub node and initialize it
		sub_node *sub = malloc(sizeof(sub_node));
		if (sub == NULL)
		{
		    perror("Memory allocation failed");
		    free(new);
		    fclose(fptr);
		    return failure;
		}
		strcpy(sub->file, temp->data);
		sub->wordcount = 1;
		sub->link = NULL;

		index[res - 'a'] = new;// Update the main array with the new node
		new->s_link = sub;// Link the main node to the sub node
	    }
	    else
	    {
		Main_node *mtemp = index[res - 'a'];
		sub_node *sprev = NULL;

		 // Traverse through the main nodes to find the matching word
		while (mtemp != NULL)
		{
		    if (strcmp(mtemp->word, string) == 0) // If the word matches
		    {
			sub_node *stemp = mtemp->s_link;

			while (stemp != NULL)
			{
			    // Traverse through the sub nodes to find the matching filename
			    if (strcmp(stemp->file, temp->data) == 0)
			    {
				stemp->wordcount++;// Increment word count
				break;
			    }
			    sprev = stemp;
			    stemp = stemp->link;
			}

			if (stemp == NULL)// If the filename doesn't exist in sub nodes
			{
			     // Create a new sub node and initialize it
			    sub_node *sub2 = malloc(sizeof(sub_node));
			    if (sub2 == NULL)
			    {
				perror("Memory allocation failed");
				fclose(fptr);
				return failure;
			    }
			    strcpy(sub2->file, temp->data);
			    sub2->wordcount = 1;
			    mtemp->filecount++;
			    sub2->link = NULL;

			    sprev->link = sub2;
			}
			break;
		    }
		    mtemp = mtemp->m_link;// Move to the next main node
		}

		if (mtemp == NULL)// If the word doesn't exist in main nodes
		{
		    Main_node *new_main = malloc(sizeof(Main_node));
		    if (new_main == NULL)
		    {
			perror("Memory allocation failed");
			fclose(fptr);
			return failure;
		    }
		    strcpy(new_main->word, string);
		    new_main->m_link = NULL;
		    new_main->s_link = NULL;
		    new_main->filecount = 1;

		    sub_node *new_sub = malloc(sizeof(sub_node));
		    if (new_sub == NULL)
		    {
			perror("Memory allocation failed");
			free(new_main);
			fclose(fptr);
			return failure;
		    }
		    strcpy(new_sub->file, temp->data);
		    new_sub->wordcount = 1;
		    new_sub->link = NULL;

		    new_main->s_link = new_sub;

		    Main_node *temp_main = index[res - 'a'];
		    while (temp_main->m_link != NULL)
		    {
			temp_main = temp_main->m_link;
		    }
		    temp_main->m_link = new_main;
		}
	    }
	}
	fclose(fptr);// Close the file
	temp = temp->link;// Move to the next filename in the linked list
    }
    return success;
}

