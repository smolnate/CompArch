#include <stdio.h>
#include <stdlib.h>

//Binary Search Tree

struct treenode {
	int data;
	struct treenode *left;
	struct treenode *right;
};

struct treenode* insert(struct treenode*, int, int);
struct treenode* search(struct treenode*, int, int);
void free_tree(struct treenode*);

void free_tree(struct treenode *root){
	//in order traversal and free every node
	if(root== NULL){
		return;
	}
	free_tree(root->left);
	free_tree(root->right);
	free(root);
	root = NULL;	
}

struct treenode* insert(struct treenode *root, int num, int height){
	if(root==NULL){ //create new node
		struct treenode *temp = malloc(sizeof(struct treenode));
		temp->data = num;
		temp->left = NULL;
		temp->right = NULL;
		printf("inserted %d\n", height);
		return temp;
	}
	if(root->data == num){
		printf("duplicate\n");
	}
	else if(num < root->data){	
		root->left = insert(root->left, num, height+1);
	}
	else if(num > root->data){ //call insert on right child
		root->right = insert(root->right, num, height+1);
	}
	return root;
}

struct treenode* search(struct treenode *root, int num, int height){
	if(root==NULL){
		printf("absent\n");
	}
	else if(root->data == num){
		printf("present %d\n", height);
	}
	else if(num > root->data){ //num is bigger, search right child
		return search(root->right, num, height+1);
	}
	else if(num < root->data){ //search left child
		return search(root->left, num, height+1);
	}
	return root;
}
		

struct treenode *root = NULL;

int main(int argc, char **argv){
	FILE *fp = fopen(argv[1], "r");
	if(fp==NULL){
		printf("error");
		exit(0);
	}
	char mode;
	int num;
	int height=1;
	
	while(fscanf(fp, "%c\t%d\n", &mode, &num) == 2){
		if(mode == 'i')
		root = insert(root, num, height);
		else if(mode == 's')
			search(root, num, height);	
	}

	free_tree(root);	
	return 0;
}
