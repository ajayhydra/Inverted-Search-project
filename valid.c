/*
NAME:
DATE:
DESCRIPTION:
SAMPLE I/P:
SAMPLE O/P:
 */
#include"search.h"

int insert_at_last(flist **head, char *data)
{
    flist *new_node = malloc(sizeof(flist));
    if (new_node == NULL)
    {
	return failure;
    }

    strcpy(new_node->data, data);
    new_node->link = NULL;

    if (*head == NULL)
    {
	*head = new_node;
	printf("%s file added to the list .\n",new_node->data);

    } 
    else
    {
	flist *temp = *head;
	while (temp->link != NULL) {
	    temp = temp->link;
	}
	temp->link = new_node;
	printf("%s file added to the list .\n",new_node->data);
    }
    return success;
}

int check_validate_cmd(char *argv[], int argc, flist **head) 
{
    int i = 0;
    for (i = 1; i < argc; i++)
    {
	if (strstr(argv[i], ".txt") != NULL)
	{
	    FILE *fptr = fopen(argv[i], "r");
	    if (fptr == NULL)
	    {
		return failure;
	    }
	    fseek(fptr, 0, SEEK_END);
	    int size = ftell(fptr);
	    fclose(fptr);

	    if (size == 0)
	    {
		printf("%s file is empty\n", argv[i]);
		return failure;
	    }
	    else 
	    {
		char *filename = malloc(strlen(argv[i]) + 1);
		if (filename == NULL) 
		{
		    printf("Memory allocation failed for %s\n", argv[i]);
		    return failure;
		}
		strcpy(filename, argv[i]);

		flist *temp = *head;
		int duplicate = 0;
		while (temp != NULL)
		{
		    if (strcmp(temp->data, filename) == 0)
		    {
			printf("%s file duplicate appears in the command line.\n", argv[i]);
			duplicate = 1;
			break;
		    }
		    temp = temp->link;
		}

		if (!duplicate)
		{
		    if (insert_at_last(head,filename) == failure)
		    {
			printf("Insertion failed for %s\n", argv[i]);
			free(filename);
			return failure;
		    }
		} 
		else
		{
		    free(filename);
		}
	    }
	}
	else
	{
	    printf("%s file is not a text file.\n", argv[i]);
	}
    }
    return success;
}


void print_list(flist *head)
{
    //checking list is empty or not.
    if (head == NULL)
    {
	printf("INFO : List is empty\n");
    }
    else
    {
	while (head)		
	{
	    printf("%s -> ", head -> data); //printing data of head
	    head = head -> link; //update head link to next node
	}

	printf("NULL\n");
    }
}

