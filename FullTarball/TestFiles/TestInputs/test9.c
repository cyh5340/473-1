#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "memalloc.h"
#include <stdbool.h>
//***********************************************************************************


// Struct for testing a linked list
struct node{
int key;
int value;
char name[10];
struct node* next;
}*head;
int RAM_SIZE=1024*1024;
/*
void set_up()
{
	chunk=NULL;
	//chunk->f=0;
	//chunk->next
	freed_chunks=0;
	chunk_number=0;
	int i;
	for(i=1;i<2048;i++)
		freelist[i] = 0;
	freelist[0] = ((void*)(&buddy));
}
*/
void test_linked_list(void);
void test_int_pointers(void);

FILE * pFile;

int main(int argc, char ** argv){
	 // FILE * pFile;
	 pFile = fopen ("test9_output.txt","w");
    	int size;
    	RAM_SIZE=1<<20;//1024*1024
    	void* RAM=malloc(RAM_SIZE);//1024*1024
	

	//int type = 0; 
	//strcpy(type, argv[1]);	
	setup(FIRST_FIT,RAM_SIZE,RAM);//First Fit, Memory size=1024*1024, Start of memory=RAM


	char *str1 = "Hello World\0";
	char *str2;//, *str3;

	// Replace with your function for malloc call
	str2 = (char *) my_malloc(strlen(str1)+1);
	strcpy(str2,str1);
	fprintf(pFile, "%s \n\n", str2);

	my_free(str2);


	test_linked_list();


    test_int_pointers();

	return 0;
}

// Function to test integer pointer allocation
void test_int_pointers(void){

	int *ptr;
	ptr = (int *) my_malloc(sizeof(int));
	*ptr = 999;
	fprintf(pFile, "\n*ptr is: %d\n\n",*ptr);
	my_free(ptr);

}

// Function to test linked list
void test_linked_list(void){

	// Replace with your function for malloc
	head = (struct node*) my_malloc(sizeof (struct node));
	head->next = NULL;
	head->key = 100;

	// Replace with your function for malloc
	head->next = (struct node*) my_malloc(sizeof (struct node));
	head->next->key = 200;
	head->next->next = NULL;

    	fprintf(pFile, "Head->key is: %d \n", head->key);
	fprintf(pFile, "Head->next->key is: %d \n", head->next->key);

	fprintf(pFile, "\nSize of my struct: %d\n\n", sizeof(struct node));

	struct node *temp;
	temp = head->next;
	head->next = NULL;

	// Relplace with your function for free
	my_free(temp);
	my_free(head);


}
