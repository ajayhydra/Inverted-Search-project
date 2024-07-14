/*
NAME:
DATE:
DESCRIPTION:
SAMPLE I/P:
SAMPLE O/P:
*/
#include"search.h"

void display(Main_node **arr)
{
    printf("------------------------------------------------------------\n");
    printf("| INDEX |   Word     | FileCount |    FileName    | WordCount |\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < 27; i++)
    {
        Main_node *temp = arr[i];
        while (temp != NULL)
        {
            printf("|   [%c] | %-10s | %-9d |", i + 'a', temp->word, temp->filecount);

            // Printing file name and word count
            sub_node *temp1 = temp->s_link;
            if (temp1 != NULL)
            {
                printf(" %-14s | %-9d |\n", temp1->file, temp1->wordcount);
                temp1 = temp1->link;
            }
            else
            {
                printf(" %-14s | %-9s |\n", "-", "-");
            }

            // Printing additional subnodes
            while (temp1 != NULL)
            {
                printf("|       |            |           | %-14s | %-9d |\n", temp1->file, temp1->wordcount);
                temp1 = temp1->link;
            }

            // Move to the next main node
            temp = temp->m_link;
        }
    }
    printf("------------------------------------------------------------\n");
}


