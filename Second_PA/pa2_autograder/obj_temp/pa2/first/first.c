#include <stdio.h>
#include <stdlib.h>

//Simple Hexadoku Solver

//All Functions Here
void printBoard(int[16][16]);
int sanity(int[16][16]);
int findEmpty(int[16][16], int);
int solveBoard(int[16][16], int);
void readBoard(int[16][16], FILE*);
int checkUsed(int[16]);
void reset(int[16]);
//Global board
int board[16][16] = {{0}};

//solving board by trying 1 number at a time
int solveBoard(int board[16][16], int start){
	int s[16]={0};
	int i;
	int ct=0;
	int index = findEmpty(board, start);
	while(index != -1){
		//try numbers
		for(i=0;i<16;i++){
			board[index/16][index%16] = i;
			s[i] = sanity(board);
		}
		//check to see only 1 sane number
		for(i=0;i<16;i++){
			ct += s[i];	
		}		
		if(ct == 0) //no sane number, OR more than 1 sane number
			return 0;
		if(ct > 1){ //more than 1 sane number, skip this and go to the next
			board[index/16][index%16] = -1; //remove the number
			return solveBoard(board, findEmpty(board, index+1));//go to next blank
		}
		//place sane number back on board spot
		for(i=0;i<16;i++){
			if(s[i]==1){
				board[index/16][index%16] = i;
				break;
			}
		}
		ct = 0;
		reset(s);
		index = findEmpty(board, start);
	}
	return 1;
}

//check the used array. Returns 1 if no numbers were duplicated, 0 if not.
int checkUsed(int used[16]){
	int i=0;
	for(i=0; i<16; i++){
		if(used[i]>1)
			return 0;
	}
	return 1;
}

//reset any used array to 0
void reset(int arr[16]){
	int i;
	for(i=0; i<16; i++){
		arr[i]=0;
	}
}

//Sanity Function. Returns 1 if sane, 0 if not.
int sanity(int board[16][16]){
	//First condition: checking rows
	int used[16] = {0};
	int i, j;
	for(i=0; i<16; i++){
		for(j=0; j<16; j++){
			if(board[i][j]>=0) used[board[i][j]]++;	
		}
		if(checkUsed(used)==0)
			return 0;
		reset(used);
	}
	//Second condition: checking cols
	reset(used);
	for(j=0; j<16; j++){
		for(i=0; i<16; i++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
		if(checkUsed(used)==0)
			return 0;
		reset(used);
	}
	//Third condition: checking subgrids of 4x4 size.		
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=0;i<4;i++){
		for(j=4;j<8;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=0;i<4;i++){
		for(j=8;j<12;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=0;i<4;i++){
		for(j=12;j<16;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=4;i<8;i++){
		for(j=0;j<4;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=4;i<8;i++){
		for(j=4;j<8;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=4;i<8;i++){
		for(j=8;j<12;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=4;i<8;i++){
		for(j=12;j<16;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=8;i<12;i++){
		for(j=0;j<4;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=8;i<12;i++){
		for(j=4;j<8;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=8;i<12;i++){
		for(j=8;j<12;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=8;i<12;i++){
		for(j=12;j<16;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=12;i<16;i++){
		for(j=0;j<4;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=12;i<16;i++){
		for(j=4;j<8;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=12;i<16;i++){
		for(j=8;j<12;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	for(i=12;i<16;i++){
		for(j=12;j<16;j++){
			if(board[i][j]>=0) used[board[i][j]]++;
		}
	}
	if(checkUsed(used)==0)
		return 0;
	reset(used);
	return 1;
}	

//Prints the board
void printBoard(int board[16][16]){
	int i,j;
	char c;
	for(i=0; i<16; i++){
		for(j=0; j<16; j++){
			if(board[i][j]>9){ //letter, 10-15
				c = board[i][j] + 55;
			}
			else{ //0-9
				c = board[i][j] + 48;
			}
			if(j == 15){
				printf("%c\n", c);
			}
			else{
				printf("%c\t", c);
			}
		}
	}
}

//Reads the board from input file
void readBoard(int board[16][16], FILE *fp){
	int i, j, k;
	char c;
	for(i=0; i<16; i++){
		for(j=0; j<16; j++){
			if(j == 15)
				fscanf(fp, "%c\n", &c);
			else
				fscanf(fp, "%c\t", &c);
			//convert char to int
			if(c == '-')
				k = -1;
			else if('0' <= c && c <= '9')
				k = c - 48;
			else
				k = c - 55;
			board[i][j] = k;		
		}
	}	
}

//Finds and returns index of the next empty spot on the board. Returns -1 if no empty.
int findEmpty(int board[16][16], int start){
	int index = 0;
	int i, j;
	for(i=0; i<16; i++){
		for(j=0; j<16; j++){
			if(board[i][j] == -1 && (i*16)+j >= start)
				return index;
			index++;
		}	
	}
	return -1;
}

int main(int argc, char **argv){
	int board[16][16];
	FILE *fp = fopen(argv[1], "r");
	readBoard(board, fp);
	//board[0][1] = 0;
	//printBoard(board);
	//printf("\n");
	//printf("Sanity: %d\n", sanity(board));
	int result = solveBoard(board, 0);
	while(result != 0){
		if(findEmpty(board, 0)==-1)
			break;
		result = solveBoard(board, 0);
	}
	if(result == 0){
		printf("no-solution");
		exit(0);
	}
	else
		printBoard(board);	
	return 0;
}
