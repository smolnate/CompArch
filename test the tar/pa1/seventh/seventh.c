#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//print last character


int main(int argc, char** argv){
	int x;
	for(x=1; x<argc; x++){
		char *str = argv[x];
		printf("%c", str[strlen(str)-1]);
	}
	return 0;
}
