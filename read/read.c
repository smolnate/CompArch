#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  if(argc!=2){
    printf("insufficient arguments\n");
    exit(0);
  }
  printf("Entered file name is %s\n", argv[1]);
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL){
    printf("File does not exist\n");
    exit(0);
  }
  /* Now read the first line in the file */
  int num = 0;
  if (fscanf(fp, "%d\n", &num) == EOF){
    printf("Empty file\n");
    exit(0);
  }
  printf("the total number of values are %d\n", num);
  int j = 0;
  for(j = 0; j < num; j++){
    int temp;
    fscanf(fp, "%d\n", &temp);
    printf("The number is %d\n", temp);
  }
  fclose(fp);
  return  0;
}
