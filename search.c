/*
NAME:
DATE:
DESCRIPTION:
SAMPLE I/P:
SAMPLE O/P:
*/

#include"search.h" // Include the header file for function prototypes and data structures

// Function to find the numeric index for a given string
int find_num(char *str)
{
    int index = 0;
    if(str[0] >= 65 && str[0] <= 90) // Check if first character is uppercase
    {
        str[0] = str[0] + 32; // Convert uppercase to lowercase
    }
    if((str[0] >= 33 && str[0] <= 47) || (str[0] >= 58 && str[0] <= 63)) // Check if first character is special character
    {
        index = 26; 
        return index;
    }
    index = str[0]; // Set index to ASCII value of first character
    return index;
}

// Function to search the database for a given word
int search_database(Main_node **index , char *str, int size)
{
    int res = find_num(str); 

    Main_node *mtemp = index[res - 'a']; 

    sub_node *stemp = NULL; 

    while(mtemp != NULL) // Traverse through the main nodes
    {
       
       	if(strcmp(mtemp->word,str) == 0) // If the word matches
       	{
          
	    printf("%s word present in %d files.\n",mtemp->word,mtemp->filecount); // Print the word and the number of files it's present in

            stemp = mtemp->s_link; 

            while(stemp != NULL) // Traverse through the sub nodes
            {
            
	    	printf("Wordcount: %d, Present in file: %s\n",stemp->wordcount,stemp->file); // Print word count and filename
                stemp = stemp->link; 
            
	    }
        }
        
	mtemp = mtemp->m_link; // Move to the next main node
    }

    return success; // Return success after searching the database
}

