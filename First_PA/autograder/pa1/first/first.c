#include <stdio.h>
#include <stdlib.h>

//Right Truncatable Prime
//

/*
 * This function checks whether the number is prime or not
 * Returns 0 if NOT PRIME, 1 if PRIME
 */

int isPrime(int num);

int isPrime(int num){	
	int i=2;
	for(i=2; i<num; i++){
		//number evenly divisible by i: NOT prime
		if((num%i)==0){
			return 0;
		}
	}
	return 1;	
}

int main(int argc, char** argv){
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error\n");
		exit(0);
	}
	int numbers = 0;
	//stores how many numbers to check in numbers
	fscanf(fp, "%d\n", &numbers);
	//allocate space for arr based on how many numbers there are
	int *arr = malloc(numbers * sizeof(int));
	int i = 0;
	//populate arr with all the numbers from file
	for(i=0; i<numbers; i++){
		fscanf(fp, "%d\n", &arr[i]);
	}
	
	int num=0;
	//for each number, run the prime test
	for(i=0; i<numbers; i++){
		num = arr[i];
		if(num<0)
			num = num*(-1);
		int temp = 1;
		while(num>0){
			temp = isPrime(num);
			if(temp == 0){
				break;
			}
			else{
				num = num / 10;
			}	
		}
		if(temp == 0)
			printf("no\n");
		else
			printf("yes\n");
	}

	//frees memory associated to arr to prevent leaking
	free(arr);
	return 0;
}  



