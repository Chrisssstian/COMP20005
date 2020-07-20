#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
  int n;
  int i, j, k;
  printf("Enter a number: ");
  if (scanf("%d", &n) == 0 || n <= 0) {
    printf("Invalid Input\n");
    exit(EXIT_FAILURE);
  }
  else {
    for (i=1; i<=n;i++){
      for(j=0;j<n-i;j++){
        printf(" ");
      }
      for (k=n;k>n-i;k--){
        printf("X");
      }
      printf("\n");
    }
  }


  return 0;
}
