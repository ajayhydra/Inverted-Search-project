#ifndef SEARCH_H
#define SEARCH_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include<ctype.h>


//structure for the linked list 
typedef struct fname
{
    char data[1000];
    struct fname *link;

}flist;


#define success 1
#define failure 0
#define list_empty 2
#define empty 4;
//#define duplicate 5;
#define max_buf 1000


//structure fo sub node
typedef struct snode
{
    int wordcount;
    char file[max_buf];
    struct snode *link;
}sub_node;


//structure to store the main node details
typedef struct mnode
{
    int filecount;
    char word[max_buf];
    struct snode *s_link;
    struct mnode *m_link;
}Main_node;


//functions for inverted search 


//check and validate command line arguments

int check_validate_cmd(char *argv[],int argc,flist **head);

//print the linked list of file name in command line
void print_list(flist *head);


//function to create the database
int create_database(flist **head,Main_node **index);

//int check_index(char *str);

//function to display the databse
void display(Main_node **arr);


//function to search a word in the database
int search_database(Main_node **index , char *str,int size);

//function to save the database in to a text file
int save_database(Main_node **index);

//function to update the database with a backup file 
int update_database(Main_node **st,flist **head);

#endif


