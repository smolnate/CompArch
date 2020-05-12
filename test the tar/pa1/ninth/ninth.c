#include <stdio.h>
#include <stdlib.h>

//Binary Search Tree with Deletion
//delete:27
//insert:121
//search:142
struct treenode {
	int data;
	struct treenode *left;
	struct treenode *right;
};

struct treenode* insert(struct treenode*, int, int);
struct treenode* search(struct treenode*, int, int);
struct treenode* delete(struct treenode*, int);
void free_tree(struct treenode*);
void swap(struct treenode*, struct treenode*);

void swap(struct treenode *p1, struct treenode *p2){
	int temp;
	temp = p1->data;
	p1->data = p2->data;
	p2->data = temp;
}

struct treenode* delete(struct treenode *root, int num){
	if(root == NULL){
		printf("fail\n");
		return root;
	}
	if(root->data == num){ //delete this node!
		//case 1: no children. just free the root node and return null
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
			printf("success\n");
			return NULL;
		}
		//case 2: one child. swap root and its child
		else if((root->left != NULL && root->right == NULL) || (root->left == NULL && root->right != NULL)) {
			if(root->left != NULL){
				swap(root, root->left);
				struct treenode *temp = root->left;
				root->right = root->left->right;
				root->left = root->left->left;
				free(temp);
				temp = NULL;
				printf("success\n");	
			}
			else{
				swap(root, root->right);
				struct treenode *temp = root->right;
				root->left = root->right->left;
				root->right = root->right->right;
				free(temp);
				temp = NULL;
				printf("success\n");
			}
			return root;
		}
		//case 3: two children. Get min from right subtree.
		else if(root->left != NULL && root->right != NULL){
			//use prev and temp as pointers to traverse and hold positions
			struct treenode *prev = NULL;
			struct treenode *temp = root->right;
			//move ptrs to the right position to find min in right subtree
			while(temp->left != NULL){
				prev=temp;
				temp=temp->left;
			}
			
			//swap root and temp data
			swap(root, temp);
			
			//case1: temp does not have a right child
			if(temp->right == NULL){
				free(temp);
				temp=NULL;
				if(prev==NULL)
					root->right = NULL;
			}
			//case2: temp has right child: two other cases		
			else{
				//subcase 1: prev is still NULL
				if(prev==NULL){
					root->right = root->right->right;
					free(temp);
					temp=NULL;
				}
				//subcase 2: prev is not NULL
				else{
					prev->left = temp->right;
					free(temp);
					temp=NULL;
				}
			}
			printf("success\n");
			return root;
		}
	}
	else if(num < root->data){
		root->left = delete(root->left, num);	
	}
	else{
		root->right = delete(root->right, num);
	}
	return root;
}
void free_tree(struct treenode *root){
	//in order traversal and free every node
	if(root==NULL){
		return;
	}
	free_tree(root->left);
	free_tree(root->right);
	free(root);
	root=NULL;
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
		else if(mode == 'd')
			root = delete(root, num);
	}


	return 0;
}
