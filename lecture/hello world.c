#include <stdio.h>
#include <stdlib.h>

int arr[10] = {3, 5, 6, 8, 7, 42, 36, 87, 110};

int linearsearch(int key){
  int i=0;
  for(i=0; i<10; i++){
    if(arr[i] == key){
      return 1;
    }
  }
  return 0;
}

int main(){
  int key = 0;
  printf("Enter number to search: ");
  scanf("%d", &key);
  if(linearsearch(key)==0) //not found
    printf("Key %d not found\n", key);
  else //found
    printf("Key %d found\n", key);
  return 0;
}
