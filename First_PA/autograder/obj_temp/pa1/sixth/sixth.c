#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//isVowel returns 1 if the character is a vowel, 0 if consonant.
int isVowel(char);

int isVowel(char c){
	if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
		return 1;
	}
	else
		return 0;
}

int main(int argc, char** argv){
	int x;
	for(x=1; x<argc; x++){
		char *str = argv[x];
		//case 1: word starts with vowel, so add "yay" to the end.
		if(isVowel(str[0]) == 1)
			printf("%syay ", str);
		//case 2: word starts with consonant, take all letters up to the first vowel
		//put these letters at the end and add "ay" to the end.
		else{
			int y=0;
			while(y<strlen(str) && isVowel(str[y]) == 0){
				y++;
			}
			char *end = malloc(y);
			char *start = malloc(strlen(str)-y);
			end = strncpy(end, str, y);
			start = strncpy(start, str+y, strlen(str)-y);
			printf("%s%say ", start, end);
			free(end);
			free(start);
		}
	}		

	return 0;
}
