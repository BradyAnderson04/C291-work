//This program is supposed to scan 5 ints from the user
//Using those 5 ints, it should construct a linked list of 5 elements
//Then it prints the elements of the list using the PrintList function


/*
Changes made:
1.Syntax errors
2.Implemented arrow syntzax to dereference Node struct pointers
3.changed j to an i
4.added function prototype definition
5.added some include statements
6.Made everything memory allocation statement malloc
7.Changed all the scanf statements to right type specifier
8.Added a printf statement to be more clear
9.Changed print logic to actually print values now
10.Iterate through node by node
*/
#include <stdio.h>
#include <stdlib.h>

struct Node{
	int data;
	struct Node* next;
};

void PrintList(struct Node* n);

int main(void){
	struct Node* first = {0, 0};
	struct Node* second = {0, 0};
	struct Node* third = {0, 0};
	struct Node* fourth = {0, 0};
	struct Node* fifth = {0, first};


	
	first = (struct Node*)malloc(sizeof(struct Node));
	second = (struct Node*)malloc(sizeof(struct Node));
	third = (struct Node*)malloc(sizeof(struct Node));
	fourth = (struct Node*)malloc(sizeof(double));
	fifth = (struct Node*)malloc(sizeof(int));

	int i;
	printf("Enter some integer value for data to be stored and press ENTER:\n");
	scanf(" %d", &i);
	first->data = i;

	printf("Enter some integer value for data to be stored and press ENTER:\n");
	scanf(" %d", &i);
	second->data = i;
	first->next = second;

	printf("Enter some integer value for data to be stored and press ENTER:\n");
	scanf(" %d", &i);
	third->data = i;
	second->next = third;

	printf("Enter some integer value for data to be stored and press ENTER:\n");
	scanf(" %d", &i);
	fourth->data = i;
	third->next = fourth;

	printf("Enter some integer value for data to be stored and press ENTER:\n");
	scanf(" %d", &i);
	fifth->data = i;
	fourth->next = fifth;
	fifth->next = NULL;

	PrintList(first);
}

void PrintList(struct Node* n){
	while(n != NULL){
		printf("%d", n->data);
		n = n->next;
	}

	printf("\n");
}