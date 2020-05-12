#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

void insert(int num);
int hash(int key, int buckets);
void search(int num);

struct node *table[1000];

int main(int argc, char** argv){
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error");
		exit(0);
	}
	char mode;
	int num;
	while(fscanf(fp, "%c\t%d\n", &mode, &num)==2){
		if(mode == 'i'){
			insert(num);
		}
		else if(mode == 's'){
			search(num);
		}
	}
	
	
	return 0;
}

int hash(int key, int buckets){
	return (key % buckets);
}

void insert(int num){
	struct node *temp = malloc(sizeof(struct node));
	temp->data = num;	
	//check if node exists
	int index = hash(num, 1000);
	if(index < 0){
		index = index * (-1);
	}
	//check if first item to LL
	struct node *ptr = table[index];
	if(ptr == NULL){
		table[index] = temp;
		printf("inserted\n");
		return;
	}
	for(ptr = table[index]; ptr != NULL; ptr = ptr->next){
		if(ptr->data == num){
			printf("duplicate\n");
			return;
		}
	}
	//went through without finding num, add to front
	temp->next = table[index];
	table[index] = temp;
	printf("inserted\n");
	return;
}

void search(int num){
	struct node *ptr;
	int index = hash(num, 1000);
	if(index < 0){
		index = index * (-1);
	}
	ptr = table[index];
	for(ptr = table[index]; ptr != NULL; ptr = ptr->next){
		if(ptr->data == num){
			printf("present\n");
			return;
		}
	}
	printf("absent\n");
	return;
}




