#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node{
	unsigned int value;
	int assigned;
	char *name;
	struct node *next;
};
struct line{
	char *string;
	int finished;
	struct line *next;
};

struct listnode{ //to be used for decoder and multiplexer
	int value; //0 or 1
	char *name;
	struct listnode *next;
};

char* getname(struct listnode*, int);
int bintoint(char*, int);
void updateval(struct node*, char*, int);
char xorc(char, char);
char flip(char);
void finish(struct line*, char*);
int linefinished(struct line*, char*);
int finished(struct line*);
void unassign(struct node*);
unsigned int gray(int);
void free_linelist(struct line*);
void free_nodelist(struct node*);
void free_listnodelist(struct listnode*);
struct line* insertline(struct line*, char*);
struct node* insertLL(struct node*, char*);
struct listnode* insertlistnode(struct listnode*, char*, int);
void printlist(struct node*);
int power(int, int);
void int_to_bin(unsigned int, int, int*);
void assign(struct node*, int*, int);
int outassigned(struct node*);
int assigned(struct node*, char*);
int search(struct node*, char*);
void print_row(int*, struct node*, int);
void NOT(struct node*, char*, struct node*, char*);
void AND(struct node*, char*, struct node*, char*, struct node*, char*);
void OR(struct node*, char*, struct node*, char*, struct node*, char*);
void NAND(struct node*, char*, struct node*, char*, struct node*, char*);
void XOR(struct node*, char*, struct node*, char*, struct node*, char*);
void NOR(struct node*, char*, struct node*, char*, struct node*, char*);
void XNOR(struct node*, char*, struct node*, char*, struct node*, char*);
void resetval(struct node*);
void unfinish(struct line*);
int searchline(struct line*, char*);
int getval(struct node*, char*);
char* graytobinary(char*, char*, int);
int getmultival(struct listnode*, int);

void free_listnodelist(struct listnode *head){
	struct listnode *ptr = head;
	while(head!=NULL){
		ptr = head;
		head = head->next;
		free(ptr);
	}
}

int bintoint(char* binary, int length){
	int value = 0;
	int base = 1;
	int i;
	for(i=length-1; i>=0; i--){
		if(binary[i] == '1')
			value += base;
		base = base*2;
	}
	return value;
}

char* graytobinary(char *gray, char *binary, int length){
	binary[0] = gray[0];
	int i=1;
	for(i=1; i<length; i++){
		if(gray[i] == '0')
			binary[i] = binary[i-1];
		else
			binary[i] = flip(binary[i-1]);	
	}
	return binary;
}

char xorc(char a, char b){ return (a==b) ? '0':'1';}
char flip(char a){return (a == '0') ? '1':'0';}

void finish(struct line *head, char *string){
	struct line *ptr = head;
	while(ptr != NULL){
		if(strcmp(ptr->string, string)==0){
			ptr->finished = 1;
			return;
		}
		ptr = ptr->next;
	}
}

int finished(struct line *head){
	struct line *ptr = head;
	while(ptr != NULL){
		if(ptr->finished == 0) 
			return 0;
		ptr = ptr->next;
	}
	return 1;
}

