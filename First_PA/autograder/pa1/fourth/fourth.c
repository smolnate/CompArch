#include <stdio.h>
#include <stdlib.h>
//Matrix Multiplication

int multiply(int**, int**, int, int, int, int);
void print_matrix(int**, int, int);
void free_matrix(int**, int);

int multiply(int **m1, int **m2, int row, int col, int c1, int r2){
	int product = 0;
	int x, y;
	//multiply the row in m1 with the col in m2
	for(x=0, y=0; x<c1; x++, y++){
			product = product + (m1[row][x]*m2[y][col]);
	}
	
	return product;
}

void free_matrix(int **matrix, int rows){
	//free cols before freeing main row
	int x;
	for(x=0; x<rows; x++){
		free(matrix[x]);
	}
	free(matrix);
	return;
}

void print_matrix(int **matrix, int rows, int cols){
	int x, y;
	for(x=0; x<rows; x++){
		for(y=0; y<cols; y++){
			if(y == cols-1){
				printf("%d\n", matrix[x][y]);
			}
			else{
				printf("%d\t", matrix[x][y]);
			}
		}
	}
	return;
}

int main(int argc, char** argv){
	int **matrix1;
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error");
		exit(0);
	}
	int r1, c1;
	fscanf(fp, "%d\t%d\n", &r1, &c1);
	int i=0, j=0;
	matrix1 = malloc(r1 * sizeof(int*));
	for(i=0; i<r1; i++){
		matrix1[i] = malloc(c1 * sizeof(int));
	}
	//populate matrix1
	for(i=0; i<r1; i++){
		for(j=0; j<c1-1; j++){
			fscanf(fp, "%d\t", &matrix1[i][j]);
		}
		fscanf(fp, "%d\n", &matrix1[i][c1-1]);
	}
	//read r2 c2 for second matrix
	int r2, c2;
	fscanf(fp, "%d\t%d\n", &r2, &c2);
	//check valid matrices
	if(c1 != r2){
		printf("bad-matrices");
		exit(0);
	}
	//create matrix2
	int **matrix2 = malloc(r2 * sizeof(int*));
	for(i=0; i<r2; i++){
		matrix2[i] = malloc(c2 * sizeof(int));
	}
	//populate matrix2
	for(i=0; i<r2; i++){
		for(j=0; j<c2-1; j++){
			fscanf(fp, "%d\t", &matrix2[i][j]);
		}
		fscanf(fp, "%d\n", &matrix2[i][c2-1]);
	}
	//create new result matrix
	int **result = malloc(r1 * sizeof(int*));
	for(i=0; i<r1; i++){
		result[i] = malloc(c2*sizeof(int));
	}
	//populate matrix3
	for(i=0; i<r1; i++){
		for(j=0; j<c2; j++){
			result[i][j] = multiply(matrix1, matrix2, i, j, c1, r2);
		}
	}
	print_matrix(result, r1, c2);
	//free all matrices!!!
	free_matrix(matrix1, r1);
	free_matrix(matrix2, r2);
	free_matrix(result, r1);	
	return 0;
}
