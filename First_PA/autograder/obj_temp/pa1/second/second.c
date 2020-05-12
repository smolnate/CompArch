#include <stdio.h>
#include <stdlib.h>


//create structure for linked list: integers
struct node {
	int number;
	struct node *next;
};

//head node of LL
struct node *head= NULL;

//LL function prototypes
void print_list();
void free_list();
void insert(int x);
void delete(int y);
int getSize(struct node *head);

int main(int argc, char** argv){
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error");
		exit(0);
	}
	
	char mode;
	int num = 0;
	while(fscanf(fp, "%c\t%d\n", &mode, &num) == 2){
		if(mode == 'i'){
			insert(num);
		}
		else if(mode == 'd'){
			delete(num);
		}
	}
	printf("%d\n", getSize(head));
	print_list();
	free_list(); 
	return 0;
}

void print_list(){
	struct node *ptr = head;
	while(ptr != NULL){
		printf("%d\t", ptr->number);
		ptr = ptr->next;
	}
}

void free_list(){
	struct node *temp = head;
	while(temp != NULL){
		struct node *temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
}

void insert(int x){
	struct node *prev = NULL;
	struct node *temp = malloc(sizeof(struct node));
	temp->number = x;
	//first number to be added
	if(head == NULL){
		head = temp;	
		return;
	}
	struct node *ptr = head;
	while(ptr != NULL){
		//check if adding a duplicate
		if(x == ptr->number){
			return;
		}
		//case1: add to front
		if(x < ptr->number && prev == NULL){
			temp->next = ptr;
			head = temp;
			return;	
		}
		//case 2: add in middle
		else if(x < ptr->number && prev != NULL){
			temp->next = ptr;
			prev->next = temp;
			return;
		}
		//case 3: add to the end
		else if(x > ptr->number && ptr->next == NULL){
			ptr->next = temp;
			ptr = temp;
			return;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

void delete(int y){
	struct node *prev = NULL;
	struct node *ptr = head;
	//empty list passed
	if(ptr == NULL){
		return;
	}
	//traverse thru LL to find number
		//case 1: delete head
	if(ptr->number == y && prev == NULL){
		head = head->next;
		free(ptr);
		return;
	}
	while(ptr != NULL && ptr->number != y){
		prev = ptr;
		ptr = ptr->next;
	}
	if(ptr == NULL){ //not found
		return;
	}
	prev->next = ptr->next;
	free(ptr);
	return;
}

int getSize(struct node *h){
	int size = 0;
	struct node *ptr = head;
	while(ptr != NULL){
		size++;
		ptr = ptr->next;
	}
	return size;
}

