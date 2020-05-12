#include <stdio.h>
#include <stdlib.h>

//MAGIC SQUARE
//prints "magic" or "not-magic"

void populate(int**, int*, int, FILE*);
int checkRows(int**, int, int);
int checkCols(int**, int, int);
int checkDiag(int**, int, int);
int checkUsed(int*, int);

void populate(int **matrix, int *used, int n, FILE* fp){
	int x, y;
	int number;
	//read matrix from file
	for(x=0; x<n; x++){
		for(y=0; y<n-1; y++){
			fscanf(fp, "%d\t", &number);
			if(number < 1 || number > (n*n)){
				printf("not-magic");
				exit(0);
			}
			used[number-1] = 1;
			matrix[x][y] = number;
		}
		fscanf(fp, "%d\n", &number);
		used[number-1] = 1;
		matrix[x][n-1]=number;
	}
	return;
}

int checkRows(int **matrix, int n, int sum){
	int tempsum=0;
	int x, y;	
	//get tempsum of other rows, compare to sum
	for(x=0; x<n; x++){
		tempsum=0;
		//sum the row
		for(y=0; y<n; y++){
			tempsum = tempsum + matrix[x][y];
		}
		//compare tempsum to sum
		if(tempsum != sum){
			return 0;
		}
	}
	//passes the test
	return 1;	
}

int checkCols(int **matrix, int n, int sum){
	int tempsum=0;
	int x, y;	
	//get tempsum of other cols, compare to sum
	for(y=0; y<n; y++){
		tempsum=0;
		//sum the col
		for(x=0; x<n; x++){
			tempsum = tempsum + matrix[x][y];
		}
		//compare tempsum to sum
		if(tempsum != sum){
			return 0;
		}
	}
	//passes the test
	return 1;
}

int checkDiag(int **matrix, int n, int sum){
	int sum1=0, sum2=0;
	int x, y;
	//check one diagonal
	for(x=0, y=0; x<n; x++, y++){
		sum1 = sum1 + matrix[x][y];
	}
	//check other diagonal
	for(x=n-1, y=0; x>=0; x--, y++){
		sum2 = sum2 + matrix[x][y];
	}
	if(sum1==sum2 && sum1 == sum)
		return 1;
	else
		return 0;
}

int checkUsed(int *used, int n){
	int x=0;
	for(x=0; x<(n*n); x++){
		if(used[x]==0)
			return 0;
	}
	return 1;
}

int main(int argc, char** argv){
	int **matrix;
	int *used;
	FILE *fp = fopen(argv[1], "r");
	if(fp==NULL){
		printf("error");
		exit(0);
	}
	int n;
	fscanf(fp, "%d\n", &n);
	//n is size of matrix n x n

	//malloc the matrix
	matrix = malloc(sizeof(int*) * n);
	int i;
	for(i=0; i<n; i++){
		matrix[i] = malloc(sizeof(int)*n);
	}

	//malloc used numbers array
	used = malloc(sizeof(int) * (n*n));

	//populate used as 0 to start: update to 1 when number is used
	for(i=0; i<(n*n); i++){
		used[i]=0;
	}

	//populate matrix while updating used array
	populate(matrix, used, n, fp);	
	//get sum to check with functions
	int sum=0;
	for(i=0; i<n; i++){
		sum = sum + matrix[i][0];
	}
	if(checkRows(matrix,n,sum)==1 && checkCols(matrix,n,sum)==1 && checkDiag(matrix,n,sum)==1 && checkUsed(used,n)==1)
		printf("magic");
	else
		printf("not-magic");
	
	//free matrix
	for(i=0;i<n; i++){
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}