int linefinished(struct line *head, char *string){
	struct line *ptr = head;
	while(ptr != NULL){
		if(strcmp(ptr->string, string)==0){
			if(ptr->finished == 1)
				return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}

int searchline(struct line *head, char *string){
	struct line *ptr = head;
	while(ptr != NULL){
		if(strcmp(ptr->string, string)==0) //found
			return 1;
		ptr = ptr->next;
	}
	return 0;
}

void unfinish(struct line *head){
	struct line *ptr = head;
	while(ptr != NULL){
		ptr->finished = 0;
		ptr = ptr->next;
	}
}

void resetval(struct node *head){
	struct node *ptr = head;
	while(ptr != NULL){
		ptr->value = 0;
		ptr->assigned = 0;
		ptr = ptr->next;
	}
}

void XNOR(struct node *h1, char *v1, struct node *h2, char *v2, struct node *h3, char *v3){
	//locate v1
	struct node *p1 = h1;
	struct node *p2 = h2;
	struct node *p3 = h3;
	while(p1 != NULL){
		if(strcmp(p1->name, v1) == 0){
			//locate v2
			while(p2 != NULL){
				if(strcmp(p2->name, v2) == 0){
					//locate v3
					while(p3 != NULL){
						if(strcmp(p3->name, v3) == 0){
							if(p1->value == p2->value)
								p3->value = 1; 
							else
								p3->value = 0;
							p3->assigned = 1;
							return;
						}
						p3 = p3->next;
					}
				}
				p2 = p2->next;
			}
		}
		p1 = p1->next;
	}
}

void XOR(struct node *h1, char *v1, struct node *h2, char *v2, struct node *h3, char *v3){
	//locate v1
	struct node *p1 = h1;
	struct node *p2 = h2;
	struct node *p3 = h3;
	while(p1 != NULL){
		if(strcmp(p1->name, v1) == 0){
			//locate v2
			while(p2 != NULL){
				if(strcmp(p2->name, v2) == 0){
					//locate v3
					while(p3 != NULL){
						if(strcmp(p3->name, v3) == 0){
							if(p1->value != p2->value)
								p3->value = 1;
							else
								p3->value = 0;
							p3->assigned = 1;
							return;
						}
						p3 = p3->next;
					}
				}
				p2 = p2->next;
			}
		}
		p1 = p1->next;
	}
}

void NOR(struct node *h1, char *v1, struct node *h2, char *v2, struct node *h3, char *v3){
	//locate v1
	struct node *p1 = h1;
	struct node *p2 = h2;
	struct node *p3 = h3;
	while(p1 != NULL){
		if(strcmp(p1->name, v1) == 0){
			//locate v2
			while(p2 != NULL){
				if(strcmp(p2->name, v2) == 0){
					//locate v3
					while(p3 != NULL){
						if(strcmp(p3->name, v3) == 0){
							if(p1->value == 0 && p2->value == 0)
								p3->value = 1;
							else
								p3->value = 0;
							p3->assigned = 1;
							return;
						}
						p3 = p3->next;
					}
				}
				p2 = p2->next;
			}
		}
		p1 = p1->next;
	}
}

void NAND(struct node *h1, char *v1, struct node *h2, char *v2, struct node *h3, char *v3){
	//locate v1
	struct node *p1 = h1;
	struct node *p2 = h2;
	struct node *p3 = h3;
	while(p1 != NULL){
		if(strcmp(p1->name, v1) == 0){
			//locate v2
			while(p2 != NULL){
				if(strcmp(p2->name, v2) == 0){
					//locate v3
					while(p3 != NULL){
						if(strcmp(p3->name, v3) == 0){
							if(p1->value == 1 && p2->value == 1)
								p3->value = 0;
							else
								p3->value = 1;
							p3->assigned = 1;
							return;
						}
						p3 = p3->next;
					}
				}
				p2 = p2->next;
			}
		}
		p1 = p1->next;
	}
}

void OR(struct node *h1, char *v1, struct node *h2, char *v2, struct node *h3, char *v3){
	//locate v1
	struct node *p1 = h1;
	struct node *p2 = h2;
	struct node *p3 = h3;
	while(p1 != NULL){
		if(strcmp(p1->name, v1) == 0){
			//locate v2
			while(p2 != NULL){
				if(strcmp(p2->name, v2) == 0){
					//locate v3
					while(p3 != NULL){
						if(strcmp(p3->name, v3) == 0){
							if(p1->value == 0 && p2->value == 0)
								p3->value = 0;
							else
								p3->value = 1;
							p3->assigned = 1;
							return;
						}
						p3 = p3->next;
					}
				}
				p2 = p2->next;
			}
		}
		p1 = p1->next;
	}
}	
	
void unassign(struct node *head){
	struct node *ptr = head;
	while(ptr != NULL){
		ptr->assigned = 0;
		ptr = ptr->next;
	}
}

void print_row(int *arr, struct node *head, int numInputs){
	int i=0;
	for(i=0; i<numInputs; i++){
		printf("%d ", arr[i]);
	}
	struct node *ptr = head;
	while(ptr != NULL){
		if(ptr->next == NULL) 
			printf("%d", ptr->value);
		else{
			printf("%d ", ptr->value);
		}
		ptr = ptr->next;
	}
}

void AND(struct node *h1, char *v1, struct node *h2, char *v2, struct node *h3, char *v3){
	//locate v1
	struct node *p1 = h1;
	struct node *p2 = h2;
	struct node *p3 = h3;
	while(p1 != NULL){
		if(strcmp(p1->name, v1) == 0){
			//locate v2
			while(p2 != NULL){
				if(strcmp(p2->name, v2) == 0){
					//locate v3
					while(p3 != NULL){
						if(strcmp(p3->name, v3) == 0){
							if(p1->value == 1 && p2->value == 1)
								p3->value = 1;
							else
								p3->value = 0;
							p3->assigned = 1;
							return;
						}
						p3 = p3->next;
					}
				}
				p2 = p2->next;
			}
		}
		p1 = p1->next;
	}
}	
					

void NOT(struct node *head, char *var1, struct node *head2, char *var2){
	struct node *ptr = head;
	struct node *ptr2 = head2;
	while(ptr != NULL){
		if(strcmp(ptr->name, var1) == 0){ //found input
			while(ptr2 != NULL){
				if(strcmp(ptr2->name, var2) == 0){
					ptr2->assigned = 1;
					if(ptr->value == 1)
						ptr2->value = 0;
					else
						ptr2->value = 1;
				}
				ptr2=ptr2->next;
			}
		}
		ptr = ptr->next;
	}	
}

int search(struct node *head, char *name){
	struct node *ptr = head;
	while(ptr != NULL){
		if(strcmp(ptr->name, name) == 0)
			return 1; //found
		ptr = ptr->next;
	}
	return 0; //not found
}

int getmultival(struct listnode *head, int n){
	int i=0;
	struct listnode *ptr = head;
	while(ptr!=NULL){
		if(i==n) return ptr->value;
		i++;
		ptr=ptr->next;
	}
	return ptr->value;
}

char* getname(struct listnode *head, int n){
	int i=0;
	struct listnode *ptr = head;
	while(ptr != NULL){
		if(i==n) return ptr->name;
		i++;
		ptr = ptr->next;
	}
	return ptr->name;
}

void updateval(struct node *head, char *name, int value){
	struct node *ptr = head;
	while (ptr!=NULL){
		if(strcmp(ptr->name, name)==0){
			ptr->value = value;
			ptr->assigned = 1;
			return;
		}
		ptr=ptr->next;
	}
}

int getval(struct node *head, char *name){
	struct node *ptr = head;
	while(ptr != NULL){
		if(strcmp(ptr->name, name)==0)
			return ptr->value;
		ptr = ptr->next;
	}
	return -1; //invalid
}

int assigned(struct node *head, char *name){
	struct node *ptr = head;
	while (ptr!= NULL){
		if(strcmp(ptr->name, name)==0){
			if(ptr->assigned == 1) return 1;
			else return 0;
		}
		ptr = ptr->next;
	}
	return 0;
}

int outassigned(struct node *outhead){
	struct node *ptr = outhead;
	while(ptr != NULL){
		if(ptr->assigned == 0)
			return 0;
		ptr = ptr->next;
	}
	return 1;
}

void assign(struct node *head, int *arr, int count){
	int i=0;
	struct node *ptr = head;
	for(i=0; i<count; i++){
		ptr->value = arr[i];
		ptr->assigned = 1;
		ptr = ptr->next;
	}
}

void int_to_bin(unsigned int num, int count, int* arr){
	int mask = 1 << (count-1);
	int i;
	for(i=0; i<count; i++){
		arr[i] = (num & mask) ? 1 : 0;
		num <<= 1;
	}
}
int power(int base, int power){
	int res = 1;
	while(power > 0){
		res *= base;
		power--;
	}
	return res;
}

struct node* insertLL(struct node *head, char* name){
	struct node *add = malloc(sizeof(struct node));
	add->name = name;
	add->next = NULL;
	if(head == NULL){
		head = add;
	}
	else{
		struct node *ptr = head;
		while(ptr->next != NULL){
			ptr = ptr->next;
		}
		ptr->next = add;
	}
	return head;
}

struct listnode* insertlistnode(struct listnode *head, char *name, int value){
	struct listnode *add = malloc(sizeof(struct listnode));
	add->name = name;
	add->value = value;
	add->next = NULL;
	if(head==NULL){
		head = add;
	}
	else{
		struct listnode *ptr = head;
		while(ptr->next != NULL){
			ptr = ptr->next;
		}
		ptr->next = add;
	}
	return head;	
}

struct line* insertline(struct line *head, char* str){
	struct line *add = malloc(sizeof(struct line));
	add->string = str;
	add->finished = 0;
	add->next = NULL;
	if(head == NULL)
		head = add;
	else{
		struct line *ptr = head;
		while(ptr->next != NULL){
			ptr = ptr->next;
		}
		ptr->next = add;
	}
	return head;
}


void printlist(struct node *head){
	struct node *ptr = head;
	while(ptr != NULL){
		printf("%s ", ptr->name);
		ptr = ptr->next;
	}
}

unsigned int gray(int row){
	return row ^ (row >> 1);
}

//struct listnode *listhead = NULL;
struct node *inhead = NULL;
struct node *temphead = NULL;
struct node *outhead = NULL;
struct line *linehead = NULL;
/*****************************************/

int main(int argc, char** argv){
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error");
		exit(0);
	}
	//parse for inputvar and outputvar, then rewind file
	int numInputs=0;
	int numOutputs=0;
	int i=0;
	char *string = malloc(512);
	char *mode = malloc(15);
	//struct node *temphead = NULL;
	while(fgets(string, 512, fp) != NULL){
		char *str = malloc(512);
		strcpy(str, string);
		sscanf(string, "%s", mode);
		if(strcmp(mode, "INPUTVAR") == 0) {//found inputvar
			int offset=0;
			int n=0;
			sscanf(string, "INPUTVAR %d%n", &numInputs, &n);
			offset += n;
			for(i=0; i<numInputs; i++){
				char *name = malloc(25*sizeof(char));
				sscanf(string+offset, " %s%n", name, &n);
				offset += n;
				inhead = insertLL(inhead, name);
				//free(name);
			}
			linehead = insertline(linehead, str);	
		}
		else if(strcmp(mode, "OUTPUTVAR") == 0){//pfound output var
			int offset=0;
			int n=0;
			sscanf(string, "OUTPUTVAR %d%n", &numOutputs, &n);
			offset+=n;
			for(i=0; i<numOutputs; i++){
				char *name = malloc(25*sizeof(char));
				sscanf(string+offset, " %s%n", name, &n);
				offset += n;
				outhead = insertLL(outhead, name);
				//free(name);
			}
			linehead = insertline(linehead, str);
		}
		else{
			linehead = insertline(linehead, str);
		}
		//free(str);
	}
//	printlist(inhead);
//	printf("\n");
//	printlist(outhead);
	//NOW rewind. skip inputvar and outputvar.
	//row by row, generate the graycode sequence. assign to each input var.
	int row = 0;
	int n = power(2, numInputs);
	int *garr = malloc(sizeof(int)*numInputs);
	for(row = 0; row < n; row++){
		unassign(outhead);
		unfinish(linehead);
		resetval(temphead);
		unassign(temphead);
		fseek(fp, 0, SEEK_SET);
		unsigned int g = gray(row);
		int_to_bin(g, numInputs, garr);
		assign(inhead, garr, numInputs);
		//Now assigned. Loop through fp, doing all possible arithmetics. Check if assigned.
		while(outassigned(outhead) != 1 && finished(linehead) != 1){		
		fseek(fp, 0, SEEK_SET);
		while(fgets(string, 512, fp) != NULL){
			int offset = 0;
			int n = 0;
			char *var1 = malloc(25*sizeof(char));
			char *var2 = malloc(25*sizeof(char));
			char *var3 = malloc(25*sizeof(char));
			sscanf(string, "%s%n", mode, &n);
			offset += n;
			if(linefinished(linehead, string)==1) //this line was computed. skip.
				continue;
			else if(strcmp(mode, "INPUTVAR") == 0 || strcmp(mode, "OUTPUTVAR") == 0){
				finish(linehead, string);
				continue;
			}
			else if(strcmp(mode, "NOT") == 0){
					sscanf(string+offset, "%s %s", var1, var2);
					//fscanf(fp, "%s %s", var1, var2);
					if(search(inhead, var1) == 1){//it is one of the inputs
						if(search(outhead, var2) == 1){ //output variable!
							NOT(inhead, var1, outhead, var2);
							finish(linehead, string);
						}
						else if(search(temphead, var2) == 1){ //temp variable AND is assigned a value! we can compute.
							NOT(inhead, var1, temphead, var2);
							finish(linehead, string);
						}
						else{ //output to temp variable, but never seen before. insert to LL
							temphead = insertLL(temphead, var2);
							NOT(inhead, var1, temphead, var2);
							finish(linehead, string);	
						}
					}	
					else if(search(temphead, var1) == 1 && assigned(temphead, var1)==1){ //input is temp/assign.
						if(search(inhead, var2) == 1){ //output to input. we are good.
							NOT(temphead, var1, inhead, var2);
							finish(linehead, string);
						}
						else if(search(temphead, var2) == 1){ //output to temp variable
							NOT(temphead, var1, temphead, var2);
							finish(linehead, string);
						}
						else{ //output to new temp variable
							temphead = insertLL(temphead, var2);	
							NOT(temphead, var1, temphead, var2);
							finish(linehead, string);
						}
					}
					else if(strcmp(var1, "1") == 0){
						if(search(temphead, var2)==1){
							updateval(temphead, var2, 0);
						}
						else if(search(outhead, var2) == 1){
							updateval(outhead, var2, 0);
						}
						else {
							temphead = insertLL(temphead, var2);
							updateval(temphead, var2, 0);
							finish(linehead, string);
						}
					}
					else { //we do not know the input. cannot compute.
						continue;
					}
			}
			else if(strcmp(mode, "AND") == 0) {
				sscanf(string+offset, "%s %s %s", var1, var2, var3);
				//fscanf(fp, "%s %s %s", var1, var2, var3);
				//check if inputs exist. if one does not exist, skip.
				if((search(inhead,var1)==0&&search(temphead,var1)==0)||(search(inhead,var2)==0&&search(temphead,var2)==0)) 
					continue;
				//both inputs exist. check if any are temps, if they are, check if they were assigned
				if((search(temphead, var1)==1 && assigned(temphead,var1)==0) || (search(temphead, var2)==1 && assigned(temphead, var2)==0))
					continue;
				//both inputs assigned, compute to output 
				if(search(inhead, var1) == 1) {//var1 input variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1) {//nice. output variable is output.
							AND(inhead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							AND(inhead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							AND(inhead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							AND(inhead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}
				else if(search(temphead, var1) == 1) {//var1 TEMP variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1){ //nice. output variable is output.
							AND(temphead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							AND(temphead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							AND(temphead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							AND(temphead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}	
			}
			else if(strcmp(mode, "OR") == 0) {
				sscanf(string+offset, "%s %s %s", var1, var2, var3);
				//fscanf(fp, "%s %s %s", var1, var2, var3);
				//if both inputs NOT assigned skip line	
				if((search(inhead,var1)==0&&search(temphead,var1)==0)||(search(inhead,var2)==0&&search(temphead,var2)==0)) 
					continue;
				//both inputs exist. check if any are temps, if they are, check if they were assigned
				if((search(temphead, var1)==1 && assigned(temphead,var1)==0) || (search(temphead, var2)==1 && assigned(temphead, var2)==0))
					continue;	
				//both inputs assigned, compute to output 
				if(search(inhead, var1) == 1) {//var1 input variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1) {//nice. output variable is output.
							OR(inhead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							OR(inhead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							OR(inhead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							OR(inhead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}
				else if(search(temphead, var1) == 1) {//var1 TEMP variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1){ //nice. output variable is output.
							OR(temphead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							OR(temphead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							OR(temphead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							OR(temphead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}	
			}
			else if(strcmp(mode, "NAND") == 0) {
				sscanf(string+offset, "%s %s %s", var1, var2, var3);
				//fscanf(fp, "%s %s %s", var1, var2, var3);
				//if both inputs NOT assigned skip line
				if(((search(inhead,var1)==0&&search(temphead,var1)==0)||(search(inhead,var2)==0&&search(temphead,var2)==0)) || (!((assigned(inhead, var1)==1 && assigned(temphead, var2)==1)||(assigned(temphead, var1)==1 && assigned(temphead, var2) == 1))))		 
					continue;
				//both inputs assigned, compute to output 
				if(search(inhead, var1) == 1) {//var1 input variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1) {//nice. output variable is output.
							NAND(inhead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							NAND(inhead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							NAND(inhead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							NAND(inhead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}
				else if(search(temphead, var1) == 1) {//var1 TEMP variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1){ //nice. output variable is output.
							NAND(temphead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							NAND(temphead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							NAND(temphead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							NAND(temphead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}	
			}
			else if(strcmp(mode, "NOR") == 0) {
				sscanf(string+offset, "%s %s %s", var1, var2, var3);
				//fscanf(fp, "%s %s %s", var1, var2, var3);
				//if both inputs NOT assigned skip line
				if(((search(inhead,var1)==0&&search(temphead,var1)==0)||(search(inhead,var2)==0&&search(temphead,var2)==0)) || (!((assigned(inhead, var1)==1 && assigned(temphead, var2)==1)||(assigned(temphead, var1)==1 && assigned(temphead, var2) == 1)))) 
					continue;
				//both inputs assigned, compute to output 
				if(search(inhead, var1) == 1) {//var1 input variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1) {//nice. output variable is output.
							NOR(inhead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							NOR(inhead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							NOR(inhead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							NOR(inhead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}
				else if(search(temphead, var1) == 1) {//var1 TEMP variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1){ //nice. output variable is output.
							NOR(temphead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							NOR(temphead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							NOR(temphead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							NOR(temphead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}	
			}
			else if(strcmp(mode, "XOR") == 0) {
				sscanf(string+offset, "%s %s %s", var1, var2, var3);
				//fscanf(fp, "%s %s %s", var1, var2, var3);
				//if both inputs NOT assigned skip line
				if(((search(inhead,var1)==0&&search(temphead,var1)==0)||(search(inhead,var2)==0&&search(temphead,var2)==0)) || (!((assigned(inhead, var1)==1 && assigned(temphead, var2)==1)||(assigned(temphead, var1)==1 && assigned(temphead, var2) == 1)))) 
					continue;
					//both inputs assigned, compute to output 
				if(search(inhead, var1) == 1) {//var1 input variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1) {//nice. output variable is output.
							XOR(inhead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							XOR(inhead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							XOR(inhead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							XOR(inhead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}
				else if(search(temphead, var1) == 1) {//var1 TEMP variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1){ //nice. output variable is output.
							XOR(temphead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							XOR(temphead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							XOR(temphead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							AND(temphead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}	
			}
			else if(strcmp(mode, "XNOR") == 0) {
				sscanf(string+offset, "%s %s %s", var1, var2, var3);
				//fscanf(fp, "%s %s %s", var1, var2, var3);
				//if both inputs NOT assigned skip line
				if(((search(inhead,var1)==0&&search(temphead,var1)==0)||(search(inhead,var2)==0&&search(temphead,var2)==0)) || (!((assigned(inhead, var1)==1 && assigned(temphead, var2)==1)||(assigned(temphead, var1)==1 && assigned(temphead, var2) == 1)))) 
					continue;
				//both inputs assigned, compute to output 
				if(search(inhead, var1) == 1) {//var1 input variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1) {//nice. output variable is output.
							XNOR(inhead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							XNOR(inhead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							XNOR(inhead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							XNOR(inhead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}
				else if(search(temphead, var1) == 1) {//var1 TEMP variable. check for var2	
					if(search(inhead, var2) == 1) {//var2 is also input variable. nice.
						if(search(outhead, var3) == 1){ //nice. output variable is output.
							XNOR(temphead, var1, inhead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{ //is a temp var. need to see if we have to insert it to LL before altering
							if(search(temphead, var3) == 0) //need ot add to tempLL
								temphead = insertLL(temphead, var3);
							XNOR(temphead, var1, inhead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
					else{//var2 is a temp variable
						if(search(outhead, var3) == 1){
							XNOR(temphead, var1, temphead, var2, outhead, var3);
							finish(linehead, string);
						}
						else{
							if(search(temphead, var3) == 0)
								temphead = insertLL(temphead, var3);
							XNOR(temphead, var1, temphead, var2, temphead, var3);
							finish(linehead, string);
						}
					}
				}	
			}
			else if(strcmp(mode, "DECODER") == 0){
				struct listnode* listhead = NULL;
				int inputnum=0;
				int tempval=0;
				char *tempname = malloc(25*sizeof(char));
				char *inputname = malloc(25*sizeof(char));
				char *outputlistname = malloc(25*sizeof(char));
				sscanf(string+offset, "%d%n", &inputnum, &n);
				char *graycodebinary = malloc(inputnum*sizeof(char));
				char *binaryeq = malloc(inputnum*sizeof(char));
				offset += n;
				for(i=0; i<inputnum; i++){
					sscanf(string+offset, "%s%n", inputname, &n);
					offset += n;
					//grab value of this input from the search
					if(search(inhead, inputname) ==1) {//check input to see if assigned
						if(assigned(inhead, inputname) == 0) //not assigned. SKIP
							continue;
						else
							tempval = getval(inhead, inputname);
					}
					else { //check temp to see if assigned
						if(assigned(temphead, inputname) == 0) //not assigned. SKIP
							continue;
						else
							tempval = getval(temphead, inputname);
					}
					//convert this to a character and add it to graycodebinary
					graycodebinary[i] = tempval + '0';
				}
				//inputs have all been assigned and have been read and stored into graycodebinary.
				//start reading outputs
				for(i=0; i<pow(2, inputnum); i++){
					char *outname = malloc(25*sizeof(char));
					sscanf(string+offset, "%s%n", outputlistname, &n);
					strcpy(outname, outputlistname);
					offset+=n;
					//search templist and outputlist for this name. When found, update value to 0
					if(search(outhead, outputlistname) == 1){//its an output variable
						updateval(outhead, outputlistname, 0);
					}
					else {//it is temp variable. Check if it has been made. if not, then make.
						if(search(temphead, outputlistname) == 0) //not found. create new node
							temphead = insertLL(temphead, outputlistname);
						//either node has been created or has been found. update value
						updateval(temphead, outputlistname, 0);
					}
					//add this name to new LL holding all the decoder output variable names in order of input
					listhead = insertlistnode(listhead, outname, 0);
					//free(outname);
				}
				//convert this graycode into binary string
				binaryeq = graytobinary(graycodebinary, binaryeq, inputnum);
				//convert binary string to integer
				int listindex;
				listindex = bintoint(binaryeq, inputnum);
				//using index, iterate through output LL and return the name
				tempname = getname(listhead, listindex);
				if(search(temphead, tempname)==1) //temp variable from output LL
					updateval(temphead, tempname, 1);
				else
					updateval(outhead, tempname, 1);
				//free(tempname);
				free_listnodelist(listhead);
				//free(inputname);
				//free(outputlistname);
				//free(graycodebinary);
				//free(binaryeq);
				finish(linehead, string);
			} 
			else if(strcmp(mode, "MULTIPLEXER") == 0){
				struct listnode* multihead = NULL;
				int inputnum = 0;
				int tempval = 0;
				char *tempstring = malloc(25*sizeof(char));
				char *outputname = malloc(25*sizeof(char));
				char *inputname = malloc(25*sizeof(char));
				char *graycodebinary = malloc(25*sizeof(char));
				char *binaryeq = malloc(25*sizeof(char));
				sscanf(string+offset, "%d%n", &inputnum, &n);
				offset+=n;
				for(i=0; i<inputnum; i++){
					//read each of these inputs as a string
					char *s = malloc(25*sizeof(char));
					sscanf(string+offset, "%s%n", tempstring, &n);
					offset += n;
					strcpy(s, tempstring);
					//check if 0 or 1 or input LL or temp LL
					if(strcmp(tempstring, "0") == 0)  //0
						multihead = insertlistnode(multihead,	s, 0);
					else if(strcmp(tempstring, "1") == 0) //1
						multihead = insertlistnode(multihead, s, 1);
					else if(search(inhead, s)==1) {//input variable as multivalue
						if(assigned(inhead, s)==0)
							continue;
						else	
							multihead = insertlistnode(multihead, s, getval(inhead, s));
					}
					else { //not 0, not 1, not input variable. must be temp
						if(assigned(temphead, s)==0)
							continue;	
						else
							multihead = insertlistnode(multihead, s, getval(temphead, s));
					}
				}
				int x=0;
				int temp = inputnum;
				while(temp >>= 1) ++x;
				for(i=0; i<x; i++){ //after reading multivalues, read inputs. append
					sscanf(string+offset, "%s%n", inputname, &n);
					
					offset+=n;
					if(strcmp(inputname, "1") == 0)
						graycodebinary[i] = '1';
					else if(strcmp(inputname, "0") == 0)
						graycodebinary[i] = '0';
					else if(search(inhead, inputname)==1){
						if(assigned(inhead, inputname)==0)
							continue;
						else
							tempval = getval(inhead, inputname);
							graycodebinary[i] = tempval + '0';
					}
					else{
						if(assigned(temphead, inputname)==0)
							continue;
						else
							tempval = getval(temphead, inputname);
							graycodebinary[i] = tempval + '0';
					}				
				}
				//convert graycode binary to binary
				binaryeq = graytobinary(graycodebinary, binaryeq, x);
				//get index
				int tempindex;
				tempindex = bintoint(binaryeq, x);
				//using this index, get value from multivalue LL by iterating
				int multi_value = getmultival(multihead, tempindex);
				//get output
				sscanf(string+offset, "%s%n", outputname, &n);
				offset+=n;
				if(search(outhead, outputname)==1) //write to outLL
					updateval(outhead, outputname, multi_value);
				else { //write to tempLL, check if node exists.
					if(search(temphead, outputname)==0) //does not exist. create node.
						temphead = insertLL(temphead, outputname);
					updateval(temphead, outputname, multi_value);
				}
				//free(tempstring);
				//free(outputname);
				//free(inputname);
				//free(graycodebinary);
				//free(binaryeq);
				free_listnodelist(multihead);
				finish(linehead, string);
			}

	

		//free(var1);
		//free(var2);
		//free(var3);
		}
		}
		print_row(garr, outhead, numInputs);
		printf("\n");
	}



	
	//free everyhthing
	free(string);
	free(mode);
	free(garr);
}
