/*
NAME:
DATE:
DESCRIPTION:
SAMPLE I/P:
SAMPLE O/P:
*/
#include"search.h"


// Function to update the database based on the contents of a file
int update_database(Main_node **st,flist **head)
{
    flist *uhead=NULL;// Initialize a temporary linked list for file names

    //assign each index to null
    for(int i=0;i<=26;i++)
    {
        st[i]=NULL;
    }
    char word[100],newfile[25];
    int index;
    FILE *fptr;
    printf("Enter the file\n");
    scanf("%s",newfile);

    fptr=fopen(newfile,"r");// Open the file for reading

    //check the file exisisting or not
    if(fptr==NULL)
    {
        printf("FILE NOT EXISISTING\n");
       
     	return failure;
    }

    //read the content of the file
    while(fscanf(fptr,"%s",word)!=EOF)
    {
        if(word[0]!='#') // Check if the file is empty
        {
            printf("File is empty\n");
            return failure;
        }

        index=atoi(strtok(&word[1],";"));  //store index
        Main_node *new=malloc(sizeof(Main_node));   //create mainnode
        
	if(new==NULL)
        {
            return failure;
        }

        new->m_link=NULL;
        new->s_link=NULL;
        strcpy(new->word,strtok(NULL,";"));// Copy the word to the main node
        new->filecount=atoi(strtok(NULL,";"));// Store file count
        
	sub_node *new1=malloc(sizeof(sub_node));
        new->s_link=new1;
        new1->link=NULL;
        strcpy(new1->file,strtok(NULL,";"));
       
       	flist *node=malloc(sizeof(flist));
        strcpy(node->data,new1->file); // Copy the filename to the sub node
        node->link=NULL;
        uhead=node;
        new1->wordcount=atoi(strtok(NULL,";"));// Store word count
        sub_node *prev=new1;
        
	//store the subnode data
        for(int i=0;i<(new->filecount)-1;i++)
        {
            sub_node *new2=malloc(sizeof(sub_node));
            if(new2==NULL)
            {
                return failure;
            }
            strcpy(new2->file,strtok(NULL,";"));
            flist *utemp=uhead;
            
	    //create a new list to store the file names
            while(utemp!=NULL)
            {
                if(strcmp(new2->file,utemp->data)==0) // Copy the filename to the sub node
                {
                    break;
                }
                utemp=utemp->link;
            }
            
	    if(utemp==NULL)
            {
                flist *node1=malloc(sizeof(flist));
                strcpy(node1->data,new2->file);
                node1->link=uhead;
                uhead=node1;
            }
            new2->wordcount=atoi(strtok(NULL,";"));// Store word count
            prev->link=new2;
            new2->link=NULL;
            prev=new1;
        }
        
	//store the node to the index
        if(st[index]==NULL)
        {
            st[index]=new;
        }
        else
        {
            Main_node *temp=st[index];
            while(temp->m_link!=NULL)
            {
                temp=temp->m_link;
            }
            temp->m_link=new;
        }
    }
    
    fclose(fptr);// Close the file
    
    flist *t=uhead;
    flist *t1=*head;
    flist *prev=*head;
  
    //remove duplicates from head
    while(t1!=NULL)
    {
        while(t!=NULL)
        {
            if(strcmp(t1->data,t->data)==0)
            {
                break;
            }
            t=t->link;
        }
        if(t!=NULL)
        {
            if(*head==t1)
            {
                *head=t1->link;
                prev=*head;
                free(t1);
                t1=prev;
            }
            else
            {
                prev->link=t1->link;
                free(t1);
                t1=prev;
            }
        }
        t=uhead;
        prev=t1;
        if(t1!=NULL)
        {
            t1=t1->link;
        }
    }
    return success;
}

