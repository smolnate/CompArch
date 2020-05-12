#include <stdio.h>
#include <stdlib.h>

void free_matrix(double**, int);
void predict(double**, double*, int);	
double **inverse(double**, double**, double**, int);
double **transpose(double**, double**, int, int);
double multiply(double**, double**, int, int, int, int);
void divideRow(double**, int, double, int);
void subtractRow(double**, int, int, int);
void subtractMultipleRow(double**, int, int, double, int);

void free_matrix(double **m, int r){
	int x;
	for(x=0; x<r; x++){
		free(m[x]);
	}
	free(m);
}

//divideRow. Calling divideRow(m, r1, x, n) will divide r1 = r1 / x
void divideRow(double **m, int row, double x, int n){
	int i;
	for(i=0; i<n; i++){
		m[row][i] = m[row][i] / x;
	}
}

//subtract. Calling subtractRow(m, r1, r2) will do: r1 = r1-r2
void subtractRow(double **m, int r1, int r2, int n){
	int i;
	for(i=0; i<n; i++){
		m[r1][i] = m[r1][i] - m[r2][i];
	}
}

//subtract multipleRow. This does r1 = r1 - (r2 * x)
void subtractMultipleRow(double **m, int r1, int r2, double x, int n){
	int i;
	for(i=0; i<n; i++){
		m[r1][i] = m[r1][i] - (m[r2][i] * x);
	}
}

double **inverse(double **m1, double **augment, double **inv, int n){
	int i,j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			augment[i][j] = m1[i][j];
			if(i==j){
				augment[i][j+n] = 1;
			}
			else{
				augment[i][j+n] = 0;
			}
		}
	}
	//augmented matrix now is fully populated. Start gauss-jordan
	//Step 1: Going Down
	int z=0;
	//Get the first row to contain 1 in A[0][0]
	for(z=0; z<n; z++){
		if(augment[z][z] != 1.0)
			divideRow(augment, z, augment[z][z], n*2);
		for(i=z+1; i<n; i++){
			if(augment[i][z] != 0){
				subtractMultipleRow(augment, i, z, augment[i][z], n*2); 
			}
		}
	}
	//step 2: Going Up
	for(z=n-1; z>=0; z--){
		for(i=z-1; i>=0; i--){
			if(augment[i][z] != 0){
				subtractMultipleRow(augment, i, z, augment[i][z], n*2);
			}
		}
	}
	//populate inv
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			inv[i][j] = augment[i][j+n];
		}
	}
	return inv;	
}

double **transpose(double **m1, double **m2, int m, int n){
	int a, b;
	for(a=0; a<m; a++){
		for(b=0; b<n; b++){
			m2[b][a] = m1[a][b];
		}
	}
	return m2;
}


double multiply(double **m1, double **m2, int row, int col, int c1, int r2){
	double product = 0;
	int x, y;
	for(x=0, y=0; x<c1; x++, y++){
		product = product + (m1[row][x]*m2[y][col]);
	}
	return product;
}

void predict(double **weights, double *tests, int K){
	double result = weights[0][0];
	int i;
	for(i=0; i<K; i++){
		result = result + (weights[i+1][0]*tests[i]);			
	}	
	printf("%0.0lf\n", result);
	
}


int main(int argc, char **argv){
	double **X;
	double **XTXI;
	double **Y;
	double **XT; //X transpose array
	FILE *trainfp = fopen(argv[1], "r");
	FILE *testfp = fopen(argv[2], "r");
	int K, N;
	double **W;
	fscanf(trainfp, "%d\n", &K);
	fscanf(trainfp, "%d\n", &N);
	//allocate memory for matrices
	int i,j;	
	//allocate memory for the augmented matrix
	double **augment = malloc((K+1)*sizeof(double*));
	//allocate memory for the inverse matrix
	double **inv = malloc((K+1)*sizeof(double*));
	for(i=0; i<K+1; i++){
		inv[i] = malloc((K+1)*sizeof(double*));
	}
	for(i=0; i<K+1; i++){
		augment[i] = malloc(((K+1)*2)*sizeof(double));
	}
	//allocate matrix X
	X = malloc(N * sizeof(double*));
	for(i=0; i<N; i++){
		X[i] = malloc((K+1) * sizeof(double));
	}
	//allocate matrix X Transpose
	XT = malloc(((K+1) * sizeof(double*)));
	for(i=0; i<(K+1); i++){
		XT[i] = malloc(N * sizeof(double));
	}
	//allocate matrix Y and W
	Y = malloc(N * sizeof(double*));
	for(i=0; i<N; i++){
		Y[i] = malloc(sizeof(double));
	}
	W = malloc((K+1) * sizeof(double*));
	for(i=0; i<K+1; i++){
		W[i] = malloc(sizeof(double));
	}
	//allocate matrix for XT * X
	XTXI = malloc((K+1) * sizeof(double*));
	for(i=0; i<(K+1); i++){
		XTXI[i] = malloc(N*sizeof(double));
	}
	//populate matrices from the training data. First X
	for(i=0; i<N; i++){
		//store the 1 column first
		X[i][0] = 1.0;
		for(j=1; j<K+1; j++){
			fscanf(trainfp, "%lf%*c", &X[i][j]);
		}
		//last column is the price of house, store this in Y
		fscanf(trainfp, "%lf\n", &Y[i][0]);
	}	
	//get transposed matrix
	XT = transpose(X, XT, N, K+1);
	//multiply
	for(i=0; i<K+1; i++){
		for(j=0; j<K+1; j++){
			XTXI[i][j] = multiply(XT, X, i, j, N, N);
		}
	}
	XTXI = inverse(XTXI, augment, inv, K+1);	
	double **XTXIXT = malloc((K+1)*sizeof(double*));
	for(i=0; i<K+1; i++){
		XTXIXT[i] = malloc(N*sizeof(double));
	}

	for(i=0; i<K+1; i++){
		for(j=0; j<N; j++){
			XTXIXT[i][j] = multiply(XTXI, XT, i, j, K+1, K+1);
		}
	}
//MULTIPLY XTXIXT WITH Y TO GET W
	for(i=0;i<K+1; i++){
		for(j=0; j<1; j++){
			W[i][j] = multiply(XTXIXT, Y, i, j, N, 1);
		}
	}

	//populate M
	int M;
	fscanf(testfp, "%d\n", &M);
	//more matrices
	double *tests = malloc(K * sizeof(double*));
	for(i=0;i<M;i++){
		for(j=0; j<K-1; j++){
			fscanf(testfp, "%lf%*c", &tests[j]);
		}
		fscanf(testfp, "%lf%*c\n", &tests[K-1]);
		predict(W, tests, K);
	}
	free_matrix(X,N);
	free_matrix(Y,N);
	free_matrix(XTXI, K+1);
	free_matrix(XT, K+1);
	free_matrix(W, K+1);
	free(tests);
	return 0;
}
