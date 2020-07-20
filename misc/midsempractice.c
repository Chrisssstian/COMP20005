#include <stdio.h>

int
main(int argc, char const *argv[]) {
  int n;

  printf("Enter a number: ");
  scanf("%d",&n);

  int i, j, k;

  for (i = 1; i <= n; i++){

    for (j = 0; j <n-i; j++){
      printf("*");
    }

    for (k=n;k>n-i;k--){
      printf("X");
    }
  printf("\n");
  }


  return 0;
}
